#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ML 666

const char *FIN = "encrypt.txt";
const char *FOUT = "output.txt";

int exist[1 << 7];

char key[ML], ins[ML], outs[ML];


int replace(void)
{
	char *p, ch;
	scanf("%s", key);
	int top = strlen(key), i;

	for (p=key, i=0; i<top; ++i)
	{
		if (!exist[(int)key[i]])
		{
			exist[(int)key[i]] = 1;
			*p++ = key[i];
		}
	}
	top = p - key;
	key[top] = '\0';

	for (ch='z'; ch>='a'; --ch)
	{
		if (!exist[(int)ch])
		{
			key[top++] = ch;
		}
	}
	key[top] = '\0';

	top = 0;
	for (p=ins; *p; ++p)
	{
		outs[top++] = islower(*p) ? key[*p - 'a'] : *p;
	}
	outs[top] = '\0';

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

