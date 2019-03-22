#include <stdio.h>
#include <ctype.h>

#define ML 2333

char buf[ML], *cur = buf;

void ReadExpr(void)
{
	char *p, *q;

	scanf("%[^\n]", buf);
	for (p = q = buf; *p != '\0'; ++p)
		if (*p != ' ' && *p != '=')
			*q++ = *p;
	*q = '\0';
}

int ScanNumber(void)
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

int CalcFactor(void)
{
	int ret = ScanNumber();
	while (*cur == '*' || *cur == '/')
	{
		char op = *cur++;
		int next = ScanNumber();
		if (op == '*')
			ret *= next;
		else
			ret /= next;
	}
	return ret;
}

int CalcExpr(void)
{
	int ret = CalcFactor();
	while (*cur == '+' || *cur == '-')
	{
		char op = *cur++;
		int next = CalcFactor();
		if (op == '+')
			ret += next;
		else
			ret -= next;
	}
	return ret;
}

int main()
{
	ReadExpr();
	printf("%d", CalcExpr());

	return 0;
}
