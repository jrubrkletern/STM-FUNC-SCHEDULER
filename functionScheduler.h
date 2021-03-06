#ifndef __FUNCTIONSCHEDULER_H__
#define __FUNCTIONSCHEDULER_H__

#include <stdio.h>
#include <stdint.h>

#define SCHEDULER_SIZE 32

typedef struct {
	void* (*func)(void*);
	void* funcParam;
	uint8_t funcPriority;
} funcQueueObj;
typedef struct {
	funcQueueObj funcQueue[SCHEDULER_SIZE];	
	_Atomic volatile uint8_t functionCount;
} functionScheduler; 


void insertFunction(void*, void*, uint8_t);
void readFunction(funcQueueObj*);
void runScheduler(void);
#endif 
