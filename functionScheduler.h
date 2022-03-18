#ifndef __FUNCTIONSCHEDULER_H__
#define __FUNCTIONSCHEDULER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdatomic.h>

static const uint8_t SCHEDULER_SIZE = 32;
typedef struct functionScheduler_t {
	void* (*func[SCHEDULER_SIZE])(void*);
	uint8_t funcPriority[SCHEDULER_SIZE];
	uint8_t functionCount;
} functionScheduler; 


void insertFunction(void*, uint8_t);
void* readFunction(void);
void runScheduler(void);
#endif 
