#include <stdio.h>
#include <string.h>

#define ML 99

int main()
{
	int i, len;
	char input[2][ML], buf[3][ML], *p_num[2], *p_ans;

	scanf("%s%s", input[0], input[1]);
	sprintf(buf[0], "%82s", input[0]);
	sprintf(buf[1], "%82s", input[1]);
	for (i=0; buf[0][i]==' '; buf[0][i++]='0');
	for (i=0; buf[1][i]==' '; buf[1][i++]='0');

	for (p_num[0]=buf[0], p_num[1]=buf[1]; *p_num[0]=='0' && *p_num[1]=='0'; ++p_num[0], ++p_num[1]);

	if (strcmp(p_num[0], p_num[1]) == 0)
		return putchar('0'), 0;

	if (strcmp(p_num[0], p_num[1]) < 0)
	{
		char *temp = p_num[0];
		p_num[0] = p_num[1];
		p_num[1] = temp;

		putchar('-');
	}

	len = strlen(p_num[0]);
	for (p_ans=buf[2], i=len-1; i>=0; --i)
	{
		p_ans[i] = p_num[0][i] - p_num[1][i];
		if (p_ans[i] < 0)
		{
			p_ans[i] += 10;
			--p_num[0][i-1];
		}
	}

	for (i=0; p_ans[i]==0; ++i);
	for (; i<len; ++i)
		printf("%d", p_ans[i]);

	return 0;
}
