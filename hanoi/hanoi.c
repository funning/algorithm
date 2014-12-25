#include "stdio.h"
#include "Log.h"
#include "stack.h"
#include "MemAdapter.h"


typedef struct {
    int n;
    char a;
    char b;
    char c;
    int state;
}node;
void hanoi(int n, char A, char B, char C) {
    if(n == 1) {
        printf("Move sheet %d from %c to %c\n", n, A, C);
    }
    else {
        hanoi(n-1, A, C, B);
        printf("Move sheet %d from %c to %c\n", n, A, C);
        hanoi(n-1, B, A, C);
    }
}

void hanoi1(int n, char A, char B, char C) {
    stack* s = tk_calloc(1, sizeof(stack));
    node* root = tk_calloc(1, sizeof(node));
    root->n = n;
    root->a = A;
    root->b = B;
    root->c = C;
    stack_push(s, root);
    do{
        node* temp = stack_pop(s);
        if (temp->state == 1) {
            printf("--------------------Move sheet %d from %c to %c\n", temp->n, temp->a, temp->c);
        } else {

            if(n == 1) {
               printf("Move sheet %d from %c to %c\n", n, A, C);
            } else {
                node* next = 0;            
                if (temp->n - 1 > 0) {
                    next = tk_calloc(1, sizeof(node));
                    next->n = temp->n - 1;
                    next->a = temp->b;
                    next->b = temp->a;
                    next->c = temp->c;

                    stack_push(s, next);
                }
                next = tk_calloc(1, sizeof(node)); 
                next->state = 1;
                next->n = temp->n;
                next->a = temp->a;
                next->b = temp->b;
                next->c = temp->c;
                stack_push(s, next);            
                if (temp->n - 1 > 0) {
                    next = tk_calloc(1, sizeof(node));
                    next->n = temp->n - 1;
                    next->a = temp->a;
                    next->b = temp->c;
                    next->c = temp->b;
                    stack_push(s, next);
                }
            }            
        }
        tk_free(temp);
    }while(stack_empty(s) == 0);
    stack_destory(s);
    tk_bookkeeper_mem_report();
}

void hanoiLocal(int n, char a, char b, char c) {
    if (n == 1) {
        printf("%d Move %c to %c\n", n, a, b);
    } else {
        hanoiLocal(n-1, a, c, b);
        printf("%d Move %c to %c\n", n, a, b);
        hanoiLocal(n-1, c, b, a);
    }
}

int main() {
    int n;
    printf("请输入盘数：");
    scanf("%d", &n);
    //hanoi(n, 'A', 'B', 'C');
//    hanoi1(n, 'A', 'B', 'C');
    hanoiLocal(n, 'A', 'B', 'C');
    return 0;
} 