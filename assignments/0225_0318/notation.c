#include <stdio.h>
#include <string.h>

#define ML 107

int main()
{
	char integer[ML] = "", decimal[ML] = "", zeros[ML] = "";

	scanf("%[^.].%[0]", integer, zeros);
	scanf("%s", decimal);

	if (integer[0] == '0')
	{
		putchar(*decimal);
		if (strlen(decimal) > 1)
			printf(".%s", decimal+1);
		printf("e-%d", (int)strlen(zeros) + 1);
	}
	else
	{
		printf("%c.%s%s%se%d", *integer, integer+1, zeros, decimal, (int)strlen(integer) - 1);
	}

	return 0;
}

