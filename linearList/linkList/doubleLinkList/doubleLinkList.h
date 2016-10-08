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
extern Status InitList(DuLinkList *L);
extern Status DestroyList(DuLinkList *L);
extern Status ClearList(DuLinkList L);
extern Status ListEmpty(DuLinkList L);
extern Status ListLength(DuLinkList L);
extern Status GetElem(DuLinkList L, int i, ElemType *e); //get value of i in T
extern Status LocateElem(DuLinkList L, ElemType e, bool (*compare)(ElemType, ElemType));
extern Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e);
extern Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e);
extern Status ListInsert(DuLinkList L, int i, ElemType e);
extern Status ListDelete(DuLinkList L, int i, ElemType *e);
extern Status ListChange(DuLinkList L, int i, ElemType e); //change value of i in T
extern Status ListTraverse(DuLinkList L, bool (*visit)(int, ElemType));
extern Status ListExist(DuLinkList L);


