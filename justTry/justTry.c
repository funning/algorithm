#include "stdio.h"
#include "stack.h"
#include "MemAdapter.h"

#include "MemBookkeeper.h"
#include "Queue.h"
#include <string.h>

int partAscendingOrder(int* list, int size) {
	int i = 0, j = size - 1, k = 0;
	if (size <= 1) {
		return 0;
	}

	if (list == 0) {
		return 0;
	}
	k = list[i];
	while (i < j) {
		while (i < j) {
			if (list[j] < k) {
				list[i] = list[j];
				break;
			}
			j--;
		}
		while (i < j) {
			if (list[i] > k) {
				list[j] = list[i];
				break;
			}
			i++;
		}
	}
	list[i] = k;
	return i;
}
int partDescendingOrder(int* list, int size) {
	int i = 0, j = size - 1, k = 0;
	if (size <= 1) {
		return 0;
	}
	if (list == 0) {
		return 0;
	}
	k = list[j];
	while (i < j) {

		while (i < j) {
			if (list[i] < k) {
				list[j] = list[i];
				break;
			}
			i++;
		}
		while (i < j) {
			if (list[j] > k) {
				list[i] = list[j];
				break;
			}
			j--;
		}
	}
	list[i] = k;
	return i;
}
void quickSort(int* list, int size) {
	int middle = 0;
	if (size <= 1) {
		return;
	}
	if (list == 0) {
		return;
	}
	middle = partDescendingOrder(list, size);
	if (middle > 1) {
		quickSort(list, middle);
	}
	if (size - middle -1 > 1) {
		quickSort(list+middle+1, size - middle -1);
	}
}
void printList(int* list, int size) {
	int i = 0;
	while(i < size) {
		printf("%d ", list[i++]);
	}
	printf("\n");
}
void initNext(char* t, int* next, int size) {
	int i = 0, j = -1;
	if (size <= 1) {
		return;
	}
	if (next == 0) {
		return;
	}
	next[0] = -1;
	while (i < size && j < size) {
		if (j == -1 || t[i] == t[j]) {
			i++;
			j++;
			if (t[i] != t[j]) {
				next[i] = j;
			} else {
				next[i] = next[j];
			}
		} else {
			j = next[j];
		}
	}
}
int kmp(char* s, char* t) {
	int index = -1, i = -1, j = -1;
	int sLen = 0, tLen = 0, *next = 0;
	if (s == 0) {
		return 0;
	}
	if (t == 0) {
		return 0;
	}
	sLen = strlen(s);
	tLen = strlen(t);
	next = (int*)tk_calloc(1, sizeof(int)*tLen);
	initNext(t, next, tLen);
	while (i < sLen && j < tLen) {
		if (j == -1 || s[i] == t[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
	if (j == tLen) {
		index = i - j;
	}
	tk_free(next);
	return index;
}
int main() {
	int list[] = {1,9,3,6,0,12,16,7,19};
	int size = (sizeof(list))/(sizeof(int));
	char str[] = "qertuiopasdghjlnzxvc";
	char t[] = "op";
	printList(list, size);
	quickSort(list, size);
	printList(list, size);
	printf("kmp %d\n", kmp(str, t));
	return 0;
}
