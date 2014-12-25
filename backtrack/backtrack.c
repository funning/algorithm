#include "stdio.h"
#include "Log.h"
#include "stack.h"
#include "MemAdapter.h"

#define N 8 
int column[N+1]; // 同栏是否有皇后，1表示有 
int rup[2*N+1]; // 右上至左下是否有皇后 
int lup[2*N+1]; // 左上至右下是否有皇后 
int queen[N+1] = {0}; 
int num; // 解答编号 

void backtrack(int); // 递回求解 

int main(void) { 
    int i; 
    num = 0; 

    for(i = 1; i <= N; i++) 
        column[i] = 1; 

    for(i = 1; i <= 2*N; i++) 
        rup[i] = lup[i] = 1; 

    backtrack1(1); 

    return 0; 
} 

void showAnswer() {
    int x, y;
    printf("\n解答 %d\n", ++num);
    for(y = 1; y <= N; y++) {
        for(x = 1; x <= N; x++) {
            if(queen[y] == x) {
                printf(" Q");
            }
            else {
                printf(" .");
            }
        }
        printf("\n");
    }
}

void backtrack(int i) { 
    int j;

    if(i > N) { 
        showAnswer();
    } 
    else { 
        for(j = 1; j <= N; j++) { 
            if(column[j] == 1 && 
                 rup[i+j] == 1 && lup[i-j+N] == 1) { 
                queen[i] = j; 
                // 设定为占用
                column[j] = rup[i+j] = lup[i-j+N] = 0; printf("p i=%d, j = %d, column[j] = %d, rup[i + j] = %d, lup[i - j + N] = %d, queen[i] = %d\n", i, j, column[j], rup[i + j], lup[i - j + N], queen[i]);
                backtrack(i+1); 
                column[j] = rup[i+j] = lup[i-j+N] = 1; printf("h i=%d, j = %d, column[j] = %d, rup[i + j] = %d, lup[i - j + N] = %d, queen[i] = %d\n", i, j, column[j], rup[i + j], lup[i - j + N], queen[i]);
            } 
        } 
    } 
} 
typedef struct {
	int i;
	int j;
	int state;
} node;

void backtrack1(int ii) { 
    stack* s = tk_calloc(1, sizeof(stack));
    node* root = tk_calloc(1, sizeof(node));
    root->i = 1;
    stack_push(s, root);
    do{
    	node* temp = stack_pop(s);
    	if (temp->state == 1 || temp->state == 2) {
	    	if (temp->i > N)
	    		showAnswer();
	    	else {
	    		if (temp->state == 1) {
	    			queen[temp->i] = temp->j; 
	                // 设定为占用
	                column[temp->j] = rup[temp->i+temp->j] = lup[temp->i-temp->j+N] = 0; 
	                //printf("p i=%d, j = %d, column[j] = %d, rup[i + j] = %d, lup[i - j + N] = %d, queen[i] = %d\n", temp->i, temp->j, column[temp->j], rup[temp->i + temp->j], lup[temp->i - temp->j + N], queen[temp->i]);
	    		} else {
	    			column[temp->j] = rup[temp->i+temp->j] = lup[temp->i-temp->j+N] = 1; 
	    			//printf("h i=%d, j = %d, column[j] = %d, rup[i + j] = %d, lup[i - j + N] = %d, queen[i] = %d\n", temp->i, temp->j, column[temp->j], rup[temp->i + temp->j], lup[temp->i - temp->j + N], queen[temp->i]);
	    		}
	    	}
    	} else {
    		if (temp->i > N)
	    		showAnswer();
	    	else
    		do{
    			temp->j += 1;
	    		if (temp->j <= N ){
	    			if(column[temp->j] == 1 && 
		                 rup[temp->i+temp->j] == 1 && lup[temp->i-temp->j+N] == 1) { 
		               node* next = tk_calloc(1, sizeof(node));
			    		next->i = temp->i;
			    		next->j = temp->j;
			    		stack_push(s, next);
		               next = tk_calloc(1, sizeof(node));
			    		next->i = temp->i;
			    		next->j = temp->j;
			    		next->state = 2;
			    		stack_push(s, next);
			    		next = tk_calloc(1, sizeof(node));
			    		next->i = temp->i + 1;
			    		next->j = 0;
			    		stack_push(s, next);
			    		next = tk_calloc(1, sizeof(node));
			    		next->i = temp->i;
			    		next->j = temp->j;
			    		next->state = 1;
		                stack_push(s, next);
		                //printf("break i = %d, j = %d\n", temp->i, temp->j);
		                break;
		           	} 
	    		} 
    		}while(temp->j <= N);
    		    		
    	}
    	tk_free(temp);
    }while(stack_empty(s) == 0);
} 