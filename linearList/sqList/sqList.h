/* Sequence List c head file */

//constant
typedef enum { FALSE, TRUE }bool;
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//storage structure 
typedef int ElemType;  
typedef int Status;  
#define LIST_INIT_SIZE 100
#define LISTINCREAMENT 10
typedef struct 
{
	//Static array: ElemType data[MaxSize];
	//Dynamic array
	ElemType *elem;
	int length;
	int listsize;
}SqList;

// Basic Operation
extern Status InitList(SqList *L);
extern Status DestroyList(SqList *L);
extern Status ClearList(SqList *L);
extern Status ListEmpty(SqList L);
extern Status ListLength(SqList L);
extern Status GetElem(SqList L, int i, ElemType *e); //get value of i in T
extern Status LocateElem(SqList L, ElemType e, bool (*compare)(ElemType, ElemType));
extern Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e);
extern Status NextElem(SqList L, ElemType cur_e, ElemType *next_e);
extern Status ListInsert(SqList *L, int i, ElemType e);
extern Status ListDelete(SqList *L, int i, ElemType *e);
extern Status ListChange(SqList *T, int i, ElemType e); //change value of i in T
extern Status ListTraverse(SqList L, bool (*visit)(int, ElemType));
extern Status ListExist(SqList L);


