/* Linked List c head file */

//constant
typedef enum { FALSE, TRUE }bool;
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//storage structure 
typedef int ElemType;  
typedef int Status;  
typedef struct DuLNode 
{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
} DuLNode, *DuLinkList;

// Basic Operation
extern Status InitList(LinkList *L);
extern Status DestroyList(LinkList *L);
extern Status ClearList(LinkList L);
extern Status ListEmpty(LinkList L);
extern Status ListLength(LinkList L);
extern Status GetElem(LinkList L, int i, ElemType *e); //get value of i in T
extern Status LocateElem(LinkList L, ElemType e, bool (*compare)(ElemType, ElemType));
extern Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
extern Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
extern Status ListInsert(LinkList L, int i, ElemType e);
extern Status ListDelete(LinkList L, int i, ElemType *e);
extern Status ListChange(LinkList L, int i, ElemType e); //change value of i in T
extern Status ListTraverse(LinkList L, bool (*visit)(int, ElemType));
extern Status ListExist(LinkList L);


