/*
	FileName: line.c 
	Author: Kevin
	Date: 25/03/19 12:27
	Description: find the longest connected segmemts(by using the DSU)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MN 133
#define equal(p1, p2) (p1.x==p2.x && p1.y==p2.y)

typedef struct
{
	int x;
	int y;
} Point;
typedef struct
{
	Point src;
	Point dest;
} Segment;
Segment segs[MN];

int uf[MN];
int find(const int x)
{
	if (uf[x] >= 0)
		return uf[x] = find(uf[x]);
	return x;
}
void merge(const int x, const int y)
{
	int r1 = find(x), r2 = find(y);
	if (r1 < r2)
		uf[r1] += uf[r2], uf[r2] = r1;
	else if(r2 < r1)
		uf[r2] += uf[r1], uf[r1] = r2;
}


int main(void)
{
	int i, j, n;
	scanf("%d", &n);
	memset(uf, -1, sizeof(*uf) * (n+1));
	for (i=0; i<n; ++i)
	{
		scanf("%d %d %d %d", &segs[i].src.x, &segs[i].src.y, &segs[i].dest.x, &segs[i].dest.y);
		for (j=0; j<i; ++j)
		{
			if (equal(segs[i].src, segs[j].dest) || equal(segs[i].dest, segs[j].src))
				merge(i, j);
		}
	}

	int max_idx = 0;
	for (i=1; i<n; ++i)
	{
		if (-uf[i] > -uf[max_idx])
			max_idx = i;
	}

	Point src = segs[max_idx].src;
	for (i=1; i<n; ++i)
	{
		if (uf[i] == max_idx && segs[i].src.x < src.x)
			src = segs[i].src;
	}

	printf("%d %d %d", -uf[max_idx], src.x, src.y);

	return 0;
}
