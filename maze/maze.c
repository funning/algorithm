#include "stdio.h"
#include "stack.h"
#include "MemAdapter.h"

#include "MemBookkeeper.h"
#include "Queue.h"
int visit(int, int); 

#define I 7
#define J 9

int maze[I][J] = {{2, 2, 2, 2, 2, 2, 2, 2, 2},
                  {2, 0, 0, 2, 0, 0, 2, 2, 2},
                  {2, 0, 0, 0, 0, 0, 2, 2, 2},
                  {2, 0, 2, 2, 0, 2, 2, 2, 2},
                  {2, 2, 0, 0, 0, 2, 2, 2, 2},
                  {2, 0, 0, 0, 0, 0, 2, 2, 2},
                  {2, 2, 2, 2, 2, 2, 2, 2, 2},
				  {2, 2, 2, 2, 2, 2, 2, 2, 2},
				  {2, 2, 2, 2, 2, 2, 2, 2, 2}};

int startI = 1, startJ = 1;  // 入口
int endI = 5, endJ = 5;  // 出口
int success = 0;


void print_maze() {
	int i, j;
	for (i = 0; i < I; i++) {
		for (j = 0; j < J; j++) {
			if (maze[i][j] == 2)
				printf("H");
			else if (maze[i][j] >= 10)
				printf("0");
			else 
				printf("%d", maze[i][j]);

		}
		printf("\n");
	}
}









#define BASEVAULE 10
typedef struct {
	int x;
	int y;
}Postion;
int dealNode(int myMaze[][9], int x, int y, Postion end, int value, Postion** p) {
	int match = 0;
	if ((x == end.x) && (y == end.y)) {
		match = 1;
	}
	if ((x < end.x) && myMaze[y][x] == 0) {
		Postion* n = tk_calloc(1, sizeof(Postion));
		n->x = x;
		n->y = y;
		p[0] = n;
		myMaze[y][x] = value + 1;
	}
	return match;
}
int dealNodeR(int myMaze[][9], Queue* queue, Postion* current, Postion start, Postion end) {
	int match = 1, i = 0;
	int x = current->x, y = current->y, tmp = 0;
	Postion* p[6] = {0};
	tmp = x + 1;
	if (dealNode(myMaze, tmp, y, end, myMaze[y][x], &(p[i++])) == 1) {
		goto EXIT;
	}
	tmp = x - 1;
	if (dealNode(myMaze, tmp, y, end, myMaze[y][x], &(p[i++])) == 1) {
		goto EXIT;
	}
	tmp = y + 1;
	if (dealNode(myMaze, x, tmp, end, myMaze[y][x], &(p[i++])) == 1) {
		goto EXIT;
	}
	tmp = y - 1;
	if (dealNode(myMaze, x, tmp, end, myMaze[y][x], &(p[i++])) == 1) {
		goto EXIT;
	}
	match = 0;
	i = 0;
	for (;i<=3;i++) {
		if (p[i]) {
			QueueAdd(queue, p[i]);
		}
	}
EXIT:
	while(p[i]) {
		tk_free(p[i]);
		i++;
	}
	return match;
}
stack* toQueue(Queue* q) {
	stack* s = stack_init(1);
	Postion* p = QueueGet(q);
	while(p != 0) {
		stack_push(s, p);
		p = QueueGet(q);
	}
	return s;
}
int isNear(Postion p, Postion p1) {
	if (((p.x == p1.x) && (p.y + 1 == p1.y)) || ((p.x == p1.x) && (p.y - 1 == p1.y)) 
		|| ((p.x + 1 == p1.x) && (p.y == p1.y)) || ((p.x - 1 == p1.x) && (p.y == p1.y))) {
		return 1;
	}
	return 0;
}
void markPoit(int myMaze[][9], stack* s, Postion end) {
	Postion* p = stack_pop(s);
	Queue* q = QueueInit();
	Postion current = end;
	while(p != 0) {
		if (isNear(*p, current) == 1) {
			myMaze[p->y][p->x] = 1;
			current = *p;
			QueueAdd(q, p);
		} else {
			tk_free(p);
		}
		p = stack_pop(s);
	}
	p = QueueGet(q);
	printf("(5,5)");
	while(p != 0) {
		printf("<-(%d,%d)", p->x, p->y);
		tk_free(p);
		p = QueueGet(q);
	}
	printf("\n");
	QueueDestory(q);
}
int branchAndBound(int myMaze[][9], Postion start, Postion end) {
	int ok = 0;
	Queue* q = tk_calloc(1, sizeof(Queue));
	Postion* tmp = tk_calloc(1, sizeof(Postion));

	stack* s = stack_init(1);
	tmp->x = start.x;
	tmp->y = start.y;
	myMaze[start.y][start.x] = BASEVAULE;
	while(tmp != 0) {
		stack_push(s, tmp);
		if (dealNodeR(myMaze, q, tmp, start, end) == 1) {
			ok = 1;
			break;
		}
		tmp = QueueGet(q);
	}

	if (ok == 1) {
		markPoit(myMaze, s, end);
		stack_destory(s);
	}
	QueueDestory(q);
	tk_bookkeeper_mem_report();
	return ok;
}

int main(void) { 
    int i, j; 
    printf("end %d\n", maze[endI][endJ]);
    print_maze();

    // if(norecursive(startI, startJ) == 0)
    //     printf("\nfail\n");
    // else { 
    //     printf("\nok\n");
    //     print_maze();
    // } 
    {
    	Postion start = {0}; Postion end = {0};
	    start.x = startJ;
	    start.y = startI;
	    end.x = endJ;
	    end.y = endI;
	    branchAndBound(maze, start, end);
	    print_maze();
    }
    return 0; 
} 

int visit(int i, int j) { 
    maze[i][j] = 1; 
    if(i == endI && j == endJ)
        success = 1; 
    printf("visit maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, success = %d\n", i, j, maze[i][j], i, j + 1, maze[i][j + 1], i + 1, j, maze[i + 1][j], i, j - 1, maze[i][j - 1], i - 1, j, maze[i - 1][j], success);
    if(success != 1 && maze[i][j+1] == 0) visit(i, j+1);
    if(success != 1 && maze[i+1][j] == 0) visit(i+1, j);
    if(success != 1 && maze[i][j-1] == 0) visit(i, j-1); 
    if(success != 1 && maze[i-1][j] == 0) visit(i-1, j); 
    if(success != 1) 
        maze[i][j] = 0; 
    return success; 
}



typedef struct{
    int nodei;
    int nodej;
	int state;
}node;
void clear_foot(node* s, int top, node* s1, int* top1) {
	int i = *top1 - 1;
	for (; i > 0; i--) {
		printf("clear_foot s1[%d].nodei = %d, s1[%d].nodej = %d, s[%d].nodei = %d, s[%d].nodej = %d\n",
				i, s1[i].nodei, i, s1[i].nodej, top, s[top].nodei, top, s[top].nodej);
		if ((s1[i].nodei == s[top].nodei && ((s1[i].nodej - s[top].nodej) * (s1[i].nodej - s[top].nodej) == 1)) ||
			(s1[i].nodej == s[top].nodej && ((s1[i].nodei - s[top].nodei) * (s1[i].nodei - s[top].nodei) == 1)))
			break;
		else {
			(*top1)--;
			maze[s1[i].nodei][s1[i].nodej] = 6;
		}
	}
}


int norecursive(int i, int j) {
	stack* stack = stack_init(1);
	node* root = tk_calloc(1, sizeof(node));
	root->nodei = i;
	root->nodej = j;
	stack_push(stack, root);
	do{
		int n, m;
		node* temp = stack_pop(stack);
		printf("norecursive temp = %p, current_stacklist = %d\n", temp, stack_current(stack));
		m = temp->nodei;
		n = temp->nodej;
		if (temp->state == 1) {
			if (maze[m][n] == 1 && success == 0)
				maze[m][n] = 0;
			else
				maze[m][n] = 1;
			if (m == endI && n == endJ)
				success = 1;
			printf("norecursive maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, success = %d\n", m, n, maze[m][n], m, n + 1, maze[m][n + 1], m + 1, n, maze[m + 1][n], m, n - 1, maze[m][n - 1], m - 1, n, maze[m - 1][n], success);
		} else {
			if (success != 1) {
				node* next = tk_calloc(1, sizeof(node));
				next->state = 1;
				next->nodei = m;
				next->nodej = n;
				stack_push(stack, next);
				if (maze[m][n + 1] == 0) {
					next = tk_calloc(1, sizeof(node));
					next->state = 0;
					next->nodei = m;
					next->nodej = n + 1;
					stack_push(stack, next);
				}

				if (maze[m + 1][n] == 0) {
					next = tk_calloc(1, sizeof(node));
					next->state = 0;
					next->nodei = m + 1;
					next->nodej = n;
					stack_push(stack, next);
				}
				if (maze[m][n - 1] == 0) {
					next = tk_calloc(1, sizeof(node));
					next->state = 0;
					next->nodei = m;
					next->nodej = n - 1;
					stack_push(stack, next);
				}
				if (maze[m - 1][n] == 0) {
					next = tk_calloc(1, sizeof(node));
					next->state = 0;
					next->nodei = m - 1;
					next->nodej = n;
					stack_push(stack, next);
				}
				next = tk_calloc(1, sizeof(node));
				next->state = 1;
				next->nodei = m;
				next->nodej = n;
				stack_push(stack, next);
			}
		}
		tk_free(temp);
	}while(stack_empty(stack) == 0);
	printf("gggggggg maze[i][j] = %d\n", maze[i][j]);
	stack_destory(stack);
	tk_bookkeeper_mem_report();
	return success;
}
int visit2(int i, int j) {
	node* s = tk_calloc(1, I * J * sizeof(node));
	node* s1 = tk_calloc(1, I * J * sizeof(node));
	int p = 0;
	int p1[1] = {0};
	s[p].nodei = i;
	s[p].nodej = j;
	p++;
	do{
		int n, m;
		int havenext = 0;
		p--;
		m = s[p].nodei;
		n = s[p].nodej;
		maze[m][n] = 1;
		s1[p1[0]].nodei = m;
		s1[p1[0]].nodej = n;
		(p1[0])++;
		if (m == endI && n == endJ)
			success = 1;
		printf("visit2 maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, maze[%d][%d] = %d, success = %d\n", m, n, maze[m][n], m, n + 1, maze[m][n + 1], m + 1, n, maze[m + 1][n], m, n - 1, maze[m][n - 1], m - 1, n, maze[m - 1][n], success);
		if (success != 1) {
			if (maze[m][n + 1] == 0) {
				havenext++;
				s[p].nodei = m;
				s[p].nodej = n + 1;
				p++;
			}

			if (maze[m + 1][n] == 0) {
				havenext++;
				s[p].nodei = m + 1;
				s[p].nodej = n;
				p++;
			}
			if (maze[m][n - 1] == 0) {
				havenext++;
				s[p].nodei = m;
				s[p].nodej = n - 1;

				p++;
			}
			if (maze[m - 1][n] == 0) {
				havenext++;
				s[p].nodei = m - 1;
				s[p].nodej = n;
				p++;
			}
		}
		if (success == 1)
			break;
		if (havenext == 0) {int a[1] = {0};
			printf("clear_foot \n");
			maze[m][n] = 6;
			clear_foot(s, p - 1, s1, p1);
			print_maze();
//			scanf("%d", a);
		}
	}while(p != 0);
	printf("maze[i][j] = %d\n", maze[i][j]);
	if (s)
		tk_free(s);
	if (s1)
		tk_free(s1);

	return success;
}
