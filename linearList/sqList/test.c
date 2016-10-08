#include <stdio.h>
#include <stdlib.h>
#include "sqList.h"

bool compare(ElemType e, ElemType elem)
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
bool visit(int order, ElemType e)
{
	puts("------------------");
	printf("|order %3d|", order);
 	printf("%5d|\n", e);
 	return OK;
}	


/* test */
#define myfflush(stdin) if (feof(stdin) || ferror(stdin)) \
						{		\
							exit(0);		\
						}		\
						int c = 0; \
						while ((c = getchar()) != '\n' && c != EOF);

void menu()
{
	puts("");
	puts(" 1) Create an empty linear list(Initialize)  ");
	puts(" 2) Destroy linear list ");
	puts(" 3) Empty linear list ");
	puts(" 4) Whether the linear list is empty ");
	puts(" 5) Get the number of elements of the linear list  ");
	puts(" 6) Get the value of specified order ");
	puts(" 7) Get the first order whoes element satisfy function compare() ");
	puts(" 8) Get the previous element of specified element ");
	puts(" 9) Get the next element of specified element ");
	puts("10) Insert ");
	puts("11) Delete ");
	puts("12) Traverse ");
	puts("13) Whether the linear list exist ");
	puts("14) Change ");
	puts("15) Quit!");
	puts("16) Menu");
}

void print(int det)
{
	switch (det)
	{
		case -1:
			puts("Linear list doesn't exist");
			break;
		case 0:
			puts("Operation failed");
			break;
		case 1:
			puts("Operation OK");
			break;
	}
}

int main(int argc, char *argv[])
{
	int det = 0;
	int order = 0;
	ElemType e = 0;
	ElemType pre_e = {0}, cur_e = {0}, next_e = {0};
	SqList L = { 0 };
	menu();
	do {
		puts("");
		puts("Choose: (16 for menu)");
		int select = 0;
		scanf("%d",&select);

		switch (select)
		{
			case 1: 
				print(InitList(&L));
				break;
			case 2:
				print(DestroyList(&L));
				break;
			case 3:
				print(ClearList(&L));
				break;
			case 4:
				det = ListEmpty(L);
				if (1 == det)
				{
					puts("Empty!");
				}
				else if(det == 0)
				{
					puts("Not empty!");
				}
				else
				{
					puts("Linear list doesn't exist!");
				}
				break;
			case 5:
				det = ListLength(L);
				if (det == -1)
				{
					puts("Linear list doesn't exist!");
				}
				else
				{
					printf("The number of elements is : %d", det);
				}
				break;
			case 6:
				order = 0;
				e = 0;
				puts("Input the order: ");
				scanf("%d", &order);
				det = GetElem(L, order, &e);
				print(det);
				if (1 == det)
				{
					printf("The value of order %d is : %d\n", order, e);
				}
				break;
			case 7:
				if (!ListExist(L))
				{
					puts("linear list doesn't exist!");
				}
				e = 0;
				puts("Please input search element: ");
				scanf("%d", &e);
				det = LocateElem(L, e, compare);
				if (!det)
				{
					puts("Operation failed");
				}
				else
				{
					printf("The order is : %d\n", det);
				}
				break;
			case 8:
				pre_e = 0, cur_e = 0;
				puts("Please input element value: ");
				scanf("%d", &cur_e);
				det = PriorElem(L, cur_e, &pre_e);
				print(det);
				if (det == 1)
				{
					printf("The previous element is : %d\n", pre_e);
				}
				break;
			case 9:
				next_e = 0, cur_e = 0;
				puts("Please input element value: ");
				scanf("%d", &cur_e);
				det = NextElem(L, cur_e, &next_e);
				print(det);
				if (1 == det)
				{
					printf("The next element is : %d\n", next_e);
				}
				break;
			case 10:
				order = 0;
				e = 0;
				puts("Please input the order to insert: ");
				scanf("%d", &order);
				puts("Please input the value: ");
				scanf("%d", &e);
				print(ListInsert(&L, order, e));
				break;
			case 11:
				order = 0;
				e = 0;
				puts("Please input the order you want to delete :");
				scanf("%d", &order);
				det = ListDelete(&L, order, &e);
				print(det);
				if (det > 0)
				{
					printf("The value of deleted element is : %d\n", e);
				}
				break;
			case 12:
				print(ListTraverse(L, visit));
				puts("------------------");
				break;
			case 13:
				if (ListExist(L))
				{
					puts("exist!");
				}
				else
				{
					puts("not exist!");
				}
				break;
			case 14:
				order = 0;
				e = 0;
				puts("Please input order you want to change: ");
				scanf("%d", &order);
				puts("Please input a new value: ");
				scanf("%d", &e);
				print(ListChange(&L, order, e));
				break;
			case 15:
				exit(0);
			case 16:
				menu();
				break;
			default:
				myfflush(stdin);
				puts("Input error, 16 for menu, against");
		}
	} while (1);
	return 0;
}

/*
	do {
		puts("");
		puts("Choose: (m for menu)");
		char select[2] = { 0 };
		scanf("%s",&select);

		if (!strcmp("1", select))
		{
			print(InitList(&L));
		}
		else if (!strcmp("2", select))
		{
			print(DestroyList(&L));
		}
		else if (!strcmp("3", select))
		{
			print(ClearList(&L));
		}
		else if (!strcmp("4", select))
		{
			det = ListEmpty(L);
			if (1 == det)
			{
				puts("Empty!");
			}
			else if(det == 0)
			{
				puts("Not empty!");
			}
			else
			{
				puts("Linear list doesn't exist!");
			}
		}
		else if (!strcmp("5", select))
		{
			det = ListLength(L);
			if (det == -1)
			{
				puts("Linear list doesn't exist!");
			}
			else
			{
				printf("The number of elements is : %d", det);
			}
		}
		else if (!strcmp("6", select))
		{
			order = 0;
			ElemType e = { 0 };
			puts("Input the order: ");
			scanf("%d", &order);
			det = GetElem(L, order, &e);
			print(det);
			if (1 == det)
			{
				printf("The value of order %d is : %d\n", order, e);
			}
		}
		else if (!strcmp("7", select))
		{
			if (!ListExist(L))
			{
				puts("linear list doesn't exist!");
			}
			ElemType e = { 0 };
			puts("Please input search element: ");
			scanf("%d", &e);
			det = LocateElem(L, e, compare);
			if (!det)
			{
				puts("Operation failed");
			}
			else
			{
				printf("The order is : %d\n", det);
			}
		}
		else if (!strcmp("8", select))
		{
			ElemType pre_e = {0}, cur_e = {0};
			puts("Please input element value: ");
			scanf("%d", &cur_e);
			det = PriorElem(L, cur_e, &pre_e);
			print(det);
			if (det == 1)
			{
				printf("The previous element is : %d\n", pre_e);
			}
		}
		else if (!strcmp("9", select))
		{
			ElemType next_e = {0}, cur_e = {0};
			puts("Please input element value: ");
			scanf("%d", &cur_e);
			det = NextElem(L, cur_e, &next_e);
			print(det);
			if (1 == det)
			{
				printf("The next element is : %d\n", next_e);
			}
		}
		else if (!strcmp("10", select))
		{
			order = 0;
			ElemType e = { 0 };
			puts("Please input the order to insert: ");
			scanf("%d", &order);
			puts("Please input the value: ");
			scanf("%d", &e);
			print(ListInsert(&L, order, e));
		}
		else if (!strcmp("11", select))
		{
			order = 0;
			ElemType e = { 0 };
			puts("Please input the order you want to delete :");
			scanf("%d", &order);
			det = ListDelete(&L, order, &e);
			print(det);
			if (det > 0)
			{
				printf("The value of deleted element is : %d\n", e);
			}
		}
		else if (!strcmp("12", select))
		{
			print(ListTraverse(L, visit));
			puts("------------------");
		}
		else if (!strcmp("13", select))
		{
			if (ListExist(L))
			{
				puts("exist!");
			}
			else
			{
				puts("not exist!");
			}
		}
		else if (!strcmp("14", select))
		{
			order = 0;
			ElemType e = { 0 };
			puts("Please input order you want to change: ");
			scanf("%d", &order);
			puts("Please input a new value: ");
			scanf("%d", &e);
			print(ListChange(&L, order, e));
		}
		else if (!strcmp("q", select))
		{
			break;
		}
		else if (!strcmp("m", select))
		{
			menu();
		}
		else 
		{
			puts("Input error, 'm' for menu, against");
		}
	}while(1);
*/
