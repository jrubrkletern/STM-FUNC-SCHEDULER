#include "functionScheduler.h"
#include <stdlib.h>



static functionScheduler *scheduler;

void insertFunction(void* function, void* param, uint8_t priority) {
	for(int i = 0; i < SCHEDULER_SIZE; i++) {
		if (scheduler->funcQueue[i].func == NULL) {
			scheduler->funcQueue[i].func = function;
			scheduler->funcQueue[i].funcPriority = priority;
			scheduler->functionCount++;
			break;
		}
		
	}
}

void* (*readFunction(void))(void*) {
	void* returnPtr = NULL;
	if (scheduler->functionCount > 0) {
		uint8_t highestPriority = 0;
		uint8_t highestPriorityIdx = 0;
		for (int i = 0; i < SCHEDULER_SIZE; i++) {
			if (scheduler->funcQueue[i].funcPriority > highestPriority) {
				highestPriority = scheduler->funcQueue[i].funcPriority;
				highestPriorityIdx = i;		
			}
		
		}
		returnPtr = scheduler->funcQueue[highestPriorityIdx].func;
		scheduler->funcQueue[highestPriorityIdx].func = NULL;
		scheduler->funcQueue[highestPriorityIdx].funcPriority = 0;
	}
	return returnPtr;
	
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
	void* (*functionPtr)(void*) = NULL;
	while(1) {
		if(scheduler->functionCount > 0) {
			functionPtr = readFunction();
			if(functionPtr != NULL) {
				
			}
		}
	}

	
}

