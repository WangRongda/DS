/* Sequence List c head file */

//constant
//typedef enum { FALSE, TRUE }bool;
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//storage structure 
//typedef int ElemType;  
typedef int Status;  
#define LIST_INIT_SIZE 100
#define LISTINCREAMENT 10
/*
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
*/

template <class ElemType> class SqList
{
	private:
		ElemType *elem;
		int length;
		int listsize;
	public:
		SqList(ElemType *initElem = 0, int initLength = 0, int initListsize = 0)
			:elem(initElem), length(initLength), listsize(initListsize){};
		Status InitList();
		Status DestroyList();
		Status ClearList();
		Status ListEmpty();
		Status ListLength();
		Status GetElem(int i, ElemType *e);
		Status LocateElem(ElemType e, bool (*compare)(ElemType, ElemType));
		Status PriorElem(ElemType cur_e, ElemType *pre_e);
		Status NextElem(ElemType cur_e, ElemType *next_e);
		Status ListInsert(int i, ElemType e);
		Status ListDelete(int i, ElemType *e);
		Status ListChange(int i, ElemType e);
		Status ListTraverse(bool (*visit)(int, ElemType));
		Status ListExist();
};

/* Sequence List implementation 
 * gcc 4.8
 * 123899696@qq.com
 */ 

#include <stdlib.h>

#define TM template <class ElemType> \
Status	SqList<ElemType>::


TM InitList()
{
	free(elem);
	elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!elem)
	{
		exit(OVERFLOW);
	}
	length = 0;
	listsize = LIST_INIT_SIZE;
	return OK;
}

TM DestroyList()
{
	if (!elem)  
	{
		return -1;
	}
	free(elem);
	elem = NULL;
	length = 0;
	listsize = 0;
	return OK;
}

TM ClearList()
{
	if (!elem)
	{
		return -1;
	}
	length = 0;
	return OK;
}


TM ListEmpty()
{
	if (!elem)
	{
		return -1;
	}
	if (0 == length)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TM ListLength()
{
	if (!elem)
	{
		return -1;
	}
	return length;
}

TM GetElem(int i, ElemType *e)
{
	if (!elem) 
	{
		return -1;
	}
	else if (i < 1 || i > length)
	{
		return ERROR;
	}
	*e = elem[i-1];
	return OK;
}

/*
 * bool compare(ElemType e, ElemType elem);
 * {
 *		if (e == elem)
 *		{
 *			return 1;
 *		}
 *		else
 *		{
 *			return 0;
 *		}
 *	}
 */
TM LocateElem(ElemType e, bool (*compare)(ElemType, ElemType))
{
	if (!elem)
	{
		return -1;
	}
	int i;
	for (i = 0; i < length; i++)
	{
		if (compare(e, elem[i]))
		{
			return i+1;
		}
	}
	return 0;
}

/* example:
 * bool (int e)
 * {
 *		printf("%d\n", e);
 *		return OK;
 * }	
 */
TM ListTraverse(bool (*visit)(int, ElemType))
{
	if (!elem)
	{
		return -1;
	}
	int i;
	for (i = 0; i < length; i++)
	{
		if (!visit(i+1, elem[i]))
		{
			return ERROR;
		}
	}
	return OK;
}

TM PriorElem(ElemType cur_e, ElemType *pre_e)
{
	if (!elem)
	{
		return -1;
	}
	int i;
	for (i = 1; i < length; i++)
	{
		if (cur_e == elem[i])
		{
			*pre_e = elem[i-1];
			return OK;
		}
	}
	return ERROR;
}

TM NextElem(ElemType cur_e, ElemType *next_e)
{
	if (!elem)
	{
		return -1;
	}
	int i;
	for (i = 0; i < (length - 1); i++)
	{
		if (cur_e == elem[i])
		{
			*next_e = elem[i+1];
			return OK;
		}
	}
	return ERROR;
}

TM ListInsert(int i, ElemType e)
{
	if (!elem)
	{
		return -1;
	}
	if (i < 1 || i > length + 1)
	{
		return ERROR;
	}
	if (length >= listsize)
	{
		ElemType *newbase = (ElemType *)realloc(elem, 
				(listsize + LISTINCREAMENT) * sizeof(ElemType));
		if (!newbase) 
		{
			exit(OVERFLOW);
		}
		elem = newbase;
		listsize += LISTINCREAMENT;
	}
	ElemType *q = &(elem[i-1]), *p;
	for (p = &(elem[length - 1]); p >= q; --p)
	{
		*(p+1) = *p;
	}
	*q = e;
	++length;
	return OK;
}// ListInsert

TM ListDelete(int i, ElemType *e)
{
	if (!elem)
	{
		return -1;
	}
	if ((i < 1) || (i > length))
	{
		return ERROR;
	}
	ElemType *p = &(elem[i-1]);
	*e = *p;
	ElemType *q = elem + length - 1;
	for (++p; p <= q; ++p)
	{
		 *(p-1) = *p;
	}
	--length;
	return OK;
} //ListDelete

TM ListChange(int i, ElemType e)
{
	if (!elem)
	{
		return -1;
	}
	if ((i < 1) || (i > length))
	{
		return ERROR;
	}
	elem[i-1] = e;
	return OK;
}

TM ListExist() 
{
	if (!elem)  //Sequence List does not exist
	{
		return ERROR;
	}
	return OK;
}

