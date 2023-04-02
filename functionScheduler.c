#include "functionScheduler.h"
#include <stdlib.h>



static functionScheduler *scheduler;

void insertFunction(void* function, void* param, uint8_t priority) {
	uint8_t priorityIdx = priority - 1;
	if (scheduler->queueData[priorityIdx].funcCount < SCHEDULER_SIZE) {
		
		if(scheduler->queueData[priorityIdx].tail + 1 == SCHEDULER_SIZE) {
			scheduler->queueData[priorityIdx].tail = 0;
			} else {
			scheduler->queueData[priorityIdx].tail++;
			}
			scheduler->queueData[priorityIdx].funcCount++;
			scheduler->funcQueue[priorityIdx][tail].func = function;
			if(PARAM_STORAGE_EN) {
				memcpy(scheduler->paramData[priorityIdx][tail], param, MAX_PARAM_SIZE); 
			}
			//scheduler->funcQueue[priorityIdx][tail].funcParam = param; //need proper storage for parameters
			
		
		
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
		return;
	}
	funcObj->func = NULL;
	return;
	
}

void runScheduler(void) {
	scheduler = calloc(sizeof(functionScheduler));
	if(scheduler == NULL) {
		return;
	}
	if(PARAM_STORAGE_EN) {
		for(int i = 0; i < 10; i++) {
			for(j = 0; j < SCHEDULER_SIZE; j++)
			scheduler->paramData[i][j] = malloc(MAX_PARAM_SIZE);
			if(scheduler->paramData[i][j] == NULL) {
				return;
			}
			scheduler->funcQueue[i][j].funcParam = scheduler->paramData[i][j];
		}
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

