#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ML 33
#define MN 105


typedef struct
{
	char name[ML];
	int order;
	long long tel;
} Person;

Person person[MN];


int person_cmp(const void *p, const void *q)
{
	Person *a = (Person *)p, *b = (Person *)q;
	int flag = strcmp(a->name, b->name);
	if (flag == 0)
		flag = a->order - b->order;
	return flag;
}


Person *unique(Person *begin, Person *end)
{
	Person *left, *right;
	for (left=begin, right=begin+1; right!=end; ++right)
	{
		if (strcmp(left->name, right->name) != 0 || left->tel != right->tel)
		{
			if (left+1 != right)
			{
				*++left = *right;
			}
			else
			{
				++left;
			}
		}
	}

	return left+1;
}


void add_index(Person *begin, Person *end)
{
	Person *left, *right;
	int cnt = 0;
	char index_buf[ML];

	for (left=begin, right=begin+1; right!=end; ++right)
	{
		if (strcmp(left->name, right->name) == 0)
		{
			sprintf(index_buf, "_%d", ++cnt);
			strcat(right->name, index_buf);
		}
		else
		{
			cnt = 0;
			left = right;
		}
	}
}


int main()
{
	int i, n;
	scanf("%d", &n);

	for (i=0; i<n; ++i)
	{
		scanf("%s %lld", person[i].name, &person[i].tel);
		person[i].order = i;
	}

	qsort(person, n, sizeof(*person), person_cmp);
	n = unique(person, person+n) - person;
	add_index(person, person+n);

	for (i=0; i<n; ++i)
	{
		printf("%s %lld\n", person[i].name, person[i].tel);
	}

	return 0;
}

