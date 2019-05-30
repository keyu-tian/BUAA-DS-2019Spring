/*
	FileName: queue.c
	Author: Kevin
	Date: 8/04/19 15:08
	Description: implement a Server-Custom system
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MN 16384
#define MIN_Q_CNT 3
#define MAX_Q_CNT 5


typedef enum {false, true} bool;

typedef struct
{
	int arrived_time;
	int tot_waiting_time;
} Person;
Person queue[MN];
int head, tail;

int available_q_cnt;


#define get_avr_len() ((tail-head) / available_q_cnt)

void open_windows(void);
void close_windows(void);


int main()
{
	int time, T, new_man_cnt;
	bool enqueued, dequeued;

	available_q_cnt = 3;
	for (scanf("%d", &T), time=0; true; ++time)
	{
		if (time < T) scanf("%d", &new_man_cnt);
		else new_man_cnt = 0;

		enqueued = false;
		while (new_man_cnt--)
		{
			enqueued = true;
			queue[tail].arrived_time = time;
			++tail;
		}
		if (enqueued)	// may open some new window(s)
			open_windows();

		dequeued = false;
		int server_cnt = available_q_cnt;
		while (server_cnt-- && head < tail)
		{
			dequeued = true;
			queue[head].tot_waiting_time = time - queue[head].arrived_time;
			++head;
		}
		if (dequeued)	// may close some new window(s)
			close_windows();

		if (time > T && head == tail)
			break;
	}

	int i;
	for (i=0; i<tail; ++i)
		printf("%d : %d\n", i+1, queue[i].tot_waiting_time);

	return 0;
}


void open_windows(void)
{
	int avr_len;
	for (avr_len=get_avr_len(); avr_len>=7 && available_q_cnt<MAX_Q_CNT; avr_len=get_avr_len())
	{
		++available_q_cnt;
	}
}

void close_windows(void)
{
	int avr_len;
	for (avr_len=get_avr_len(); avr_len<7 && available_q_cnt>MIN_Q_CNT; avr_len=get_avr_len())
	{
		--available_q_cnt;
	}
}

