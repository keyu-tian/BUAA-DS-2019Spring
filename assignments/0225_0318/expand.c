#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ML 99

int same_type(const char a, const char b)
{
	return (islower(a) && islower(b))
		|| (isupper(a) && isupper(b))
		|| (isdigit(a) && isdigit(b));
}

int main()
{
	int i, len;
	char _s[ML] = "", *s = _s+1, c;

	scanf("%s", s);

	for (i=0, len=strlen(s); i<len; ++i)
	{
		if (s[i] == '-')
		{
			if (s[i-1] < s[i+1] && same_type(s[i-1], s[i+1]))
			{
				for (c=s[i-1]+1; c<s[i+1]; ++c)
				{
					putchar(c);
				}
			}
			else
			{
				putchar('-');
			}
		}
		else
		{
			putchar(s[i]);
		}
	}

	return 0;
}
