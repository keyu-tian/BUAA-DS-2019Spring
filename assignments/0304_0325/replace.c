#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML 10000

const char *FIN = "filein.txt";
const char *FOUT = "fileout.txt";

char ins[ML], outs[ML];
char s[ML], d[ML];


int replace(void)
{
	char *p;
	int top = 0;
	scanf("%s %s", s, d);
	int len_s = strlen(s), len_d = strlen(d), i;

	for (p=ins; *p; ++p)
	{
		if (!strncasecmp(p, s, len_s))
		{
			p += len_s - 1;
			for (i=0; i<len_d; ++i)
			{
				outs[top++] = d[i];
			}
		}
		else
		{
			outs[top++] = *p;
		}
	}
	outs[top] = '\0'; // 注意不能写成outs[top++]='\0'，因为有效字符数是top，outs[top]这个位置就是第top+1个字符就应该是0
	// 如果写成outs[top++]='\0'，那么在这之后top就比有效字符数多1了，fwrite就多写了一个'\0'，有可能就在末尾多了一个空格

	return top;
}


int main()
{
	FILE *fin = fopen(FIN, "rb");
	FILE *fout = fopen(FOUT, "wb");

	fseek(fin, 0, SEEK_END);
	int bytes = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	fread(ins, bytes, 1, fin);

	bytes = replace();

	fwrite(outs, bytes, 1, fout);

	fclose(fin);
	fclose(fout);
	return 0;
}
