#include "MemAdapter.h"
#include "stack.h"


#ifdef LINKEDLIST
stack* stack_init(int size) {
	stack* stack = tk_calloc(1, sizeof(stack));
	stack->head = 0;
	stack->len = 0;
	return stack;
}
void stack_push(stack* stack, void* point) {
	struct node* tmp = 0;
	if (stack == 0) {
		return;
	}
	if (point == 0) {
		return;
	}
	tmp = tk_calloc(1, sizeof(struct node));
	if (tmp == 0) {
		return;
	}
	tmp->data = point;
	tmp->next = stack->head;
	stack->head = tmp;
	(stack->len)++;
}
void* stack_pop(stack* stack) {
	void* temp = 0;
	struct node* tmpNode = 0;
	if (stack == 0) {
		return 0;
	}
	if (stack->head == 0) {
		return 0;
	}
	tmpNode = stack->head;
	stack->head = tmpNode->next;
	temp = tmpNode->data;
	tk_free(tmpNode);
	(stack->len)--;
	return temp;
}

int stack_empty(stack* stack) {
	int is_empty = 0;
	if (stack == 0) {
		is_empty = 1;
	}

	is_empty = (stack->head == 0)?1:0;
	return is_empty;
}
int stack_current(stack* stack) {
	if (stack == 0) {
		return 0;
	}
	return stack->len;
}
void stack_destory(stack* stack) {
	void* tmp = 0;
	if(stack == 0) {
		return;
	}
	tmp = stack_pop(stack);
	while(tmp != 0) {
		tk_free(tmp);
		tmp = stack_pop(stack);
	}
	tk_free(stack);
}
#else//LINKEDLIST
stack* stack_init(int size) {
	stack* stack = tk_calloc(1, sizeof(stack));
	stack->point = tk_calloc(1, size * sizeof(void*));
	stack->size = size;
	stack->current = 0;
	return stack;
}
void stack_push(stack* stack, void* point) {
	TK_TRACE_DEBUG(("push_stack stack->current = %d, stack->size = %d\n", stack->current, stack->size));
	if (stack->current >= stack->size - 1) {
		void** temp = tk_calloc(1, (stack->size + 10) * sizeof(void*));
		if (temp) {
			memcpy(temp, stack->point, (stack->current) * sizeof(void*));
			tk_free(stack->point);
			stack->point = temp;
			stack->size = stack->size + 10;
			(stack->point)[(stack->current)++] = point;
		}
	} else
		(stack->point)[(stack->current)++] = point;
	TK_TRACE_DEBUG(("out push_stack stack->current = %d, stack->size = %d\n", stack->current, stack->size));
}
void* stack_pop(stack* stack) {
	void** point = stack->point;
	void* temp = point[--(stack->current)];
	TK_TRACE_DEBUG(("pop_stack stack->current = %d\n", stack->current));
	return temp;
}
int stack_empty(stack* stack) {
	int is_empty = 0;
	if(stack->current == 0)
		is_empty = 1;
	return is_empty;
}
int stack_current(stack* stack) {
	return stack->current;
}
void stack_destory(stack* stack) {
	if(stack) {
		if (stack->point) {
		int i = 0;
		for (; i < stack->current; i++) {
			tk_free(stack->point[i]);
		}
		tk_free(stack->point);
		}
		tk_free(stack);
	}
}
#endif//LINKEDLIST