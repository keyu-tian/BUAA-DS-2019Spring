/*
	FileName: unique.c 
	Author: Kevin
	Date: 27/05/19 18:01
	Description: dfs(backtracking search)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

#define MN 1003

int V, E, S, T;
int dest[MN];

typedef struct
{
	int v;
	int id;
} Edge;

Edge edge[MN][MN];
int tot[MN];

void add_edge(const int u, const int v, const int id)
{
	edge[u][tot[u]].id = id;
	edge[u][tot[u]].v = v;
	tot[u]++;
}

int cmp(const void *p, const void *q)
{
	return ((Edge *)p)->id - ((Edge *)q)->id;
}
void sort_edge()
{
	int u;
	for (u=0; u<V; ++u)
		if (tot[u] > 1)
			qsort(edge[u], tot[u], sizeof(*edge[u]), cmp);
}


bool ins[MN];
int sta[MN], top;
void dfs(const int u)
{
	if (u == T)
	{
		int i;
		for (i=0; i<top; ++i)
			printf("%d ", sta[i]);
		puts("");
	}

	int i, v, id;
	for (i=0; i<tot[u]; ++i)
	{
		id = edge[u][i].id;
		v = edge[u][i].v;
		if (!ins[v])
		{
			ins[v] = true;
			sta[top++] = id;
			dfs(v);
			--top;
			ins[v] = false;
		}
	}
}


int main()
{
	scanf("%d %d", &V, &E);
	
	int u, v, id;
	while (E--)
	{
		scanf("%d %d %d", &id, &u, &v);
		add_edge(u, v, id);
		add_edge(v, u, id);
	}

	sort_edge();

	S = 0, T = V-1, ins[S] = true;
	dfs(S);

	return 0;
}
