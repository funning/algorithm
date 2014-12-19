#include "stdio.h"
#include "Log.h"
#include "stack.h"
#include "MemAdapter.h"

static int size = 0;
void print_list(int* list, int size) {
	int i = 0;
	printf("\n");
	for (; i < size; i++) {
		printf("%d ", list[i]);
	}
	
	printf("\n");
}
void swap(int* list, int i, int j) {
	int temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}
int part(int* list, int i, int j) {
	int m = i;
	int n = j;
	while(m < n) {
		while(list[m] <= list[i] && m < j)
			m++;
		while(list[n] >= list[i] && n > i)
			n--;
		swap(list, m, n);
	}
	if(m >= n)
		swap(list, m, n);
	swap(list, i, n);
	return n;
}


void sort1(int* list, int i, int j) {
	int p = part(list, i, j);
	if (i < p - 1)
		sort1(list, i, p - 1);
	if (j > p + 1)
		sort1(list, p + 1, j);
}




typedef struct{
	int i;
	int j;
}node;

void sort2(int* list, int i, int j) {
	stack* s = tk_calloc(1, sizeof(stack));
	node* root = tk_calloc(1, sizeof(node));
	root->i = i;
	root->j = j;
	stack_push(s, root);
	do{
		node* temp = stack_pop(s);
		int p = part(list, temp->i, temp->j);
		if (temp->i < p - 1) {
			node* next = tk_calloc(1, sizeof(node));
			next->i = temp->i;
			next->j = p - 1;
			stack_push(s, next);
		}
		if (temp->j > p + 1) {
			node* next = tk_calloc(1, sizeof(node));
			next->i = p + 1;
			next->j = temp->j;
			stack_push(s, next);

		}
		tk_free(temp);
	}while(stack_empty(s) == 0);
	stack_destory(s);
	tk_bookkeeper_mem_report();
}




int dealList(int* list, int size) {
	int tmp = 0, i = 0, j = size - 1;
	if (size <= 1) {
		return 1;
	}
	tmp = list[i];
	while(i < j) {
		while(j > i) {
			if (list[j] <= tmp) {
				list[i] = list[j];
				break;
			}
			j--;
		}
		while(j > i) {
			if (list[i] > tmp) {
				list[j] = list[i];
				break;
			}
			i++;
		}
	}
	list[i] = tmp;
	return i;
}

void divideAndConquer(int* list, int size) {
	int middle = 0;
	if (size <= 1) {
		return;
	}
	middle = dealList(list, size);
	divideAndConquer(list, middle);
	divideAndConquer(list+middle+1, size-middle-1);
}
void main() {
	int plist[] = {1,2,0,12,9,6,2,6,16,10,100,0,99};
	size = sizeof(plist) / sizeof(int);

	print_list(plist, size);
	divideAndConquer(plist, size);
//	sort2(plist, 0, size - 1);
	print_list(plist, size);
}
