/*
	FileName: bst.c
	Author: Kevin
	Date: 29/04/19 16:23
	Description: implementation of a BST
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MP 65536

#define T const char *
#define less(t1, t2) (strcmp(t1, t2) < 0)
#define greater(t1, t2) (strcmp(t1, t2) > 0)
#define equal(t1, t2) (strcmp(t1, t2) == 0)

typedef struct _TNode
{
	T val;
	int cnt;
	struct _TNode *fa;
	struct _TNode *lc, *rc;
} TNode;
TNode _mem_pool[MP], *_p_pool = _mem_pool;

typedef struct
{
	TNode *root;
	int cnt;
} BST;
#define construct_tnode(_ptr, _fa, _lc, _rc, _val) \
	do \
	{ \
		(_ptr) = _p_pool++, \
		(_ptr)->fa = _fa, \
		(_ptr)->lc = _lc, \
		(_ptr)->rc = _rc, \
		(_ptr)->val = _val; \
		(_ptr)->cnt = 1; \
	} while (0)


void init(BST *pB)
{
	pB->cnt = 0;
	pB->root = NULL;
}


void rec_insert(TNode *pT, T val)
{
	if (less(val, pT->val))
	{
		if (pT->lc == NULL)
			new_node(pT->lc, pT, NULL, NULL, val);
		else
			rec_insert(pT->lc, val);
	}
	else if (greater(val, pT->val))
	{
		if (pT->rc == NULL)
			new_node(pT->rc, pT, NULL, NULL, val);
		else
			rec_insert(pT->rc, val);
	}
	else
	{
		++pT->cnt;
	}
}
void insert(BST *pB, T val)
{
	++pB->cnt;

	if (pB->root == NULL)
		new_node(pB->root, NULL, NULL, NULL, val);
	else
		rec_insert(pB->root, val);
}


void dfs_leaf(const TNode *pT, const int dep)
{
	if (pT == NULL)
		return;
	dfs_leaf(pT->lc, dep+1);
	printf("%s %d\n", pT->val, pT->cnt);
	dfs_leaf(pT->rc, dep+1);
}


#define ML 16384
char buf[ML], *cur = buf;

int read_buf(const char *FILE_NAME)
{
	FILE *fin = fopen(FILE_NAME, "rb");

	fseek(fin, 0, SEEK_END);
	const int bytes = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	fread(buf, bytes, 1, fin);
	fclose(fin);

	return bytes;
}
char *next_word(void)
{
	while (*cur && !isalpha(*cur))
		++cur;
	if (!*cur)
		return NULL;

	char *begin = cur;
	do *cur = tolower(*cur);
	while (isalpha(*(++cur)));
	*cur++ = '\0';

	return begin;
}


int main()
{
#ifdef _VSC_KEVIN
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	
	read_buf("article.txt");

	BST bst;
	init(&bst);
	char *next;

	while ((next = next_word()) != NULL)
		insert(&bst, next);
	
	if (bst.root)
	{
		printf("%s", bst.root->val);
		if (bst.root->rc)
		{
			printf(" %s", bst.root->rc->val);
			if (bst.root->rc->rc)
			{
				printf(" %s", bst.root->rc->rc->val);
			}
		}
		
		printf("\n");
	}

	dfs_leaf(bst.root, 1);
	
	return 0;
}
