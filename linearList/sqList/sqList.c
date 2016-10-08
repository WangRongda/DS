/* Sequence List implementation 
 * gcc 4.8
 * 123899696@qq.com
 */ 

#include <stdlib.h>
#include "sqList.h"

Status InitList(SqList *L)
{
	free(L->elem);
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem)
	{
		exit(OVERFLOW);
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}

Status DestroyList(SqList *L)
{
	if (!L->elem)  
	{
		return -1;
	}
	free(L->elem);
	L->elem = NULL;
	L->length = 0;
	L->listsize = 0;
	return OK;
}

Status ClearList(SqList *L)
{
	if (!L->elem)
	{
		return -1;
	}
	L->length = 0;
	return OK;
}


Status ListEmpty(SqList L)
{
	if (!L.elem)
	{
		return -1;
	}
	if (0 == L.length)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status ListLength(SqList L)
{
	if (!L.elem)
	{
		return -1;
	}
	return L.length;
}

Status GetElem(SqList L, int i, ElemType *e)
{
	if (!L.elem) 
	{
		return -1;
	}
	else if (i < 1 || i > L.length)
	{
		return ERROR;
	}
	*e = L.elem[i-1];
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
Status LocateElem(SqList L, ElemType e, bool (*compare)(ElemType, ElemType))
{
	if (!L.elem)
	{
		return -1;
	}
	int i;
	for (i = 0; i < L.length; i++)
	{
		if (compare(e, L.elem[i]))
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
Status ListTraverse(SqList L, bool (*visit)(int, ElemType))
{
	if (!L.elem)
	{
		return -1;
	}
	int i;
	for (i = 0; i < L.length; i++)
	{
		if (!visit(i+1, L.elem[i]))
		{
			return ERROR;
		}
	}
	return OK;
}

Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e)
{
	if (!L.elem)
	{
		return -1;
	}
	int i;
	for (i = 1; i < L.length; i++)
	{
		if (cur_e == L.elem[i])
		{
			*pre_e = L.elem[i-1];
			return OK;
		}
	}
	return ERROR;
}

Status NextElem(SqList L, ElemType cur_e, ElemType *next_e)
{
	if (!L.elem)
	{
		return -1;
	}
	int i;
	for (i = 0; i < (L.length - 1); i++)
	{
		if (cur_e == L.elem[i])
		{
			*next_e = L.elem[i+1];
			return OK;
		}
	}
	return ERROR;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
	if (!L->elem)
	{
		return -1;
	}
	if (i < 1 || i > L->length + 1)
	{
		return ERROR;
	}
	if (L->length >= L->listsize)
	{
		ElemType *newbase = (ElemType *)realloc(L->elem, 
				(L->listsize + LISTINCREAMENT) * sizeof(ElemType));
		if (!newbase) 
		{
			exit(OVERFLOW);
		}
		L->elem = newbase;
		L->listsize += LISTINCREAMENT;
	}
	ElemType *q = &(L->elem[i-1]), *p;
	for (p = &(L->elem[L->length - 1]); p >= q; --p)
	{
		*(p+1) = *p;
	}
	*q = e;
	++L->length;
	return OK;
}// ListInsert

Status ListDelete(SqList *L, int i, ElemType *e)
{
	if (!L->elem)
	{
		return -1;
	}
	if ((i < 1) || (i > L->length))
	{
		return ERROR;
	}
	ElemType *p = &(L->elem[i-1]);
	*e = *p;
	ElemType *q = L->elem + L->length - 1;
	for (++p; p <= q; ++p)
	{
		 *(p-1) = *p;
	}
	--L->length;
	return OK;
} //ListDelete

Status ListChange(SqList *L, int i, ElemType e)
{
	if (!L->elem)
	{
		return -1;
	}
	if ((i < 1) || (i > L->length))
	{
		return ERROR;
	}
	L->elem[i-1] = e;
	return OK;
}

Status ListExist(SqList L) 
{
	if (!L.elem)  //Sequence List does not exist
	{
		return ERROR;
	}
	return OK;
}

