/*
	FileName: bst.c
	Author: Kevin
	Date: 13/05/19 15:53
	Description: LCA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML 21
#define MN 8192

typedef enum {false, true} bool;
typedef struct
{
	int lc, rc;
	const char *name;
} Node;
Node t[MN];


int tot;
char fa_name[MN][ML];
char son_name[MN][2][ML];
char q_name[2][ML];


int find_index(const char *name)
{
	int idx = -1, i;
	for (i=0; i<=tot; ++i)
	{
		if (strcmp(t[i].name, name) == 0)
		{
			idx = i;
			break;
		}
	}
	
	return idx;
}
int get_index(const char *name)
{
	int idx = find_index(name);
	if (idx == -1)
	{
		idx = ++tot;
		t[idx].name = name;
	}
	return idx;
}


int dep[MN];
int dfn[MN << 1], dnt;
int first[MN];
void dfs(const int u, const int fa)
{
	dep[u] = dep[fa] + 1;
	dfn[++dnt] = u, first[u] = dnt;
	if (t[u].lc)
	{
		dfs(t[u].lc, u);
		dfn[++dnt] = u;
	}
	if (t[u].rc)
	{
		dfs(t[u].rc, u);
		dfn[++dnt] = u;
	}
}
int rmq(int l, int r)
{
	if (l > r)
	{
		int tp = l;
		l = r;
		r = tp;
	}
	
	int i, min_o = dfn[l];
	for (i=l+1; i<=r; ++i)
	{
		if (min_o > dfn[i])
			min_o = dfn[i];
	}
	
	return min_o;
}


int main()
{
	FILE *fin = fopen("in.txt", "r");
	
	tot = 0;
	t[0].name = "NULL";

	int i, amount;
	fscanf(fin, "%d", &amount);
	for (i=0; i<amount; ++i)
	{
		fscanf(fin, "%s %s %s", fa_name[i], son_name[i][0], son_name[i][1]);
		int fa = get_index(fa_name[i]), lc = get_index(son_name[i][0]), rc = get_index(son_name[i][1]);
		t[fa].lc = lc, t[fa].rc = rc;
	}
	fclose(fin);

	dfs(1, 0);

	scanf("%s %s", q_name[0], q_name[1]);
	int u = find_index(q_name[0]), v = find_index(q_name[1]);
	
	if (dep[u] > dep[v])
	{
		int tp = u;
		u = v;
		v = tp;
	}
	
	int dis = dep[v] - dep[u];
	if (dis)
	{
		printf("%s %s %d", t[v].name, t[u].name, dis);
	}
	else
	{
		int lca_idx = rmq(first[u], first[v]);
		dis = dep[u] - dep[lca_idx];
		printf("%s %s %d\n", t[lca_idx].name, q_name[0], dis);
		printf("%s %s %d\n", t[lca_idx].name, q_name[1], dis);
	}
	

#ifdef _VSC_KEVIN
	system("pause");
#endif
	return 0;
}

