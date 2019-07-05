/*
	FileName: bst.c
	Author: Kevin
	Date: 13/05/19 19:13
	Description: Huffman-code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML 65536
#define bint unsigned long
#define test(x, k) !!(((x) >> k) & 1u)
#define set(x, k) ((x) |= 1u << k)
#define reset(x, k) ((x) &= ~(1u << k))


int buf_len;
char buf[ML << 1];


typedef enum {false, true} bool;
typedef struct
{
	bint code;
	char code_len;
	bool vis;
	int weight;
	int lc, rc;
} Node;
Node _t[ML], *t = _t+1;
int tot;

typedef struct
{
	int first;
	int second;
} pair;


void init()
{
	t['\0'].weight = 1;
	t[-1].weight = 0x3f3f3f3f;
	tot = 128;
}


void count()
{
	char *p, *q;
	for (p=q=buf; *p; ++p)
		if (*p != '\n' && *p != '\r')
			*q++ = *p, ++t[*p].weight;

	*q++ = '\0';	// valid '\0'
	buf_len = q - buf;

	int i;
	for (i=0; i<=tot; ++i)
		if (t[i].weight == 0)
			t[i].vis = true;
}


pair find_min2()
{
	pair min2 = {.first = -1, .second = -1};

	int i;
	for (i=0; i<=tot; ++i)
	{
		if (!t[i].vis && t[i].weight < t[min2.second].weight)
		{
			min2.second = i;
			if (t[min2.second].weight < t[min2.first].weight)
			{
				int tp = min2.first;
				min2.first = min2.second;
				min2.second = tp;
			}
		}
	}

	return min2;
}


void code()
{
	pair min2;
	int u, v;
	while (min2=find_min2(), (u=min2.first) != -1 && (v=min2.second) != -1)
	{
		int new_node = ++tot;
		t[new_node].lc = u;
		t[new_node].rc = v;
		t[new_node].weight = t[u].weight + t[v].weight;

		t[u].vis = t[v].vis = true;
	}
}



bint cur_code;
int cur_code_len;
void dfs(const int u)
{
	if (t[u].lc == 0 && t[u].rc == 0)	// leaf
	{
		t[u].code = cur_code;
		t[u].code_len = cur_code_len;
	}
	else	// must have 2 sons (cuz Huffman Tree must be a full binary tree!)
	{
		++cur_code_len, dfs(t[u].lc), --cur_code_len;

		set(cur_code, cur_code_len);
		++cur_code_len, dfs(t[u].rc), --cur_code_len;
		reset(cur_code, cur_code_len);
	}
}


bool stack[ML];
int top;
void write_node(const Node node)
{
	int k;
	for (k=0; k<node.code_len; ++k)
		stack[top++] = test(node.code, k);
}
void write_ans(FILE *fout)
{
	top = 0;
	Node node;
	int i;
	for (i=0; i<buf_len; ++i)
		write_node(t[buf[i]]);

	int res = top % 8;
	if (res)
		top += 8-res;

	int k;
	for (i=0; i<top; i+=8)
	{
		bint bits = 0;
		for (k=0; k<8; ++k)
			if (stack[i+k])
				set(bits, (8-1-k));
		printf("%x", bits);
		fputc(bits, fout);
	}
}


int main()
{
	const char *FIN = "input.txt", *FOUT = "output.txt";

	FILE *fin = fopen(FIN, "rb");
	FILE *fout = fopen(FOUT, "w");

	fseek(fin, 0, SEEK_END);
	buf_len = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	fread(buf, buf_len, 1, fin);

	init();
	count();
	code();
	cur_code_len = 0, dfs(tot);
	write_ans(fout);

	fclose(fin);
	fclose(fout);


#ifdef _VSC_KEVIN
	system("pause");
#endif
	return 0;
}

