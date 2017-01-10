////////////////////////////////////////////////////////////////////////////////
//       Filename:  first.cc
//
//    Description:   
//
//        Version:  1.0
//        Created:  2016-12-27 09:15:41
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

struct node{
	int data;
	node *lc, *rc;
};

// Build order binary tree
node* buildBinaryTree(const int n){
	int i;
    int R[10000] = { 0 };
    for (i = 0; i < n; ++i) {
        cin >> R[i];
    }
    
	node *root = new node, *p;
	root->data = R[0];
	root->lc = root->rc = NULL;
	for(i = 1; i < n; i++){
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

// Non-recursive Preorder traversal
void preorder(node *t, const int n){
	node *s[n], *p=t;
	int top = -1; 
	do
	{
		while(p != NULL)
		{
			cout << p->data << " "; 
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
    node *root; 
    int n = 0;
    while (cin >> n && 0 != n)
    {
        root = buildBinaryTree(n);
        preorder(root, n);    
    }
    return 0;
}
