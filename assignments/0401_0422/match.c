/*
	FileName: article.c
	Author: Kevin
	Date: 8/04/19 11:19
	Description: brace-matching
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 16384

char buf[MAX_LEN];

struct StackNode
{
	char c;
	int line;
} output_stack[MAX_LEN], match_stack[MAX_LEN];
int out_top, match_top;


void read_buf(void);
void erase_useless_braces(void);


int main()
{
	read_buf();
	erase_useless_braces();
	int line;
	char *p;

	for (p=buf, line=1; *p; ++p)
	{
		switch (*p)
		{
			case '\n':
				++line;
				break;

			case '(':
				output_stack[out_top].c = *p, output_stack[out_top++].line = line;
				match_stack[match_top].c = *p, match_stack[match_top++].line = line;
				break;

			case ')':
				if (!match_top || match_stack[match_top-1].c != '(')
					return printf("without maching \')\' at line %d", line), 0;
				output_stack[out_top].c = *p, output_stack[out_top++].line = line;
				--match_top;
				break;

			case '{':
				if (match_top && match_stack[match_top-1].c == '(')
					return printf("without maching \'(\' at line %d", match_stack[match_top-1].line), 0;
				output_stack[out_top].c = *p, output_stack[out_top++].line = line;
				match_stack[match_top].c = *p, match_stack[match_top++].line = line;
				break;

			case '}':
				if (!match_top || match_stack[match_top-1].c != '{')
					return printf("without maching \'}\' at line %d", line), 0;
				output_stack[out_top].c = *p, output_stack[out_top++].line = line;
				--match_top;
				break;
		}
	}

	if (match_top)
		return printf("without maching \'%c\' at line %d", match_stack[match_top-1].c, match_stack[match_top-1].line), 0;

	int i;
	for (i=0; i<out_top; ++i)
		putchar(output_stack[i].c);

	return 0;
}


void read_buf(void)
{
	const char *FIN = "example.c";
	FILE *fin = fopen(FIN, "rb");

	fseek(fin, 0, SEEK_END);
	int bytes = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	fread(buf, bytes, 1, fin);

	fclose(fin);
}


#define erase_until(BEGIN, FLAG_STR) \
	do \
	{ \
		for (end = strstr(BEGIN, FLAG_STR); p<end; ++p) \
		{ \
			if (strchr("(){}<>[]", *p)) \
				*p = '?'; \
		} \
	} while (0)

void erase_useless_braces(void)
{
	char *p, *end;
	for (p=buf; *p; ++p)
	{
		if (p[0] == '/' && p[1] == '/')
			erase_until(p+2, "\n");
		else if (p[0] == '/' && p[1] == '*')
			erase_until(p+2, "*/");
		else if (p[0] == '\'')
			erase_until(p+1, "\'");
		else if (p[0] == '\"')
			erase_until(p+1, "\"");
	}
}

