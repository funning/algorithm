#ifndef STACK__H__
#define STACK__H__
#include "DriverMem.h"

#define LINKEDLIST 1


#ifdef LINKEDLIST
typedef struct{
    struct node* head;
	int len;
}stack;
#else//LINKEDLIST
typedef struct{
    void** point;
	int current;
	int size;
}stack;
#endif//LINKEDLIST

stack* stack_init(int size);
void stack_push(stack* stack, void* point);
void* stack_pop(stack* stack);

int stack_empty(stack* stack);
int stack_current(stack* stack);
void stack_destory(stack* stack);
#endif//STACK__H__