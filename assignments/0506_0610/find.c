/*
	FileName: find.c 
	Author: Kevin
	Date: 03/06/19 17:05
	Description: binary search
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


#define ML 25
#define MC 257
#define MN 3600
#define NHASH  3001
#define MULT  37


int words_cnt;
char words[MN][ML];

int begin[MC], end[MC];

int cmp_time;


typedef unsigned int hint;
typedef struct _Node
{
	struct _Node *next, *prev;
	const char *s;
} Node;
typedef struct
{
	Node *head, *tail;
	int cnt;
} List;
List hash[NHASH];


hint get_hash_code(const char *s);

void push_first(List *pl, const char *s);
void push_back(List *pl, const char *s);
void insert(const char *s);



int naive_search(const char *s);
int naive_binary_search(const char *s);
int hash_binary_search(const char *s);
int hash_search(const char *s);



int main()
{
	memset(begin, -1, sizeof(begin));

	FILE *fin = fopen("dictionary3000.txt", "r");
	while (fscanf(fin, "%s", words[words_cnt]) == 1)
	{
		if (begin[words[words_cnt][0]] == -1)
			begin[words[words_cnt][0]] = words_cnt;
		end[words[words_cnt][0]] = words_cnt;
		
		insert(words[words_cnt]);
		++words_cnt;
	}
		
	static char word[ML];
	int mode, found;
	while (~scanf("%s %d", word, &mode))
	{
		cmp_time = 0;
		switch (mode)
		{
			case 1:
				found = naive_search(word);
				printf("%d %d\n", found, cmp_time);
				break;
			case 2:
				found = naive_binary_search(word);
				printf("%d %d\n", found, cmp_time);
				break;
			case 3:
				found = hash_binary_search(word);
				printf("%d %d\n", found, cmp_time);
				break;
			case 4:
				found = hash_search(word);
				printf("%d %d\n", found, cmp_time);
				break;
		}
	}

#ifdef _KEVIN
	system("pause");
#endif

	return 0;
}


hint get_hash_code(const char *s)
{
	unsigned int h;
	for(h=0; *s; ++s)
		h = MULT*h + *s;

	return h % NHASH;
}

void push_first(List *pl, const char *s)
{
	pl->head = pl->tail = (Node *)malloc(sizeof(Node));
	pl->head->next = pl->head->prev = NULL;
	pl->head->s = s;
}
void push_back(List *pl, const char *s)
{
	if (pl->cnt)
	{
		Node *p_new = (Node *)malloc(sizeof(Node));
		p_new->prev = pl->tail, p_new->next = NULL, p_new->s = s;
		pl->tail = pl->tail->next = p_new;
	}
	else
		push_first(pl, s);
	++pl->cnt;
}

void insert(const char *s)
{
	hint hc = get_hash_code(s);
	push_back(hash+hc, s);
}




int naive_search(const char *s)
{
	int i;
	for (i=0; i<words_cnt; ++i)
	{
		int cmp = strcmp(words[i], s);
		++cmp_time;
		if (cmp == 0)
			return 1;
		if (cmp > 0)
			return 0;
	}
	return 0;
}
int naive_binary_search(const char *s)
{
	int l = 0, r = words_cnt-1;
	while (l <= r)
	{
		int mid = (l+r) >> 1;
		int cmp = strcmp(words[mid], s);
		++cmp_time;
		if (cmp == 0)
			return 1;
		if (cmp < 0)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return 0;
}
int hash_binary_search(const char *s)
{
	int l = begin[s[0]], r = end[s[0]];
	if (l==-1 || r==-1)
		return 0;

	while (l <= r)
	{
		int mid = (l+r) >> 1;
		int cmp = strcmp(words[mid], s);
		++cmp_time;
		if (cmp == 0)
			return 1;
		if (cmp < 0)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return 0;
}
int hash_search(const char *s)
{
	hint hc = get_hash_code(s);
	Node *p;
	for (p=hash[hc].head; p; p=p->next)
	{
		int cmp = strcmp(p->s, s);
		++cmp_time;
		if (cmp == 0)
			return 1;
		if (cmp > 0)
			return 0;
	}
	return 0;
}

