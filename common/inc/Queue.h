#ifndef QUEUE__H__
#define QUEUE__H__ 


#include "DriverMem.h"


typedef struct{
	struct node* head;
	struct node* tail;
}Queue;
Queue* QueueInit();
void* QueueGet(Queue* q);

void QueueAdd(Queue* q, void* data);
void QueueDestory(Queue* q);
int QueueSize(Queue* q);
#endif//QUEUE__H__