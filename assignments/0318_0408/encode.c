/*
	FileName: encode.c 
	Author: Kevin
	Date: 25/03/19 13:24
	Description: encode a string(implementation)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ML 6666
#define KEY_LEN 95

const char *FIN = "in.txt";
const char *FOUT = "in_crpyt.txt";

int exist[1 << 8];
char code[1 << 8];

char ins[ML], outs[ML];
char key[ML];

void get_key(void)
{
	char *p, ch;
	scanf("%[^\n]", key);
	int top = strlen(key), i;

	for (p=key, i=0; i<top; ++i)
	{
		if (!exist[(int)key[i]])
		{
			exist[(int)key[i]] = 1;
			*p++ = (int)key[i];
		}
	}

	top = p - key;
	for (ch=32; ch<=126; ++ch)
	{
		if (!exist[(int)ch])
		{
			key[top++] = ch;
		}
	}
	key[top] = '\0';
}


struct Node
{
	int l, r;
	char ch;
} list[ML];

void erase(int p)
{
	list[list[p].l].r = list[p].r;
	list[list[p].r].l = list[p].l;
}

void gener_code(void)
{
	int i, p, times;
	int before = 0, after = 0;

	for (i=0; i<KEY_LEN; ++i)
		list[i].l = (KEY_LEN+i-1) % KEY_LEN, list[i].r = (i+1) % KEY_LEN, list[i].ch = key[i];

	p = 0;
	while (list[p].l != p)
	{
		before = list[p].ch;
		erase(p);

		times = before;
		while (times--)
			p = list[p].r;

		after = list[p].ch;
		code[before] = after;
	}
	code[after] = list[0].ch;
}


int main()
{
	FILE *fin = fopen(FIN, "rb");
	FILE *fout = fopen(FOUT, "wb");

	fseek(fin, 0, SEEK_END);
	int bytes = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	fread(ins, bytes, 1, fin);

	get_key();
	gener_code();

	int i;
	for (i=0; i<bytes; ++i)
	{
		if (code[(int)ins[i]])
			outs[i] = code[(int)ins[i]];
		else
			outs[i] = ins[i];
	}
	fwrite(outs, bytes, 1, fout);

	fclose(fin);
	fclose(fout);
	return 0;
}
