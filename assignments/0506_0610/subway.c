/*
	FileName: subway.c
	Author: Kevin
	Date: 27/05/19 16:44
	Description: Dijkstra or SPFA or Floyd
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {false, true} bool;
#define MLINE 20
#define ML 50
#define MV 300

int V;
char station_name[MV][ML];
int get_id(const char *this_name);


int line[MV][MV];
int dist[MV][MV], INF = 0x3f3f3f3f;
void build_graph(void);
void floyd(void);
void print_path(const int src, const int dest);


int main()
{
	char src_name[ML], dest_name[ML];
	scanf("%s %s", src_name, dest_name);

	build_graph();
	floyd();
	print_path(get_id(src_name), get_id(dest_name));

	return 0;
}


int get_id(const char *this_name)	// valid range: [1, V]
{
	int id;
	bool found = false;
	for (id=1; id<=V; ++id)
	{
		if (strcmp(this_name, station_name[id]) == 0)
		{
			found = true;
			break;
		}
	}

	if (!found)
		strcpy(station_name[id=++V], this_name);

	return id;
}


void build_graph()
{
	FILE *fin = fopen("bgstations.txt", "r");

	int line_id, num_of_lines, num_of_stations;
	char this_name[ML];

	fscanf(fin, "%d", &num_of_lines);
	while (num_of_lines--)
	{
		fscanf(fin, "%d %d", &line_id, &num_of_stations);
		int prev_id = -1, id;
		while (num_of_stations--)
		{
			fscanf(fin, "%s %*d", this_name);
			id = get_id(this_name);

			if (~prev_id)
			{
				dist[prev_id][id] = dist[id][prev_id] = 1;
				line[prev_id][id] = line[id][prev_id] = line_id;
			}

			prev_id = id;
		}
	}

	fclose(fin);
}


int path[MV][MV];
void floyd(void)
{
	int i, j, k;

	for (i=1; i<=V; ++i)
		for (j=1; j<=V; ++j)
			if (!dist[i][j] && i!=j)
				dist[i][j] = INF;

	for (k=1; k<=V; ++k)
		for (i=1; i<=V; ++i)
			for (j=1; j<=V; ++j)
				if (dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j], path[i][j] = k;
}


int sta[MV], top;
void get_path(const int src, const int dest)
{
	if (!path[src][dest])
		sta[top++] = src;
	else
		get_path(src, path[src][dest]), get_path(path[src][dest], dest);
}
void print_path(const int src, const int dest)
{
	top = 0;
	get_path(src, dest);
	sta[top++] = dest;

	printf("%s", station_name[src]);
	int i, j;
	for (i=0; i<top-1; i=j)
	{
		int cur_line = line[sta[i]][sta[i+1]];
		for (j=i+1; j+1<top && line[sta[j]][sta[j+1]]==cur_line; ++j);
		printf("-%d(%d)-%s", cur_line, j-i, station_name[sta[j]]);
	}
}

