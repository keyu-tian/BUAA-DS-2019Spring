/*
	FileName: article.c
	Author: Kevin
	Date: 03/06/19 18:45
	Description: brace-matching
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ML 55
#define MN 1007


typedef struct
{
	int id, seat;
	char name[ML];
} Node;


int n;
Node a[MN];


int cmp_multi(const void *p, const void *q)
{
	Node *a = (Node *)p, *b = (Node *)q;
	return a->seat != b->seat ? a->seat - b->seat : a->id - b->id;
}
int cmp_id(const void *p, const void *q)
{
	return ((Node *)p)->id - ((Node *)q)->id;
}



void read_file()
{
	FILE *fin = fopen("in.txt","r");
	scanf("%d", &n);
	int i;
	for (i=0; i<n; i++)
		fscanf(fin, "%d %s %d", &a[i].id, a[i].name, &a[i].seat);
	qsort(a, n, sizeof(*a), cmp_multi);
	fclose(fin);
}


void write_ans()
{
	FILE *fout = fopen("out.txt","w");
	qsort(a ,n, sizeof(*a), cmp_id);
	int i;
	for (i=0; i<n; i++)
		fprintf(fout,"%d %s %d\n", a[i].id, a[i].name, a[i].seat);
	fclose(fout);
}


void check_first()
{
	if (a->seat!=1)
	{
		a[n-1].seat = 1;
		qsort(a, n, sizeof(*a), cmp_multi);
	}
}
void check_all()
{
	int i;
	for (i=0; i<n-1; i++)
	{
		if (a[i].seat != a[i+1].seat)
		{
			if (a[i+1].seat != a[i].seat+1)
			{
				a[n-1].seat = a[i].seat+1;
				qsort(a, n, sizeof(*a), cmp_multi);
			}
		}
	}
	for (i=0; i<n-1; i++)
	{
		if (a[i].seat == a[i+1].seat)
		{
			a[i+1].seat = a[n-1].seat+1;
			qsort(a, n, sizeof(*a), cmp_multi);
		}
	}
}


int main()
{
	read_file();
	
	check_first();
	check_all();

	write_ans();

	return 0;
}

