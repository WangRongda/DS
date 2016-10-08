/* Linked List implementation 
 * gcc 4.8
 * 123899696@qq.com
 */ 

#include <stdlib.h>
#include "circularLinkList.h"

Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!(*L)) exit(OVERFLOW);
	(*L)->next = *L;
	return OK;
}

Status DestroyList(LinkList *L)
{
	if (!(*L))
	{
		return -1;
	}
	LinkList pNext;
	while ((*L)->next != (*L))
	{
		pNext = (*L)->next;
		(*L)->next = pNext->next;
		free(pNext);
	}
	free(*L);
	*L = NULL;
	return OK;
}

Status ClearList(LinkList L)
{
	if (!L)
	{
		return -1;
	}
	LinkList pNext;
	while (L->next != L)
	{
		pNext = L->next;
		L->next = pNext->next;
		free(pNext);
	}
	return OK;
}

Status ListEmpty(LinkList L)
{
	if (!L)
	{
		return -1;
	}
	if (L->next == L)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

Status ListLength(LinkList L)
{
	if (!L)
	{
		return -1;
	}
	int length = 0;
	LinkList peach = L->next;
	while (peach != L)
	{
		++length;
		peach = peach->next;
	}
	return length;
}

Status GetElem(LinkList L, int i, ElemType *e)
{
	if (!L) 
	{
		return -1;
	}
	int n = 1;
	LinkList peach = L->next;
	while ((peach != L) && n < i)
	{
		peach = peach->next;
		n++;
	}
	if ((peach == L) || i < 1)
	{
		return ERROR;
	}
	*e = peach->data;
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
Status LocateElem(LinkList L, ElemType e, bool (*compare)(ElemType, ElemType))
{
	if (!L)
	{
		return -1;
	}
	int order = 1;
	LinkList peach = L->next;
	while (peach != L)
	{
		if (compare(e, peach->data))
		{
			return order;
		}
		peach = peach->next;
		order++;
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
Status ListTraverse(LinkList L, bool (*visit)(int, ElemType))
{
	if (!L)
	{
		return -1;
	}
	LinkList peach = L->next;
	int order = 0;
	while (peach != L)
	{
		if (!visit(++order, peach->data))
		{
			return ERROR;
		}
		peach = peach->next;
	}
	return OK;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	if (!L)
	{
		return -1;
	}
	LinkList peach = L->next;
	LinkList pPre = peach;
	peach = peach->next;
	while (peach != L)
	{
		if (cur_e == peach->data)
		{
			*pre_e = pPre->data;
			return OK;
		}
		pPre = peach;
		peach = peach->next;
	}
	return ERROR;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	if (!L)
	{
		return -1;
	}
	LinkList peach = L->next;
	while (peach->next != L)
	{
		if (cur_e == peach->data)
		{
			*next_e = peach->next->data;
			return OK;
		}
		peach = peach->next;
	}
	return ERROR;
}

Status ListInsert(LinkList L, int i, ElemType e)
{
	if (!L)
	{
		return -1;
	}
	LinkList peach = L;
	int j = 0;
	int sign = 0;
	while (((L != peach) || (0 == sign)) && j < i-1)
	{
		peach = peach->next;
		j++;
		sign = 1;
	}
	if (((L == peach) && (1 == sign)) || i < 1)
	{
		return ERROR;
	}
	LinkList pnew = (LinkList) malloc(sizeof(LNode));
	pnew->data = e;
	pnew->next = peach->next;
	peach->next = pnew;
	return OK;
}// ListInsert

Status ListDelete(LinkList L, int i, ElemType *e)
{
	if (!L)
	{
		return -1;
	}
	LinkList peach = L;
	int j = 0;
	while((peach->next != L) && j < i - 1)
	{
		peach = peach->next;
		j++;
	}
	if ((peach->next == L) || i < 1)
	{
		return ERROR;
	}
	LinkList q = peach->next;
	*e = q->data;
	peach->next = q->next;
	free(q);
	return OK;
} //ListDelete

Status ListChange(LinkList L, int i, ElemType e)
{
	if (!L)
	{
		return -1;
	}
	LinkList peach = L->next;
	int j = 1;
	while ((peach != L) && j < i)
	{
		peach = peach->next;
		j++;
	}
	if ((L == peach) || i < 1)
	{
		return ERROR;
	}
	peach->data = e;
	return OK;
}

Status ListExist(LinkList L) 
{
	if (!L)  //Sequence List does not exist
	{
		return ERROR;
	}
	return OK;
}

