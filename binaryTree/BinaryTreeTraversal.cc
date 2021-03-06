////////////////////////////////////////////////////////////////////////////////
//       Filename:  theFirstOrder.cc
//
//    Description:   
//
//        Version:  1.0
//        Created:  2016-11-20 16:46:10
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  WangRongda (WRD), 123899696@qq.com
//   Organization:  HDU
//
// Copyright (c) 2016, WangRongda
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
using namespace std;

const int M = 100000;

struct node{
	int data;
	node *lc, *rc;
};

// Non-recursive Preorder traversal
void preorder(node *t){
	node *s[M], *p=t;
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

// Non-recursive inorder traversal
void inorder(node *t){
	node *s[M], *p=t;
	int top = -1; //置栈空
	do
	{
		while(p != NULL)
		{
			s[++top] = p;
			p = p->lc;
		}
		if(top != -1)
		{
			p = s[top--];
			cout << p->data << " "; //输出元素，用一个空格隔开
			p = p->rc;
		}
	} while(top!=-1 || p!=NULL);
	cout << endl;
}

// Non-recursive postorder traversal
void postorder(node *t)
{
	node *s[M], *p = t;
	int top = -1;
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
			cout << s[top--]->data << " ";
		}

		/// if top of stack is the left child
		cout << s[top--]->data << " ";
		p = s[top]->rc;
	} while (-1 != top);
	cout << endl;
}

// level travelsal
void levelorder(node *t)
{
	node *s[M], *p=t;
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

// Recursive Preorder traversal
void RePreorder(node *t) {
	if (t) {
		cout << t->data << " ";
		RePreorder(t->lc);
		RePreorder(t->rc);
	}
}
// Recursive inorder traversal
void ReInorder(node *t) {
	if (t) {
		ReInorder(t->lc);
		cout << t->data << " ";
		ReInorder(t->rc);
	}
}
// Recursive postorder traversal
void RePostorder(node *t) {
	if (t) {
		RePostorder(t->lc);
		RePostorder(t->rc);
		cout << t->data << " ";
	}
}

//构建二叉排序树
node* buildBinaryTree(int R[], int n){
	int i;
	node *root = new node, *p;
	root->data = R[0];
	root->lc = root->rc = NULL;
	for(i=1; i<n; i++){
		node *newNode = new node;
		newNode->data = R[i];
		newNode->lc = newNode->rc = NULL;
		p = root;
		while(p != NULL){
			if(p->data <= R[i]){
				if(p->rc == NULL) {p->rc = newNode;break;}
				else p = p->rc;
			}
			else {
				if(p->lc == NULL) {p->lc = newNode;break;}
				else p = p->lc;
			}
		}
	}
	return root;
}

int main()
{
	int i, n, array[1000];
	cin >> n;
	for(i=0; i<n; i++) cin >> array[i];
	node *root = buildBinaryTree(array, n);
	preorder(root);
	inorder(root);
	postorder(root);
	RePreorder(root);
	cout << endl;
	ReInorder(root);
	cout << endl;
	RePostorder(root);
	cout << endl;
	return 0;
}
