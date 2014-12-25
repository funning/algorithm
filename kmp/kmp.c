#include "stdio.h"
#include "stack.h"
#include "MemAdapter.h"

#include "MemBookkeeper.h"
#include "Queue.h"
#include <string.h>

void initNextList(int* nextList, char* t) {
	int tLen = 0, j = 0, k = -1;
	if (t == 0) {
		return;
	}

	nextList[0] = -1;
	tLen = strlen(t);
	while (j < tLen) {
		if (k == -1 || t[j] == t[k]) {
			k++;
			j++;
			nextList[j] = k;
		} else {
			k = nextList[k];
		}
	}
}
void initNextListVal(int* nextList, char* t) {
	int tLen = 0, j = 0, k = -1;
	if (t == 0) {
		return;
	}
	nextList[0] = -1;
	tLen = strlen(t);
	while (j < tLen) {
		if (k == -1 || t[j] == t[k]) {
			k++;
			j++;
			if (t[j] != t[k]) {
				nextList[j] = k;
			} else {
				nextList[j] = nextList[k];
			}
		} else {
			k = nextList[k];
		}
	}
}

int next(char* t, int j, int* nextList) {
	if (j >= strlen(t) || t < 0) {
		return 0;
	}
	if (nextList[0] == 0) {
		// initNextList(nextList, t);
		initNextListVal(nextList, t);
	}
	return nextList[j];
}



char* kmpStrStr(char* s, char* t) {
	char* p = 0;
	int sLen = strlen(s);
	int tLen = strlen(t);
	int i = 0, j = 0;
	int* nextList = tk_calloc(1, sizeof(int)*tLen);
	// for (i = 0; i < sLen; ++i) {
	// 	j = 0;
	// 	do{
	// 		for (; j < tLen; ++j) {
	// 			if (s[i] != t[j]) {
	// 				j = next(t, j);
	// 				break;
	// 			}
	// 			i++;
	// 		} 
	// 	}while(j != 0);
	// 	if (j == tLen) {
	// 		p = s + i - j;
	// 		break;
	// 	}
	// }
	
	while (i < sLen && j < tLen) {
		if (j == -1 || s[i] == t[j]) {
			i++;
			j++;
		} else {
			j = next(t, j, nextList);
		}
	}
	tk_free(nextList);
	if (j >= tLen) {
		p = s + i - j;
	}
	return p;
}


int main() {
	char s[] = "aopakafoafjoafjijgorgrgplrg";
	char t[] = "oafji";
	char* p = kmpStrStr(s, t);
	printf("s = %s\nt = %s\np = %s\n", s, t, p);
	return 0;
}
