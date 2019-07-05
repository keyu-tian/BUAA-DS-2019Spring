/*
	FileName: bst.c
	Author: Kevin
	Date: 29/04/19 15:55
	Description: implementation of BST
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T int
#define less(t1, t2) t1 < t2

typedef struct _TNode
{
	T val;
	struct _TNode *fa;
	struct _TNode *lc, *rc;
} TNode;
typedef struct
{
	TNode *root;
	int cnt;
} BST;
#define construct_tnode(_ptr, _fa, _lc, _rc, _val) \
	do \
	{ \
		(_ptr) = (TNode *)malloc(sizeof(TNode)), \
		(_ptr)->fa = _fa, \
		(_ptr)->lc = _lc, \
		(_ptr)->rc = _rc, \
		(_ptr)->val = _val; \
	} while (0)


void init(BST *pB)
{
	pB->cnt = 0;
	pB->root = NULL;
}


void rec_insert(TNode *pT, const T val)
{
	if (less(val, pT->val))
	{
		if (pT->lc == NULL)
			construct_tnode(pT->lc, pT, NULL, NULL, val);
		else
			rec_insert(pT->lc, val);
	}
	else	// pT->val >= val
	{
		if (pT->rc == NULL)
			construct_tnode(pT->rc, pT, NULL, NULL, val);
		else
			rec_insert(pT->rc, val);
	}
}
void insert(BST *pB, const T val)
{
	++pB->cnt;

	if (pB->root == NULL)
		construct_tnode(pB->root, NULL, NULL, NULL, val);
	else
		rec_insert(pB->root, val);
}


void dfs_leaf(const TNode *pT, const int dep)
{
	if (pT == NULL)
		return;
	if (pT->lc == NULL && pT->rc == NULL)
	{
		printf("%d %d\n", pT->val, dep);
		return;
	}
	
	dfs_leaf(pT->lc, dep+1);
	dfs_leaf(pT->rc, dep+1);
}



int main()
{
#ifdef _VSC_KEVIN
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	
	int n;
	scanf("%d", &n);
	
	BST bst;
	init(&bst);

	while (n--)
	{
		int val;
		scanf("%d", &val);
		insert(&bst, val);
	}
	
	dfs_leaf(bst.root, 1);
	
	return 0;
}

