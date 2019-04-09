/*
	FileName: monkey.c 
	Author: Kevin
	Date: 25/03/19 12:33
	Description: Josephus Problem
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	int i, n, m, k, r;
	scanf("%d %d %d", &n, &m, &k);

	for (i=1, r=0; i<=n; ++i)
		r = (r+m) % i;

	printf("%d", (r+k-1) % n + 1);

	return 0;
}
