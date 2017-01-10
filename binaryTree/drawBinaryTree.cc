////////////////////////////////////////////////////////////////////////////////
//       Filename:  drawBinaryTree.cc
//
//    Description:  Draw Binary Tree 
//
//        Version:  1.0
//        Created:  2016-11-25 19:46:56
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  WangRongda (WRD), 123899696@qq.com
//   Organization:  HDU
//
// Copyright (c) 2016, WangRongda
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define myfor(n) for(int i = 0; i < n; i++)

struct node {
	int data;
	int height;
	node *lc;
	node *rc;
};

const int N = 5; // N = odd 

void print1(node *p)
{
	// print data of current node
	cout << setw((p->height)*(N - 1)) << " ";
	myfor(pow(2, (p->height) - 1) - 1)
	{
		cout << " ";
	}
	cout << setw(N) << p->data;
	myfor(pow(2, (p->height) - 1) - 1) 
	{
	   	cout << " ";
	}
}

// print +-------+
void print2(node *p)
{
	cout << setw((N + 1) * pow(2, p->height - 3)) << " ";
	cout << "+";
	myfor((N + 1) * pow(2, p->height - 2) - 1)
	{
		cout << "-";
	}
	cout << "+";
	cout << setw((N + 1) * pow(2, p->height - 3) - 1) << " ";
}

// print |       |
void print3(node *p)
{
	cout << setw((N + 1) * pow(2, p->height - 3)) << " ";
	cout << "|";
	myfor((N + 1) * pow(2, p->height - 2) - 1)
	{
		cout << " ";
	}
	cout << "|";
	cout << setw((N + 1) * pow(2, p->height - 3) - 1) << " ";
}

	 
// level travelsal
void levelorder(node *t, int n)
{
	node *s[n + 1], *p=t;
	int f, r; 
	f = r = 1; //设置队列的头指针和尾指针
	s[1] = p;
	int thisLevelCount = 1, nextLevelCount = 0;
	int thisLevelOrder = 0;
	while(f <= r)
	{
		p = s[f++];
		// print data of current node
		//print1(p);

		thisLevelOrder++;
		if (thisLevelOrder == thisLevelCount) {
			//cout << endl;
			// print +-------+
			myfor(thisLevelCount)
			{
				print2(p);
			}
			cout << endl;
			//print |       |
			myfor(thisLevelCount)
			{
				print3(p);
			}
			cout << endl;

			thisLevelOrder = 0;
			thisLevelCount = nextLevelCount;
			nextLevelCount = 0;
		}
		if(p->lc != NULL)
		{
			r++;
			nextLevelCount++;
			s[r] = p->lc;
		}
		if(p->rc != NULL)
		{
			r++;
			nextLevelCount++;
			s[r] = p->rc;
		}
	}
	cout << endl;
}

int getTreeHeight(node *t, const int n)
{
	node *s[n], *p = t;
	int top = -1;
	int lh, rh; // lh is the left-child-tree's height, rh is the right one
	do
	{
		while (NULL != p) {
			while (NULL != p) {
				s[++top] = p;
				p = p->lc;
			}
			p = s[top]->rc;
		}

		// if top of stack is the right child
		while (s[top] == s[top - 1]->rc) {
			lh = NULL == s[top]->lc ? 0 : s[top]->lc->height;
			rh = NULL == s[top]->rc ? 0 : s[top]->rc->height;
			s[top--]->height = 1 + (lh > rh ? lh : rh);
		}

		/// if top of stack is the left child
		lh = NULL == s[top]->lc ? 0 : s[top]->lc->height;
		rh = NULL == s[top]->rc ? 0 : s[top]->rc->height;
		s[top--]->height = 1 + (lh > rh ? lh : rh);
		
		p = s[top]->rc;
	} while (-1 != top);
	return  t->height;
}

// Build Binary-Sort-Tree(left-child < parent < right-child)
// from standard input
node* buildBinaryTree(const int n){
	node *root = new node, *p;
	cin >> root->data;
	root->lc = root->rc = NULL;
	myfor(n - 1)
	{
		node *newNode = new node;
		cin >> newNode->data;
		newNode->lc = newNode->rc = NULL;
		p = root;
		while (NULL != p) {
			if (p->data <= newNode->data) {
				if (NULL == p->rc) { p->rc = newNode; break; }
				else p = p->rc;
			}
			else {
				if (NULL == p->lc) { p->lc = newNode; break; }
				else p = p->lc;
			}
		}
	}
	return root;
}


// level travelsal
void level(node *t, const int n)
{
	node *s[n + 1], *p=t;
	int f, r; 
	f = r = 1; //设置队列的头指针和尾指针
	s[1] = p;
	while(f<=r)
	{
		p = s[f++];
		cout << p->data << " "; //输出元素，用一个空格隔开
		if(p->lc != NULL)
		{
			r++;
			s[r] = p->lc;
		}
		if(p->rc != NULL)
		{
			r++;
			s[r] = p->rc;
		}
	}
	cout << endl;
}
// Non-recursive Preorder traversal
void preorder(node *t, const int n){
	node *s[n], *p=t;
	int top = -1; //置栈空
	do
	{
		while(p != NULL)
		{
			cout << p->data << " "; //输出元素，用一个空格隔开
			s[++top] = p;
			p = p->lc;
		}
		if(top != -1)
		{
			p = s[top--];
			p = p->rc;
		}
	} while(top!=-1 || p!=NULL);
	cout << endl;
}


int main()
{
	int n;
	cin >> n;
	node *root = buildBinaryTree(n);
	getTreeHeight(root, n);
	//cout << endl;
	levelorder(root, n);
	//level(root, n);
	return 0;
}
	
