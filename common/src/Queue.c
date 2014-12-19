#include "Queue.h"
#include "MemAdapter.h"


Queue* QueueInit() {
	Queue* q = tk_calloc(1, sizeof(Queue));
	return q;
}
void* QueueGet(Queue* q) {
	void* data = 0;
	struct node* tmp = 0;
	if (q == 0) {
		return data;
	}
	if (q->head == 0) {
		return data;
	}
	if (q->head == q->tail) {
		q->tail = 0;
	}
	tmp = q->head;
	data = tmp->data;
	q->head = tmp->next;
	tk_free(tmp);
	return data;
}

void QueueAdd(Queue* q, void* data) {
	struct node* tmp = 0;
	if (q == 0) {
		return;
	}
	tmp = tk_calloc(1, sizeof(struct node));
	tmp->data = data;
	if (q->tail != 0) {
		(q->tail)->next = tmp;
	}
	q->tail = tmp;
	if (q->head == 0) {
		q->head = q->tail;
	}
}


void QueueDestory(Queue* q) {
	if (q == 0) {
		return;
	}


	while(q->head != 0) {
		void* tmp = QueueGet(q);
		tk_free(tmp);
	}
	tk_free(q);
}

int QueueSize(Queue* q) {
	int size = 0;
	struct node* tmp = 0;
	if (q == 0) {
		return size;
	}
	tmp = q->head;
	while (tmp != 0) {
		size++;
		tmp = tmp->next;
	}
	return size;
}