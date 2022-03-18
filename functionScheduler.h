#ifndef __FUNCTIONSCHEDULER_H__
#define __FUNCTIONSCHEDULER_H__

#include <stdio.h>
#include <stdint.h>

static const uint8_t SCHEDULER_SIZE = 32;
typedef struct functionScheduler_t {
	void* (*func)[SCHEDULER_SIZE];
	uint8_t funcPriority[SCHEDULER_SIZE];
} functionScheduler_t;

void insertFunction(void*);
void* readFunction(void);

#endif 
