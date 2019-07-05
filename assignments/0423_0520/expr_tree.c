/*
	FileName: expr.c 
	Author: Kevin
	Date: 29/04/9 18:56
	Description: calculate the result of a given expression(by expression tree)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define ML 2333
#define MP 65536

#define CALC(OP) \
	do \
	{ \
		if (postfix[i].op == #OP[0]) \
			postfix[i].val = postfix[i].lc->val OP postfix[i].rc->val; \
	} while (0)


typedef enum {false, true} bool;

typedef struct _Node
{
	bool is_op;
	char op;
	int val;
	struct _Node *lc, *rc;
} Node;

Node op_sta[ML], *tree_sta[ML], postfix[ML];
int op_top, tree_top, node_tot;


char prior[ML];
char buf[ML];


void init_prior(void);
void read_buf(void);
void get_postfix(void);
Node *build_expr_tree(void);
void print_node(const Node *p);


int main()
{
	init_prior();
	read_buf();
	get_postfix();

	Node *root = build_expr_tree();
	if (root != NULL)
	{
		print_node(root);
		if (root->lc != NULL)
			putchar(' '), print_node(root->lc);
		if (root->rc != NULL)
			putchar(' '), print_node(root->rc);
		putchar('\n');

		printf("%d", root->val);
	}

	return 0; 
}


void init_prior(void)
{
	prior['('] = prior[')'] = 0;
	prior['+'] = prior['-'] = 1;
	prior['*'] = prior['/'] = 2;
}

void read_buf(void)
{
	fgets(buf, ML-1, stdin);

	char *p, *q;
	for (p=q=buf; *p; ++p)
		if (!isspace(*p) && *p!='=')
			*q++ = *p;
	*q = '\0';
}

void get_postfix(void)
{
	Node next, out_op;
	char *p;
	for (p=buf, op_top=node_tot=0; *p; ++p)
	{
		if (isdigit(*p))
		{
			int val = 0;
			do val *= 10, val += *p++ - '0';
			while (isdigit(*p));
			--p;

			next.is_op = false;
			next.val = val;
			postfix[node_tot++] = next;
		}
		else
		{
			if (*p == ')')
			{
				while (1)
				{
					out_op = op_sta[--op_top];
					if (out_op.op == '(')
						break;
					postfix[node_tot++] = out_op;
				}
			}
			else
			{
				if (*p != '(')
				{
					while (op_top && prior[op_sta[op_top-1].op] >= prior[*p])
						postfix[node_tot++] = op_sta[--op_top];
				}

				next.is_op = true;
				next.op = *p;
				op_sta[op_top++] = next;
			}
		}
	}

	while (op_top)
		postfix[node_tot++] = op_sta[--op_top];
}

Node *build_expr_tree(void)
{
	int i;
	for (i=0; i<node_tot; ++i)
	{
		if (postfix[i].is_op)
		{
			postfix[i].rc = tree_sta[--tree_top];
			postfix[i].lc = tree_sta[--tree_top];

			CALC(+);
			CALC(-);
			CALC(*);
			CALC(/);
		}
		else
		{
			postfix[i].rc = NULL;
			postfix[i].lc = NULL;
		}

		tree_sta[tree_top++] = postfix+i;
	}

	return tree_sta[0];
}

void print_node(const Node *p)
{
	if (p->is_op)
		printf("%c", p->op);
	else
		printf("%d", p->val);
}

