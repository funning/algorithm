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

void sort(priceIndex* priceIndexList, int num) {
	//todo
}
void doPriceDescend(int *priceDescend, int *weight, int *value, int num) {
	int i = 0;
	priceIndex* priceIndexList = tk_calloc(1, sizeof(priceIndex)*num);
	for (i = 0; i < num; ++i) {
		(priceIndexList[i]).index = i;
		(priceIndexList[i]).price = (float)value[i] / (float)weight[i];
	}
	sort(priceIndexList, num);
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
	freePackedList(list);
	tk_free(weight); 
	tk_free(priceDescend);
	tk_free(value);
	return 0;
}
