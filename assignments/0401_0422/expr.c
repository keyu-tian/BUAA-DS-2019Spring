/*
	FileName: expr.c 
	Author: Kevin
	Date: 8/04/19 12:33
	Description: calculate the result of a given expression
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ML 2333

char buf[ML], *cur = buf;

void read_string(void);
int get_num(void), get_fact(void), calc_term(void), calc_expr(void);


int main()
{
	read_string();
	printf("%d", calc_expr());

	return 0;
}


void read_string(void)
{
	char *p, *q;

	scanf("%[^\n]", buf);
	for (p = q = buf; *p != '\0'; ++p)
		if (!strchr("=\n\r\t ", *p))
			*q++ = *p;
	*q = '\0';
}

int get_num(void)
{
	int ret = 0, sign = 1;
	if (*cur == '-')
	{
		++cur;
		sign = -1;
	}

	while (isdigit(*cur))
	{
		ret *= 10;
		ret += *cur - '0';
		++cur;
	}

	return sign * ret;
}

int get_fact(void)
{
	int ret = 0;
	if (*cur == '(')
	{
		++cur; // '('
		ret = calc_expr();
		++cur; // ')'
	}
	else
	{
		ret = get_num();
	}
	return ret;
}

int calc_term(void)
{
	int ret = get_fact();
	while (*cur == '*' || *cur == '/' || *cur == '%')
	{
		char op = *cur++;
		int next = get_fact();
		if (op == '*')
			ret *= next;
		else if (op == '/')
			ret /= next;
		else
			ret %= next;
	}
	return ret;
}

int calc_expr(void)
{
	int ret = calc_term();
	while (*cur == '+' || *cur == '-')
	{
		char op = *cur++;
		int next = calc_term();
		if (op == '+')
			ret += next;
		else
			ret -= next;
	}
	return ret;
}

