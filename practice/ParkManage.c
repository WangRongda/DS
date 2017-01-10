
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num;
	int time;
} Car;

/* SqList */
typedef struct  
{
	Car *base;
	Car *top;
	int stacksize;
} SqStack;

void InitStack(SqStack *S)
{
	S->base = (Car *)malloc(100 * sizeof(Car));
	if (!S->base) exit(-1);
	S->top = S->base;
	S->stacksize = 100;
}

char StackEmpty(SqStack S)
{
	if (S.base == S.top)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int StackLength(SqStack S)
{
	return S.top - S.base;
}

char GetTop(SqStack S, Car *e)
{
	if (S.top == S.base)
	{
		return 0;
	}
	*e = *(S.top - 1);
	return 1;
}

void Push(SqStack *S, Car e)
{
	if (S->top - S->base >= S->stacksize)
	{
		S->base = (Car *) realloc(S->base, 
				(S->stacksize + 10) * sizeof(Car));
		if (!S->base) exit(-1);
		S->top = S->base + S->stacksize;
		S->stacksize += 10;
	}
	*S->top++ = e;
}

char Pop(SqStack *S, Car *e)
{
	if (S->top == S->base)
	{
		return 0;
	}
	*e = *(--S->top);
	return 1;
}
/* SqStack end */



/* LinkQueue */
typedef struct QNode
{
	Car data;
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

char QueueEmpty(LinkQueue *Q)
{
	if (!Q->front->next)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int QueueLength(LinkQueue *Q)
{
	int length = 0;
	QueuePtr peach = Q->front->next;
	while (peach)
	{
		++length;
		peach = peach->next;
	}
	return length;
}

void EnQueue(LinkQueue *Q, Car e)
{
	QueuePtr pnew = (QueuePtr) malloc(sizeof(QNode));
	if (!pnew) exit(-1);
	pnew->data = e;
	pnew->next = NULL;
	Q->rear->next = pnew;
	Q->rear = pnew;
}

char DeQueue(LinkQueue *Q, Car *e)
{
	if (Q->front == Q->rear)
	{
		return 0;
	}
	QueuePtr pTemp = Q->front->next;
	*e = pTemp->data;
	Q->front->next = pTemp->next;
	if (Q->rear == pTemp)
	{
		Q->rear = Q->front;
	}
	free(pTemp);
	return 1;
}
/* QueueLink end */

int checkInput( int flag, char status, Car inputCar, SqStack Park, 
        LinkQueue Sidewalk);

int main()
{
	const int n = 2;
	Car inputCar, parkTopCar, car = { 0 };
	int flag;
	char status;
	SqStack Park, Spare;
	LinkQueue Sidewalk;

	inputCar = parkTopCar = car;
	InitStack(&Park);
	InitStack(&Spare);
	InitQueue(&Sidewalk);

	while ((flag = scanf("%c,%d,%d", &status, &inputCar.num, &inputCar.time))) 
	{
		if (-1 == checkInput(flag, status, inputCar, Park, Sidewalk)) {
			puts("Input again:");
			continue;
		}

		if ('A' == status) {
			if (StackLength(Park) < n) {
				Push(&Park, inputCar);
				printf("+ Car %d come int the end of Park.%d\n",
						inputCar.num, StackLength(Park));
			}
			else {
				EnQueue(&Sidewalk, inputCar);	
				printf("+ Car %d come in the end of sidewalk.%d\n",
						inputCar.num, QueueLength(&Sidewalk));
			}
		}
		if ('D' == status) {
			GetTop(Park, &parkTopCar); 
			// Park to Spare
			while (parkTopCar.num != inputCar.num) {
				Pop(&Park, &car);
				Push(&Spare, car);
				GetTop(Park, &parkTopCar);
			}

			Car leaveCar;
			Pop(&Park, &leaveCar); //Leave

			// Spare to Park
			while (!StackEmpty(Spare)) {
				Pop(&Spare, &car);
				Push(&Park, car);
			}
			// Sidewalk to Park
			if (!QueueEmpty(&Sidewalk)) {
				DeQueue(&Sidewalk, &car);
				car.time = inputCar.time;
				Push(&Park, car);
			}

			int stayTime = inputCar.time - leaveCar.time;
			float cost = 1;
			printf("- Car %d leave, Stay time: %d, cost: %.2f\n",
					inputCar.num, stayTime, stayTime * cost);
		}
	} //while(scanf))

	return 0;
} //main()











// for check Input
#define myfflush(stdin) if (feof(stdin) || ferror(stdin)) \
	                        {       \
								exit(0);        \
							}       \
                        int c = 0; \
                        while ((c = getchar()) != '\n' && c != EOF)

char compare(int e, int elem)
{
     if (e == elem)
     {
         return 1;
     }
     else
     {
         return 0;
     }
}

int SqLocateElem(SqStack S, Car e, char (*compare)(int, int))
{
    int i;
    for (i = 0; i < StackLength(S); i++)
    {
        if (compare(e.num, (S.base + i)->num))
        {
            return i+1;
        }
    }
    return 0;
}

int LinkLcateElem(LinkQueue Q, Car e, char (*compare)(int, int))
{
    int order = 1;
    QueuePtr peach = Q.front->next;
    while (peach)
    {
        if (compare(e.num, peach->data.num))
        {
            return order;
        }
        peach = peach->next;
        order++;
    }
    return 0;
}

int checkInput(int flag, char status, 
		Car inputCar, SqStack Park, LinkQueue Sidewalk)
{
	myfflush(stdin);
	if ('E' == status) {
		exit(0);
	}
	
	// check input format
	if (3 != flag) {
		puts("Input format error!\nUsage: [A|D|E],number,time\n\
example: A,1,5");
		return -1;
	}

	// check input status
	if (!('A' == status || 'D' == status || 'E' == status)) {
		puts("Input format error!\nUsage: [A|D|E],number,time\n\
				example: 'A',1,5");
		return -1;
	}
	
	// check input time, time must input bigger interger than last input 
	static int lastInputTime = -1;
	if (inputCar.time <= lastInputTime || inputCar.time < 0) {
		puts("Input time error!");
		return -1;
	}
	else {
		lastInputTime = inputCar.time;
	}

	//check input arrived car number
	if ('A' == status && 
			(0 != SqLocateElem(Park, inputCar, compare) || 
			 0 != LinkLcateElem(Sidewalk, inputCar, compare)))
   	{
		printf("Input error!\nThe car of number %d exist!\n", inputCar.num);
		return -1;
	}

	//check input leave car number
	if ('D' == status && (0 == SqLocateElem(Park, inputCar, compare))) {
		printf("The car of number %d is not in The park!\n", inputCar.num);
		return -1;
	}
	return 0;
} // check()

//check input end
