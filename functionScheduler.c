#include "functionScheduler.h"
#include <stdlib.h>



static functionScheduler *scheduler;

void insertFunction(void* function, uint8_t priority) {
	for(int i = 0; i < SCHEDULER_SIZE; i++) {
		if (scheduler->func[i] == NULL) {
			scheduler->func[i] = function;
			scheduler->funcPriority[i] = priority;
			scheduler->functionCount++;
			break;
		}
		
	}
}

void* readFunction(void) {
	void* returnPtr = NULL;
	if (scheduler->functionCount > 0) {
		uint8_t highestPriority = 0;
		uint8_t highestPriorityIdx = 0;
		for (int i = 0; i < SCHEDULER_SIZE; i++) {
			if (scheduler->funcPriority[i] > highestPriority) {
				highestPriority = scheduler->funcPriority[i];
				highestPriorityIdx = i;		
			}
		
		}
		returnPtr = scheduler->func[highestPriorityIdx];
		scheduler->func[highestPriorityIdx] = 0;
		scheduler->funcPriority[highestPriorityIdx] = 0;
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
		scheduler->func[i] = NULL;
		scheduler->funcPriority[i] = 0;
	}
	void* functionPtr = NULL;
	while(1) {
		if(scheduler->functionCount > 0) {
			functionPtr = readFunction();
		}
	}

	
}

