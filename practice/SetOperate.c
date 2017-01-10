#include <stdio.h>
#include <stdlib.h>

/* Order OrderLink */
typedef struct LNode 
{
	char data;
	struct LNode *next;
} LNode, *LinkList;
typedef struct 
{
    LinkList head;
    int len;
}Order, *OrderLink;

void InitList(OrderLink L)
{
	L->head = (LinkList)malloc(sizeof(LNode));
	if (!(L->head)) exit(255);
	L->head->next = NULL;
    L->len = 0;
}

int ListInsert(OrderLink L, char e)
{
	if ( e < 'a' || e > 'z')
	{
		return -1;
	}
	LinkList peach = L->head;
    // order insert
	while (peach->next != NULL )
	{
		if (e < peach->next->data)
		{
			break;
		}
		if (e == peach->next->data)
		{
			return 1;
		}
		peach = peach->next;
	}
	LinkList pnew = (LinkList) malloc(sizeof(LNode));
	pnew->data = e;
	pnew->next = peach->next;
	peach->next = pnew;
    L->len++;
	return 1;
}

int GetElem(OrderLink L, int i, char *e)
{
	int n = 1;
	LinkList peach = L->head->next;
	while (peach && n < i)
	{
		peach = peach->next;
		n++;
	}
	if (!peach || i < 1)
	{
		return -1;
	}
	*e = peach->data;
    return 1;
}
/* Oder LinkList define end */

void Union(OrderLink L1, OrderLink L2)
{
	printf("Set1 U Set2 = ");
	int i = 1, j = 1;
	char ch1, ch2;
	while ((i <= L1->len) && (j <= L2->len))
	{
		GetElem(L1, i, &ch1); 
		GetElem(L2, j, &ch2);
		if (ch1 == ch2)
		{
			printf("%c", ch1);
			++i;
			++j;
            continue;
		}
		else if (ch1 < ch2)
		{
			printf("%c", ch1);
			++i;
            continue;
		}
		else
		{
			printf("%c", ch2);
			++j;
		}
	}
	while (i <= L1->len)
	{
		GetElem(L1, i++, &ch1);
		printf("%c", ch1);
	}
	while (j <= L2->len)
	{
		GetElem(L2, j++, &ch2);
		printf("%c", ch2);
	}
	puts("");
} //Union

void Intersection(OrderLink L1, OrderLink L2)
{
	printf("Set1 * Set2 = ");
	int i = 1, j = 1;
	char ch1, ch2;
	while ((i <= L1->len) && (j <= L2->len))
	{
		GetElem(L1, i, &ch1);
		GetElem(L2, j, &ch2);
		if (ch1 < ch2)
		{
			i++;
            continue;
		}
		else if (ch2 < ch1)
		{
			j++;
            continue;
		}
		else
		{
			printf("%c", ch1);
			i++;
			j++;
		}
	}
	puts("");
} //intersection

void Diff(OrderLink L1, OrderLink L2)
{
	printf("Set1 - Set2 = ");
	int i = 1, j = 1;
	char ch1, ch2;
	while ((i <= L1->len) && (j <= L2->len))
	{
		GetElem(L1, i, &ch1);
		GetElem(L2, j, &ch2);
		if (ch1 < ch2)
		{
			printf("%c", ch1);
			++i;
            continue;
		}
		else if (ch2 < ch1)
		{
			++j;
            continue;
		}
		else
		{
			++i;
			++j;
		}
	}
	while (i <= L1->len)
	{
		GetElem(L1, i++, &ch1);
		printf("%c", ch1);
	}
	puts("");
} //diff
	
int main()
{
	char Set1[1024], Set2[1024];
    OrderLink L1 = (OrderLink) malloc(sizeof(Order));
    OrderLink L2 = (OrderLink) malloc(sizeof(Order));

	fgets(Set1, 1024, stdin);
	fgets(Set2, 1024, stdin);
	InitList(L1);
	InitList(L2);

	int i = 0;
	while('\0' != Set1[i])
	{
		ListInsert(L1, Set1[i]);
		++i;
	}
	i = 0;
	while('\0' != Set2[i])
	{
		ListInsert(L2, Set2[i]);
		++i;
	}

	Union(L1, L2);
	Intersection(L1, L2);
	Diff(L1, L2);
	return 0;
}

