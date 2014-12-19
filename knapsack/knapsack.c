#include "stdio.h"
#include "stack.h"
#include "MemAdapter.h"

#include "MemBookkeeper.h"
#include "Queue.h"


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
	for (int i = 0; i < num; ++i) {
		priceIndex tmp = priceIndexList[i];
		tmp.index = i;
		tmp.price = (float)value[i] / (float)weight[i];
	}
	sort(priceIndexList, num);
	for (int i = 0; i < num; ++i) {
		priceIndex tmp = priceIndexList[i];
		priceDescend[i] = tmp.index;
	}
	tk_free(priceIndexList);
}
typedef struct {
	int index;
	float weight;
}packedNode;


packedNode* doPack(int num, int *weight, int *value, int *priceDescend, int maxPack) {
	packedNode* packedList = 0;
	return packedList;
}


#define MAXPACK 60
int main() {
	int num = 0;
	int *weight = 0;
	int *value = 0;
	int *priceDescend = 0;
	init(&num, &weight, &value);
	priceDescend = tk_calloc(1, sizeof(int)*num);
	doPriceDescend(priceDescend, weight, value, num);
	doPack(num, weight, value, priceDescend, MAXPACK);
	tk_free(weight); 
	tk_free(priceDescend);
	tk_free(value);
	return 0;
}
