/*
	FileName: edit.c
	Author: Kevin
	Date: 8/04/19 14:38
	Description: text operation
*/

#include <stdio.h>
#include <string.h>

#include "list.h"


#define MAX_VERSION 256
#define MAX_LEN 1024


typedef enum
{
    INSERT_OP	=	1,
    ERASE_OP	=	2,
    UNDO_OP	=	3,
    EXIT_OP	=	-1
} OPER_INDEX;

typedef struct
{
	int first;
	int second;
} Pair;

typedef struct
{
	OPER_INDEX op;
	int pos, len;
	char str[MAX_LEN];
} Operation;
Operation _opers[MAX_VERSION], *opers = _opers + 11;


char temp_str[MAX_LEN];
List _strs[MAX_VERSION], *strs = _strs + 11;

Pair read_input(void);
void do_prev_opers(const int prev_n);
void do_next_opers(const int prev_n, const int next_n);


int main(void)
{
	Pair pair = read_input();
	int prev_n = pair.first, next_n = pair.second;
	do_prev_opers(prev_n);
	do_next_opers(prev_n, next_n);

	return 0;
}


Pair read_input(void)
{
	int i, prev_n;

	gets(temp_str);
	scanf("%d", &prev_n);
	for (i=-prev_n; i<0; ++i)
	{
		scanf("%d %d %s", &opers[i].op, &opers[i].pos, opers[i].str);
		opers[i].len = strlen(opers[i].str);
	}

	for (i=0; true; ++i)
	{
		scanf("%d", &opers[i].op);
		if (opers[i].op == EXIT_OP)
			break;
		if (opers[i].op != UNDO_OP)
		{
			scanf("%d %s", &opers[i].pos, opers[i].str);
			opers[i].len = strlen(opers[i].str);
		}
	}

	return	(Pair)
	{
		.first = prev_n,
		.second = i
	};
}

void do_prev_opers(const int prev_n)
{
	char *p;
	for (p=temp_str; *p; ++p)
	{
		push_back(strs, *p);
	}

	int i;
	int HEAD;
	for (HEAD=-1; HEAD>=-prev_n; --HEAD)
	{
		copy(strs+HEAD, strs+HEAD+1);
		switch (opers[HEAD].op)
		{
			case INSERT_OP:
				for (i=0; i<opers[HEAD].len; ++i)
					erase_at(strs+HEAD, opers[HEAD].pos);
				break;

			case ERASE_OP:
				if (opers[HEAD].pos == strs[HEAD].cnt)
					for (i=0; i<opers[HEAD].len; ++i)
						push_back(strs+HEAD, opers[HEAD].str[i]);
				else
					for (i=opers[HEAD].len-1; i>=0; --i)
						insert_before(strs+HEAD, opers[HEAD].pos, opers[HEAD].str[i]);
				break;

			default:
				break;
		}
	}
}

void do_next_opers(const int prev_n, const int next_n)
{
	// opers[0, next_n)
	// strs[0] -> strs[1] -> ... -> strs[next_n]

	int now = 0;
	int i, k, erase_cnt;
	for (i=0; i<next_n; ++i)
	{
		switch (opers[i].op)
		{
			case INSERT_OP:
				++now;
				copy(strs+now, strs+now-1);
				if (opers[i].pos == strs[now].cnt)
					for (k=0; k<opers[i].len; ++k)
						push_back(strs+now, opers[i].str[k]);
				else
					for (k=opers[i].len-1; k>=0; --k)
						insert_before(strs+now, opers[i].pos, opers[i].str[k]);
				break;

			case ERASE_OP:
				++now;
				copy(strs+now, strs+now-1);
				sscanf(opers[i].str, "%d", &erase_cnt);
				for (k=0; k<erase_cnt; ++k)
					if (!erase_at(strs+now, opers[i].pos))
						break;
				break;

			case UNDO_OP:
				if (now > -prev_n)
					--now;
				break;

			default:
				break;
		}
	}

	println(strs + now);
}
