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
typedef struct LNode 
{
	ElemType data;
	struct LNode *next;
} *Link, *Position;
typedef struct {
	Link head, tail;
	int len;
} LinkList;

// Basic Operation
extern Status MakeNode(Link *p, ElemType e);
extern void FreeNode(Link *p);
extern Status InitList(LinkList L);
extern Status DestroyList(LinkList L);
extern Status ClearList(LinkList L);
extern Status InsFirst(Link h, Link s);
extern Status DelFirst(Link h, Link *q);
extern Status Append(LinkList L, Link s);
extern Status Remove(LinkList L, Link *q);
extern Status InsBefore(LinkList L, Link *p, Link s);
extern Status InsAfter(LinkList L, Link *p, Link s);
extern Status SetCurElem(Link *p, ElemType e);
extern ElemType GetCurElem(LinkList L);
extern Status ListEmpty(LinkList L);
extern int ListLength(LinkList L);
extern Position GetHead(LinkList L);
extern Position GetLast(LinkList L);
extern Position PriorPos(LinkList L, Link p);
extern Position NextPos(LinkList L, link p);
extern Status LocatePos(LinkList L, int i, Link *p);
extern Status GetElem(LinkList L, int i, ElemType *e); //get value of i in T
extern Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));
extern Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
extern Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
extern Status ListInsert(LinkList L, int i, ElemType e);
extern Status ListDelete(LinkList L, int i, ElemType *e);
extern Status ListChange(LinkList L, int i, ElemType e); //change value of i in T
extern Status ListTraverse(LinkList L, Status (*visit)(int, ElemType));
extern Status ListExist(LinkList L);


