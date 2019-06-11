/*
	FileName: mst.c
	Author: Kevin
	Date: 27/05/19 16:31
	Description: MST
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

#define MV 100007



int uf[MV];
int find(const int x)
{
	return uf[x] ? uf[x]=find(uf[x]) : x;
}
bool merge(int x, int y)
{
	if ((x=find(x)) == (y=find(y)))
		return false;
	return uf[x] = y, true;
}



typedef int dint;
typedef struct
{
	int u, v, id;
	dint d;
} Edge;
Edge ed[MV];

int cmp_d(const void *p, const void *q)
{
	return ((Edge*)p)->d - ((Edge*)q)->d;
}
int cmp_id(const void *p, const void *q)
{
	return ((Edge*)p)->id - ((Edge*)q)->id;
}

Edge chosen[MV];
int tot;
int kruskal(const int E)
{
	int cost = 0;
	qsort(ed, E, sizeof(*ed), cmp_d);
	int i;
	for (i=0; i<E; ++i)
		if (merge(ed[i].u, ed[i].v))
			chosen[tot++] = ed[i], cost += ed[i].d;
	return cost;
}




int main()
{
	int V, E;
	scanf("%d %d", &V, &E);
	
	int i;
	for (i=0; i<E; ++i)
		scanf("%d %d %d %d", &ed[i].id, &ed[i].u, &ed[i].v, &ed[i].d);
	
	printf("%d\n", kruskal(E));
	qsort(chosen, tot, sizeof(*chosen), cmp_id);
	
	for (i=0; i<tot; ++i)
		printf("%d ", chosen[i].id);

	return 0;
}
