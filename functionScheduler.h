#ifndef __FUNCTIONSCHEDULER_H__
#define __FUNCTIONSCHEDULER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdatomic.h>

#define SCHEDULER_SIZE 32
#define MAX_PARAM_SIZE 16
#define PARAM_STORAGE_EN true
typedef struct {
	_Atomic unsigned char funcCount;
	_Atomic unsigned char head;
	_Atomic unsigned char tail;
} queueData;
typedef struct {
	void* (*func)(void*);
	void* funcParam;
} funcQueueObj;

typedef struct {
	funcQueueObj funcQueue[10][SCHEDULER_SIZE];
	void* paramData[10][SCHEDULER_SIZE];
	volatile queueData queueData[10];
	

} functionScheduler; 


void insertFunction(void*, void*, uint8_t);
void readFunction(funcQueueObj*);
void runScheduler(void);
#endif 
