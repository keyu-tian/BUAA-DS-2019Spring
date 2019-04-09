/*
	FileName: multi.c
	Author: Kevin
	Date: 25/03/19 13:07
	Description: multiply two polynomials(implementation)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MN 2333
#define ML 233333
#define sort(begin, end) qsort(begin, (end)-(begin), sizeof(*begin), cmp)

typedef struct
{
	int k;
	int exp;
} Term;

Term multi(const Term a, const Term b);
Term *merge_poly(Term *begin, Term *end);

int cmp(const void *p, const void *q);


char buf[ML], *pNow = buf;
int next_int(void);


Term po1[MN], po2[MN], ans[MN];
int tot1, tot2, tot_ans;


int main()
{
	int i, j;
	fread(buf, 1, ML, stdin);

	do
	{
		po1[tot1].k = next_int();
		po1[tot1].exp = next_int();
		++tot1;
	}
	while (*pNow != '\n');

	do
	{
		po2[tot2].k = next_int();
		po2[tot2].exp = next_int();
		++tot2;
	}
	while (*pNow != '\n');

	for (i=0; i<tot1; ++i)
	{
		for (j=0; j<tot2; ++j)
		{
			ans[tot_ans++] = multi(po1[i], po2[j]);
		}
	}

	sort(ans, ans+tot_ans);
	tot_ans = merge_poly(ans, ans+tot_ans) - ans;
	for (i=0; i<tot_ans; ++i)
		printf("%d %d ", ans[i].k, ans[i].exp);

	return 0;
}


Term multi(const Term a, const Term b)
{
	return (Term)
	{
		.k = a.k * b.k,
		.exp = a.exp + b.exp
	};
}

Term *merge_poly(Term *begin, Term *end)
{
	if (end-begin <= 1)
		return end;

	Term *prev, *now;
	for (prev=begin, now=begin+1; now!=end; ++now)
	{
		if (now->exp != prev->exp)
			*++prev = *now;
		else
			prev->k += now->k;
	}

	return prev + 1;
}

int cmp(const void *p, const void *q)
{
	return ((Term *)q)->exp - ((Term *)p)->exp;
}


int next_int(void)
{
	int ret = 0;

	while (!isdigit(*pNow))
		++pNow;
	do ret = ret * 10 + *pNow++ - '0';
	while (isdigit(*pNow));

	return ret;
}
