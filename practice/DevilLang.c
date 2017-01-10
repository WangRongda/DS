#include <stdio.h>
#include <stdlib.h>

/* SqStack */

typedef struct  
{
	char *base;
	char *top;
	int stacksize;
} SqStack;

void InitStack(SqStack *S)
{
	S->base = (char *)malloc(100 * sizeof(char));
	if (!S->base) exit(-1);
	S->top = S->base;
	S->stacksize = 100;
}

void DestroyStack(SqStack *S)
{
    free(S->base);
    S->base = S->top = NULL;
    S->stacksize = 0;
}

int StackLength(SqStack S)
{
	if (!S.base)
	{
		return -1;
	}
	return S.top - S.base;
}

void Push(SqStack *S, char e)
{
	if (S->top - S->base >= S->stacksize)
	{
		S->base = (char *) realloc(S->base, 
				(S->stacksize + 10) * sizeof(char));
		if (!S->base) exit(-1);
		S->top = S->base + S->stacksize;
		S->stacksize += 10;
	}
	*S->top++ = e;
}

char Pop(SqStack *S, char *e)
{
	if (S->top == S->base)
	{
		return -1;
	}
	*e = *(--S->top);
	return 0;
}
/* SqStack End */

/* QueueLinkList */
typedef struct QNode
{
	char data;
	struct QNode *next;
} QNode, *QueuePtr;
typedef struct  
{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue;

void InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
	if (!Q->front) exit(-1);
	Q->front->next = NULL;
}

int QueueLength(LinkQueue *Q)
{
	if (!Q->front)
	{
		return -1;
	}
	int length = 0;
	QueuePtr peach = Q->front->next;
	while (peach)
	{
		++length;
		peach = peach->next;
	}
	return length;
}

void EnQueue(LinkQueue *Q, char e)
{
	QueuePtr pnew = (QueuePtr) malloc(sizeof(QNode));
	if (!pnew) exit(-1);
	pnew->data = e;
	pnew->next = NULL;
	Q->rear->next = pnew;
	Q->rear = pnew;
}

char DeQueue(LinkQueue *Q, char *e)
{
	if (Q->front == Q->rear)
	{
		return -1;
	}
	QueuePtr pTemp = Q->front->next;
	*e = pTemp->data;
	Q->front->next = pTemp->next;
	if (Q->rear == pTemp)
	{
		Q->rear = Q->front;
	}
	free(pTemp);
	return 0;
}
/* LinkQueue end */

void translateStack(char, SqStack *, LinkQueue *);
void version(SqStack);

int main()
{
	SqStack S;
	LinkQueue Q;
	char c;

	InitStack(&S);
	InitQueue(&Q);

	while (1) {
	    // Input a charactor, translate it and Push in stack
		while ('\n' != (c = getchar()) && EOF != c) {
			translateStack(c, &S, &Q);
		}

		//Print the translated string 
		Push(&S, '\0');
		puts(S.base);
		//Print corresponding Chinese
		version(S);
		DestroyStack(&S);
		if (EOF == c) {
			exit(0);
		}
		InitStack(&S);
	}
	return 0;
}

void translateStack(char c, SqStack *S, LinkQueue *Q)
{
	int i = 0;
	if ('B' == c) {
		char *b = "tAdA";
		while ('\0' != *(b + i))
		{
			translateStack(*(b + i), S, Q);
			i++;
		}
        return;
	}
	else if ('A' == c) {
		char *a = "sae";
		while ('\0' != *(a + i)) {
			translateStack(*(a + i), S, Q);
			i++;
		}		
        return;
	}
	// Translate string inside "(" ")"
    else if (')' == c) {
		Pop(S, &c); 
		while ('(' != c) {
			EnQueue(Q, c);
			Pop(S, &c);
		}

        char pre = Q->rear->data;
		while (QueueLength(Q) >= 2) {
			DeQueue(Q, &c);
            // Push each with the last as prefix
            Push(S, pre);
			Push(S, c);
		}
        // Push last without prefix
        DeQueue(Q, &c);
        Push(S, c);
        return;
	}
	else {
		Push(S, c);
	}
} //translateStack()

void version(SqStack S)
{
	int i;
	for (i = 0; i < StackLength(S); i++) {
		switch (*(S.base + i)) {
			case 't': printf("天"); break;
			case 'd': printf("地"); break;
			case 's': printf("上"); break;
			case 'a': printf("一只"); break;
			case 'e': printf("鹅"); break;
			case 'z': printf("追"); break;
			case 'g': printf("赶"); break;
			case 'x': printf("下"); break;
			case 'n': printf("蛋"); break;
			case 'h': printf("恨"); break;
			default : printf("%c", *(S.base + i));
		}
	}		
}
