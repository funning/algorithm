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
	while(i < *pNum) {
		printf("input %d object weight, value\n", i);
		scanf("%d, %d", &(*pWeight)[i], &(*pValue)[i]);
		i++;
	}
}
void initPrice(float *price, int *weight, int *value, int num) {
	int i = 0;
	for (int i = 0; i < num; ++i) {
		price[i] = (float)value[i] / (float)weight[i];
		printf("%f,\n", price[i]);
	}
}
int main() {
	int num = 0;
	int *weight = 0;
	int *value = 0;
	float *price = 0;
	init(&num, &weight, &value);
	price = tk_calloc(1, sizeof(float)*num);
	initPrice(price, weight, value, num);
	tk_free(weight); 
	tk_free(price);
	tk_free(value);
	return 0;
}
