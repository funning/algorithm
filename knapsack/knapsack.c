#include "stdio.h"
#include "stack.h"
#include "MemAdapter.h"

#include "MemBookkeeper.h"
#include "Queue.h"
#include <string.h>

void init(int* pNum, int** pWeight, int** pValue) {
	int i = 0;
	printf("input num\n");
	scanf("%d", pNum);
	*pWeight = (int*)tk_calloc(1, sizeof(int)*(*pNum));
	*pValue = (int*)tk_calloc(1, sizeof(int)*(*pNum));
	for(;i < *pNum;i++) {
		printf("input %d object weight, value\n", i);
		scanf("%d, %d", &(*pWeight)[i], &(*pValue)[i]);
	}
}
typedef struct {
	int index;
	float price;
}priceIndex;

int part(priceIndex* priceIndexList, int start, int end) {
	int middle = start, i = start, j = end;
	priceIndex startNode = {0};
	if (start >= end) {
		return middle;
	}
	startNode = priceIndexList[end];
	while(i < j) {
		while(i < j) {
			priceIndex tmp = priceIndexList[i++];
			if (tmp.price <= startNode.price) {
				priceIndexList[j] = tmp;
				i--;
				break;
			}
		}
		while(i < j) {
			priceIndex tmp = priceIndexList[j--];
			if (tmp.price > startNode.price) {
				priceIndexList[i] = tmp;
				j++;
				break;
			}

		}
	}
	middle = i;
	priceIndexList[middle] = startNode;
	return middle;
}

void quickSort(priceIndex* priceIndexList, int num) {
	int middle = 0;
	if (num <= 1) {
		return;
	}
	if (priceIndexList == 0) {
		return;
	}
	middle = part(priceIndexList, 0, num-1);
	quickSort(priceIndexList, middle);
	quickSort(priceIndexList+middle+1, num - middle - 1);
}

void doPriceDescend(int *priceDescend, int *weight, int *value, int num) {
	int i = 0;
	priceIndex* priceIndexList = tk_calloc(1, sizeof(priceIndex)*num);
	for (i = 0; i < num; ++i) {
		(priceIndexList[i]).index = i;
		(priceIndexList[i]).price = (float)value[i] / (float)weight[i];
	}
	quickSort(priceIndexList, num);
	for (i = 0; i < num; ++i) {
		priceIndex tmp = priceIndexList[i];
		priceDescend[i] = tmp.index;
	}
	tk_free(priceIndexList);
}


typedef struct {
	float* list;
	float tatol;
	float tatolValue;
}packedList;

void freePackedList(packedList* list) {
	if (list != 0) {
		tk_free(list->list);
		tk_free(list);
	}
}
packedList* packBreadthFirst(int num, int *weight, int *value, int *priceDescend, int maxPack, packedList* havePacked) {
	packedList* listPack = 0, *listNoPack = 0, *ret = 0, *right = 0, *left = 0;
	int next = 0;
	float currentMaxWeight = -1;
	if(havePacked != 0) {
		while((havePacked->list)[next++] != 0);
		next--;currentMaxWeight = (float)maxPack - (float)havePacked->tatol;
	}
	if (next >= num || currentMaxWeight == 0) {
		ret = tk_calloc(1, sizeof(packedList));
		ret->list = tk_calloc(1, sizeof(float)*(num));
		memcpy((void*)ret->list, (void*)havePacked->list, sizeof(float)*num);
		ret->tatol = havePacked->tatol;
		ret->tatolValue = havePacked->tatolValue;
		return ret;
	}
	listPack = tk_calloc(1, sizeof(packedList));
	listPack->list = tk_calloc(1, sizeof(float)*(num));
	listNoPack = tk_calloc(1, sizeof(packedList));
	listNoPack->list = tk_calloc(1, sizeof(float)*(num));
	if (havePacked != 0) {
		memcpy((void*)listPack->list, (void*)havePacked->list, sizeof(float)*next);
		listPack->tatol = havePacked->tatol;
		listPack->tatolValue = havePacked->tatolValue;
		memcpy((void*)listNoPack->list, (void*)havePacked->list, sizeof(float)*next);
		listNoPack->tatol = havePacked->tatol;
		listNoPack->tatolValue = havePacked->tatolValue;
	}
	currentMaxWeight = (float)maxPack - (float)listPack->tatol;
	if (currentMaxWeight <= weight[priceDescend[next]]) {
		(listPack->list)[next] = currentMaxWeight;
	} else {
		(listPack->list)[next] = weight[priceDescend[next]];
	}
	listPack->tatol += (listPack->list)[next];
	listPack->tatolValue += ((float)value[priceDescend[next]]/(float)weight[priceDescend[next]])*(listPack->list)[next];
	(listNoPack->list)[next] = -1;
	right = packBreadthFirst(num, weight, value, priceDescend, maxPack, listPack);
	left = packBreadthFirst(num, weight, value, priceDescend, maxPack, listNoPack);
	if (right->tatolValue >= left->tatolValue) {
		ret = right;
		freePackedList(left);
	} else {
		ret = left;
		freePackedList(right);
	}
	freePackedList(listPack);
	freePackedList(listNoPack);
	return ret;
}





void printReslut(packedList* list, int num, int *weight, int *value, int *priceDescend) {
	int i = 0;
	printf("tatol %f\n", list->tatol);
	printf("tatolValue %f\n", list->tatolValue);
	while (i < num) {
		printf("%d:%f(w)\n", priceDescend[i], (list->list)[i]);
		i++;
	}
}
typedef struct {
	int index;
	float weight;
}packNode;
typedef struct {
	stack* s;
	float tatolWeight;
	float tatolValue;
}packStack;
Queue* allResult = 0;
packStack* currentPackStack = 0;
packStack* getCurrentStack() {
	if (currentPackStack == 0) {
		currentPackStack = tk_calloc(1, sizeof(packStack));
		currentPackStack->s = stack_init(1);
	}
	return currentPackStack;
}
void destoryStack(packStack* ps) {
	if (ps == 0) {
		return;
	}
	stack_destory(ps->s);

	tk_free(ps);
}
void destoryCurrentStack() {
	destoryStack(currentPackStack);
	currentPackStack = 0;
}
void destoryAllResult() {
	packStack* ps = 0;
	if (allResult == 0) {
		return;
	}
	ps = (packStack*)QueueGet(allResult);
	while(ps != 0) {
		destoryStack(ps);
		ps = (packStack*)QueueGet(allResult);
	}
	QueueDestory(allResult);
	allResult = 0;
}
void saveCurrentResult() {
	packStack* tmp = 0, *tp = 0;
	packNode* node = 0;
	if (currentPackStack == 0) {
		return;
	}
	if (currentPackStack->s == 0) {
		return;
	}
	if (allResult == 0) {
		allResult = QueueInit();
	}
	tmp = tk_calloc(1, sizeof(packStack));
	tmp->s = stack_init(1);
	tp = tk_calloc(1, sizeof(packStack));
	tp->s = stack_init(1);
	node = stack_pop(currentPackStack->s);
	tmp->tatolValue = tp->tatolValue = currentPackStack->tatolValue;
	tmp->tatolWeight = tp->tatolWeight = currentPackStack->tatolWeight;
	while(node != 0) {
		packNode* tmpNode = tk_calloc(1, sizeof(packNode));
		*tmpNode = *node;
		stack_push(tp->s, tmpNode);
		stack_push(tmp->s, node);
		node = stack_pop(currentPackStack->s);
	}
	node = stack_pop(tmp->s);
	while(node != 0) {
		stack_push(currentPackStack->s, node);
		node = stack_pop(tmp->s);
	}
	QueueAdd(allResult, (void*)tp);
	destoryStack(tmp);
}
void pushPackNode(packNode* node, int *weight, int *value) {
	if (node == 0) {
		return;
	}
	if (currentPackStack == 0) {
		getCurrentStack();
	}
	if (currentPackStack->s == 0) {
		currentPackStack->s = stack_init(1);
	}
	stack_push(currentPackStack->s, node);
	currentPackStack->tatolWeight += node->weight;
	currentPackStack->tatolValue += ((float)value[node->index]/(float)weight[node->index])*(node->weight);
}
void popPackNode(int *weight, int *value) {
	packNode* node = 0;
	if (currentPackStack == 0) {
		return;
	}
	if (currentPackStack->s == 0) {
		return;
	}
	node = stack_pop(currentPackStack->s);
	if (node == 0) {
		return;
	}
	currentPackStack->tatolWeight -= node->weight;
	currentPackStack->tatolValue -= ((float)value[node->index]/(float)weight[node->index])*(node->weight);
	tk_free(node);
}
void packDeepFirst(int num, int *weight, int *value, 
	int *priceDescend, int maxPack, int currentV, int isPack) {
	packStack* ps = getCurrentStack();
	packNode* node = 0;
	float currentMaxWeight = 0;
	if (currentV >= num) {
		return;
	}
	currentMaxWeight = maxPack - ps->tatolWeight;
	node = tk_calloc(1, sizeof(packNode));
	node->index = priceDescend[currentV];
	if (isPack == 1) {
		node->weight = (currentMaxWeight >= weight[priceDescend[currentV]])?weight[priceDescend[currentV]]:currentMaxWeight;
	}
	pushPackNode(node, weight, value);
	if (ps->tatolWeight >= maxPack) {
		saveCurrentResult();
	} else {
		packDeepFirst(num, weight, value, priceDescend, maxPack, currentV+1, 1);
		packDeepFirst(num, weight, value, priceDescend, maxPack, currentV+1, 0);
	}
	popPackNode(weight, value);
}
void printAllResult() {
	packStack* tmp = 0;
	packNode* node = 0;
	printf("\ndeep result\n");
	if (allResult == 0) {
		printf("no result\n");
	}
	tmp = (packStack*)QueueGet(allResult);
	while(tmp != 0) {
		printf("\ntatolValue = %f, tatolWeight = %f :\n", tmp->tatolValue, tmp->tatolWeight);
		do {
			node = (packNode*)stack_pop(tmp->s);
			if (node == 0) {
				break;
			}
			printf("%d:%f\n", node->index, node->weight);
			tk_free(node);
		}while(1);
		destoryStack(tmp);
		tmp = (packStack*)QueueGet(allResult);
	}
} 
void doPackDeep(int num, int *weight, int *value, 
	int *priceDescend, int maxPack) {
	packDeepFirst(num, weight, value, priceDescend, maxPack, 0, 1);
	packDeepFirst(num, weight, value, priceDescend, maxPack, 0, 0);
	destoryCurrentStack();
	printAllResult();
	destoryAllResult();
}
#define MAXPACK 60
int main() {
	int num = 0;
	int *weight = 0;
	int *value = 0;
	int *priceDescend = 0;
	packedList* list = 0;
	init(&num, &weight, &value);
	priceDescend = tk_calloc(1, sizeof(int)*num);
	doPriceDescend(priceDescend, weight, value, num);
	list = packBreadthFirst(num, weight, value, priceDescend, MAXPACK, 0);
	printReslut(list, num, weight, value, priceDescend);
	doPackDeep(num, weight, value, priceDescend, MAXPACK);
	freePackedList(list);
	tk_free(weight); 
	tk_free(priceDescend);
	tk_free(value);
	tk_bookkeeper_mem_report();
	return 0;
}
