#include <stdio.h>
#include <string.h>

#define R 19
#define C 19
#define DIR 8

#define valid(r, c) (r>=0 && r<R && c>=0 && c<C)

int board[R][C];
const int dr[DIR] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dc[DIR] = {0, 0, -1, 1, -1, 1, -1, 1};

int check(const int cur_r, const int cur_c)
{
	int win_player = 0;

	int cur_player = board[cur_r][cur_c];
	if (cur_player)
	{
		int i, j, r, c;
		for (i=0; i<DIR; ++i)
		{
			int cnt = 0, blank = 0;
			r = cur_r, c = cur_c;
			for (j=0; j<3; ++j)
			{
				r += dr[i], c += dc[i];
				if (valid(r, c) && board[r][c] == cur_player)
				{
					++cnt;
				}
				else
				{
					break;
				}
			}
			r = cur_r + 4 * dr[i], c = cur_c + 4 * dc[i];
			if (valid(r, c) && board[r][c] == 0)
			{
				blank = 1;
			}
			r = cur_r - dr[i], c = cur_c - dc[i];
			if (valid(r, c) && board[r][c] == 0)
			{
				blank = 1;
			}

			if (cnt == 3 && blank)
			{
				win_player = cur_player;
				break;
			}
		}
	}

	return win_player;
}


int main()
{
	int r, c;
	for (r=0; r<R; ++r)
	{
		for (c=0; c<C; ++c)
		{
			scanf("%d", board[r]+c);
		}
	}

	int found = 0;
	for (r=0; r<R && !found; ++r)
	{
		for (c=0; c<C && !found; ++c)
		{
			if (check(r, c))
			{
				found = 1;
				printf("%d:%d,%d\n", board[r][c], r+1, c+1);
			}
		}
	}

	if (!found)
	{
		puts("No");
	}

	return 0;
}
