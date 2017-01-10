#include <stdio.h>
#include <stdlib.h>

/* Circle Link without head node */
typedef struct 
{
    int nOrder;
    int nPasswd;
} people;
typedef struct node
{
    people data;
    struct node *next;
} CLinkNode;
typedef struct
{
    CLinkNode *head;
    CLinkNode *rear;
} Joseph;

void ListInsert(Joseph *J, people p)
{
    CLinkNode *pNew = (CLinkNode *) malloc(sizeof(CLinkNode));
    pNew->data.nPasswd = p.nPasswd;
    pNew->data.nOrder = p.nOrder;

    pNew->next = J->head;
    J->rear->next = pNew;
    J->rear = pNew;
}

void ListDelete(Joseph *J, int m, people *p)
{
    int i = 1;
    for ( ; i <= m - 1; ++i) {
        J->head = J->head->next;
        J->rear = J->rear->next;
    }
    J->rear->next = J->head->next;
    *p = J->head->data;
    free(J->head);
    J->head = J->rear->next;
}
    
int main(void)
{
    Joseph joseph = { 0 };
    people p = { 0 };
    int passwd, order;
    int m;
    int i = 0;

    const int n = 7;
    //scanf("%d", &n);
    scanf("%d", &m);

    /* insert first */
    scanf("%d", &passwd);
    CLinkNode *first = (CLinkNode *) malloc(sizeof(CLinkNode));
    first->data.nOrder = 1;
    first->data.nPasswd = passwd;
    joseph.head = joseph.rear = first;

    for (i = 2; i <= n; i++)
    {
        scanf("%d", &passwd);
        p.nOrder = i;
        p.nPasswd = passwd;
        ListInsert(&joseph, p);
    }

    for (i = 1; i <= n - 1; i++)
    { 
        ListDelete(&joseph, m, &p);
        printf("%d ", p.nOrder);
        m = p.nPasswd;
    }
    
    /* delete last */
    printf("%d ", joseph.head->data.nOrder);
    free(joseph.head);
    
    return 0;
}
