#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML 50
#define MN 503


enum Oper
{
	EXIT_OP,
	INS_OP,
	SEA_OP,
	DEL_OP
};


typedef struct
{
	char name[ML];
	char author[ML];
	char pub[ML];
	char date[ML];
} Book;

int tot;
Book books[MN];


int book_cmp(const void *p, const void *q);
void book_sort(void);

void load_data(void);
void save_data(void);
void printf_book(const Book *pBook, FILE *fp);

void insert_book(void);
void search_book(void);
void delete_book(void);


int main(int argc, char *argv[])
{
	load_data();

	int op;
	while (scanf("%d", &op), op != EXIT_OP)
	{
		switch (op)
		{
			case INS_OP:
				insert_book();
				break;

			case SEA_OP:
				search_book();
				break;

			case DEL_OP:
				delete_book();
				break;
		}
	}

	save_data();

	return 0;
}


int book_cmp(const void *p, const void *q)
{
	return strcmp((char *)p, (char *)q);
}

void book_sort(void)
{
	qsort(books, tot, sizeof(*books), book_cmp);
}

void load_data(void)
{
	tot = 0;
	const char *FIN = "books.txt";
	FILE *fin = fopen(FIN, "r");

	while (fscanf(fin, "%s %s %s %s", books[tot].name, books[tot].author, books[tot].pub, books[tot].date) == 4)
	{
		++tot;
	}

	book_sort();

	fclose(fin);
}

void save_data(void)
{
	const char *FOUT = "ordered.txt";
	FILE *fout = fopen(FOUT, "w");

	int i;
	for (i=0; i<tot; ++i)
	{
		printf_book(books+i, fout);
	}
}

void insert_book(void)
{
	Book newBook;
	scanf("%s %s %s %s", newBook.name, newBook.author, newBook.pub, newBook.date);
	books[tot++] = newBook;
	book_sort();
}

void printf_book(const Book *pBook, FILE *fp)
{
	fprintf(fp, "%-50s%-20s%-30s%-10s\n", pBook->name, pBook->author, pBook->pub, pBook->date);
}

void search_book(void)
{
	char key_word[ML];
	scanf("%s", key_word);

	int i;
	for (i=0; i<tot; ++i)
	{
		if (strstr(books[i].name, key_word))
		{
			printf_book(books+i, stdout);
		}
	}
}

void delete_book(void)
{
	char key_word[ML];
	scanf("%s", key_word);

	int i, j;
	for (i=0; i<tot; ++i)
	{
		if (strstr(books[i].name, key_word))
		{
			for (j=i; j<tot-1; ++j)
			{
				books[j] = books[j+1];
			}
			--tot;
			--i;
		}
	}
}


