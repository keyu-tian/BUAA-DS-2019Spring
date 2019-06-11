/*
	FileName: graphSearch.c
	Author: Kevin
	Date: 27/05/19 16:23
	Description: bfs & dfs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MV 203
#define SRC 0

typedef enum {false, true} bool;


int V;
bool g[MV][MV];
bool vis[MV];

void dfs(const int u)
{
	printf("%d ", u);
	int v;
	for (v=0; v<V; ++v)
		if (g[u][v] && !vis[v])
			vis[v] = true, dfs(v);
}


void bfs(const int src)
{
	static int q[MV];
	int hd = 0, tl = 0;
	vis[q[tl++]=src] = true;
	
	while (hd != tl)
	{
		const int u = q[hd++];
		printf("%d ", u);
		int v;
		for (v=0; v<V; ++v)
			if (g[u][v] && !vis[v])
				vis[q[tl++]=v] = true;
	}
}


int main()
{
	int E;
	scanf("%d %d", &V, &E);
	
	int u, v;
	while (E--)
	{
		scanf("%d %d", &u, &v);
		g[u][v] = g[v][u] = true;
	}
	
	memset(vis, false, sizeof(*vis) * (V));
	vis[SRC] = true, dfs(SRC);
	puts("");
	memset(vis, false, sizeof(*vis) * (V));
	bfs(SRC);
	puts("");
	
	scanf("%d", &u);
	for (v=0; v<V; ++v)
		g[u][v] = g[v][u] = false;

	memset(vis, false, sizeof(*vis) * (V));
	vis[SRC] = true, dfs(SRC);
	puts("");
	memset(vis, false, sizeof(*vis) * (V));
	bfs(SRC);
	puts("");

	return 0;
}

