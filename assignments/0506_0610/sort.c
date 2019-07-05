/*
	FileName: queue.c
	Author: Kevin
	Date: 03/06/19 19:11
	Description: sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MN 1003


int a[MN], cnt;


void quickSort(int *b, int left, int right)
{
	if (left < right)
	{
		int i, last;
		for (last=left, i=last+1; i<=right; i++)
		{
			if (b[i] < b[left])
			{
				++last;
				{
					int temp = b[last];
					b[last] = b[i];
					b[i] = temp;
				}
			}
			++cnt;
		}
		{
			int temp = b[left];
			b[left] = b[last];
			b[last] = temp;
		}
		
		quickSort(b, left, last-1);
		quickSort(b, last+1, right);
	}
}


void merge(int *b, int left, int begin, int end)
{
	static int tmp[MN];
	int i = left, j = begin, q = left;
	for (++j; i<=begin && j<=end; ++cnt)
		tmp[q++] = b[i]<b[j] ? b[i++] : b[j++];
	while (i<=begin)
		tmp[q++] = b[i++];
	while (j<=end)
		tmp[q++] = b[j++];
	for(i=left; i<=end; i++)
		b[i] = tmp[i];
}
void mergeSort(int *b, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) >> 1;
		mergeSort(b, left, mid);
		mergeSort(b, mid+1, right);
		merge(b, left, mid, right);
	}
	else
		return;
}


void heapadjust(int *h, int ik, int nk)
{
	int j, tempk = h[ik];
	j = 2*ik + 1;
	while (j < nk)
	{
		if (j+1<nk && h[j]<h[j+1])
			++j;
		if (tempk < h[j])
		{
			h[(j-1)/2] = h[j];
			j = 2*j+1;
			cnt++;
		}
		else
		{
			cnt++;
			break;
		}
	}
	h[(j-1) >> 1] = tempk;
}
void buildHeap(int *b, int n)
{
	int i;
	for(i = n/2-1; i >= 0; i--)
		heapadjust(b, i, n);
}
void heapSort(int *b, int n)
{
	if (n < 1)
		return;
	buildHeap(b, n);
	int i;
	for(i = n-1; i > 0; i--)
	{
		{
			int temp = b[i];
			b[i] = b[0];
			b[0] = temp;
		}
		heapadjust(b, 0, i);
	}
}


void bubbleSort(int *b, int n)
{
	if (n < 1)
		return;
	int i, j, swapped;
	for (i = n-1; i > 0; i--)
	{
		swapped = 0;
		for (j = 0; j < i; j++)
		{
			if (b[j] > b[j+1])
			{
				{
					int temp = b[j];
					b[j] = b[j+1];
					b[j+1] = temp;
					swapped = 1;
				}
			}
			cnt++;
		}
		if (!swapped)
			break;
	}
}


void selectSort(int *b, int n)
{
	if (n < 1)
		return;
	int i, j, t;
	for(i = 0; i < n-1; i++)
	{
		t = i;
		for(j = i+1; j < n; j++)
		{
			if(b[t] > b[j])
			{
				t = j;
			}
			cnt++;
		}
		{
			int temp = b[i];
			b[i] = b[t];
			b[t] = temp;
		}
	}
}




int main()
{
	int n, op;
	scanf("%d %d", &n, &op);
	
	int i;
	for (i=0; i<n; i++)
		scanf("%d", a+i);
	switch (op)
	{
		case 1:selectSort(a, n);break;
		case 2:bubbleSort(a, n);break;
		case 3:heapSort(a, n);break;
		case 4:mergeSort(a, 0, n-1);break;
		case 5:quickSort(a, 0, n-1);break;
	}
	for (i=0; i<n; i++)
		printf("%d ", a[i]);
	printf("\n%d", cnt);

	return 0;
}
