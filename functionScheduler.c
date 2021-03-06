#include "functionScheduler.h"
#include <stdlib.h>



static functionScheduler *scheduler;

void insertFunction(void* function, void* param, uint8_t priority) {
	if (scheduler->functionCount < SCHEDULER_SIZE) {
		for (int i = 0; i < SCHEDULER_SIZE; i++) {
			if (scheduler->funcQueue[i].func == NULL) {
				scheduler->funcQueue[i].func = function;
				scheduler->funcQueue[i].funcPriority = priority;
				scheduler->functionCount++;
				
				break;
			}
		
		}
	}
}

void readFunction(funcQueueObj *funcObj) {
	
	if (scheduler->functionCount > 0) {
		uint8_t highestPriority = 0;
		uint8_t highestPriorityIdx = 0;
		for (int i = 0; i < SCHEDULER_SIZE; i++) {
			if (scheduler->funcQueue[i].funcPriority > highestPriority) {
				highestPriority = scheduler->funcQueue[i].funcPriority;
				highestPriorityIdx = i;		
			}
		
		}
		funcObj->func = scheduler->funcQueue[highestPriorityIdx].func;
		funcObj->funcParam = scheduler->funcQueue[highestPriorityIdx].funcParam;
		scheduler->funcQueue[highestPriorityIdx].func = NULL;
		scheduler->funcQueue[highestPriorityIdx].funcPriority = 0;
		scheduler->functionCount--; //NEEDS TO BE ATOMIC
	}
	return;
	
}

void runScheduler(void) {
	scheduler = malloc(sizeof(functionScheduler));
	if(scheduler == NULL) {
		return;
	}
	
	scheduler->functionCount = 0;
	for(int i = 0; i < SCHEDULER_SIZE; i++) {
		scheduler->funcQueue[i].func = NULL;
		scheduler->funcQueue[i].funcPriority = 0;
	}

	funcQueueObj funcPtrObj;
	while(1) {
		if(scheduler->functionCount > 0) {
			readFunction(&funcPtrObj);
			if (funcPtrObj.func != NULL) {
				(*funcPtrObj.func)(funcPtrObj.funcParam);
			}
		}
	}

	
}

