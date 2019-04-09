#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LL long long

#ifdef _KEVIN
#define MAX_DLEN 100000
#define MAX_DCNT 10000
#define MAX_ALEN 400000
#define MAX_ACNT 50000
#else
#define MAX_DLEN 6000000
#define MAX_DCNT 800000
#define MAX_ALEN 8000000
#define MAX_ACNT 1000000
#endif

#define TABLE_SIZE MOD1+1

#define MOD1 950269
//#define MOD2 9999971



typedef struct _DNode
{
	struct _DNode *next;
	char *p;
} DNode;
DNode d_pool[MAX_DCNT];

typedef struct _PNode
{
	struct _PNode *next;
	int pos;
} PNode;
PNode p_pool[MAX_DCNT];

typedef struct _ANode
{
	struct _ANode *next;
	struct _PNode *head;
	char *p;
	int cnt;
} ANode;
ANode a_pool[MAX_ACNT];

DNode *hsd[TABLE_SIZE];
ANode *hsa[TABLE_SIZE];

char len_vis[MAX_DLEN];

#define MA 26

#define islw(c) (c>='a'&&c<='z')
#define isup(c) (c>='A'&&c<='Z')
#define ctoi(c) c-'a'

typedef struct
{
	int cnt;
	PNode *head;
	char *p;
} Ans;
Ans ans[MAX_ACNT];

int hs_idx[MAX_ACNT];


#define swap(a,b) do{Ans t=a;a=b;b=t;}while(0)
#define less(a,b) a.cnt>b.cnt||(a.cnt==b.cnt&&strcmp(a.p,b.p)<0)
void quickSort(Ans *a,int n)
{
	if(n<=1)return;
	if(n<6)
	{
		int i;
		for(i=1; i<n; i++)
		{
			int j=i;
			Ans t=a[j];
			while(j&&(less(t, a[j-1])))a[j]=a[j-1],--j;
			a[j]=t;
		}
		return;
	}
	int m=n>>1;
	if(less(a[m], a[0]))swap(a[m],*a);
	if(less(a[n-1], a[0]))swap(a[n-1],*a);
	if(less(a[n-1], a[m]))swap(a[n-1],a[m]);
	Ans v=a[m];
	a[m]=a[n-2];
	a[n-2]=v;
	int i=0,j=n-2;
	while(1)
	{
		do ++i;
		while(less(a[i], v));
		do --j;
		while(less(v, a[j]));
		if(i<j)swap(a[i],a[j]);
		else break;
	}
	swap(a[i],a[n-2]);
	quickSort(a,i);
	quickSort(a+i+1,n-1-i);
}



char _d_buf[MAX_DLEN], * const d_buf=_d_buf+1;
char _a_buf[MAX_ALEN], * const a_buf=_a_buf+1;
char out_buf[MAX_DLEN];


#define up_to_lw(who) \
	for (now=who##_buf; now<end; now+=32) \
	{ \
		if (isup(now[0])) now[0] += 32; \
		if (isup(now[1])) now[1] += 32; \
		if (isup(now[2])) now[2] += 32; \
		if (isup(now[3])) now[3] += 32; \
		if (isup(now[4])) now[4] += 32; \
		if (isup(now[5])) now[5] += 32; \
		if (isup(now[6])) now[6] += 32; \
		if (isup(now[7])) now[7] += 32; \
		if (isup(now[8])) now[8] += 32; \
		if (isup(now[9])) now[9] += 32; \
		if (isup(now[10])) now[10] += 32; \
		if (isup(now[11])) now[11] += 32; \
		if (isup(now[12])) now[12] += 32; \
		if (isup(now[13])) now[13] += 32; \
		if (isup(now[14])) now[14] += 32; \
		if (isup(now[15])) now[15] += 32; \
		if (isup(now[16])) now[16] += 32; \
		if (isup(now[17])) now[17] += 32; \
		if (isup(now[18])) now[18] += 32; \
		if (isup(now[19])) now[19] += 32; \
		if (isup(now[20])) now[20] += 32; \
		if (isup(now[21])) now[21] += 32; \
		if (isup(now[22])) now[22] += 32; \
		if (isup(now[23])) now[23] += 32; \
		if (isup(now[24])) now[24] += 32; \
		if (isup(now[25])) now[25] += 32; \
		if (isup(now[26])) now[26] += 32; \
		if (isup(now[27])) now[27] += 32; \
		if (isup(now[28])) now[28] += 32; \
		if (isup(now[29])) now[29] += 32; \
		if (isup(now[30])) now[30] += 32; \
		if (isup(now[31])) now[31] += 32; \
	} \
	for (now-=32; now<end; ++now) \
		if (isup(*now)) *now += 32


#define read_file(PATH, who) \
	fin = fopen(PATH, "rb"), fseek(fin, 0, SEEK_END), end = who##_buf + (bytes = ftell(fin)), fseek(fin, 0, SEEK_SET), fread(who##_buf, bytes, 1, fin), fclose(fin)

int main()
{
	int bytes, i;
	ANode *pA, *poolA = a_pool;
	DNode *pD, *poolD = d_pool;
	PNode *pP, *poolP = p_pool;
	char *now, *end, *begin;
	FILE *fin;
	LL sum;

	int fd = 0;
	read_file("dictionary.txt", d);
//	up_to_lw(d);												// have a try(delete this sentence)

	for (now=d_buf; now<end; ++now)
	{
		if (islw(*now) && !islw(now[-1]))
		{
			begin = now, sum = 0;
			do sum = (sum*131+*now++-'a')%MOD1;
			while (islw(*now)); *now = '\0';

//			for (fd=0, pD=hsd[sum]; pD; pD=pD->next)			// 字典不发生hash冲突
//				if (!strcmp(pD->p, begin))
//				{
//					fd = 1;
//					break;
//				}

			if (!fd)
			{
				pD = hsd[sum],
				hsd[sum] = poolD++,
				hsd[sum]->next = pD,
				hsd[sum]->p = begin;
				++len_vis[now-begin];
			}

		}
	}

	read_file("article.txt", a);
	up_to_lw(a);

	int tot = 0;
	for (now=a_buf; now<end; ++now)
	{
		if (islw(*now) && !islw(now[-1]))
		{
			begin = now, sum = 0;
			do sum = (sum*131+*now++-'a')%MOD1;
			while (islw(*now)); *now = '\0';


			if (len_vis[now-begin] && hsd[sum])			// 有可能在字典中出现，也有可能是冲突了，要检查是不是真的出现了
			{
				for (pD=hsd[sum]; pD; pD=pD->next)
					if (!strcmp(begin, pD->p))
						goto found;						// 真的在字典中出现了
				goto not_found;							// 冲突了，实际上没在字典中出现。
			}
			else				// 不可能在字典中出现
			{
				not_found:		// 以上两种情况都是没在字典中出现，都要添加到文章哈希中
				if (hsa[sum])		// 已经有了，或者冲突了
				{
					for (fd=0, pA=hsa[sum]; pA; pA=pA->next)
						if (!strcmp(pA->p, begin))					// 真的已经有了，加加cnt，然后加位置
						{
							fd = ++pA->cnt,
							pP = pA->head,
							pA->head = poolP++,
							pA->head->pos = begin-a_buf,
							pA->head->next = pP;
							break;
						}
					if (!fd)										// 冲突了，要加新的
						pA = hsa[sum],
						hsa[sum] = poolA++,
						hsa[sum]->next = pA,
						hsa[sum]->head = poolP++,	// 加第一个位置
						hsa[sum]->head->pos = begin-a_buf,
						hsa[sum]->head->next = NULL,
						hsa[sum]->cnt = 1,
						hsa[sum]->p = begin;
				}
				else			// 没有啊，必须添加
					hsa[sum] = poolA++,
					hsa[sum]->next = NULL,
					hsa[sum]->head = poolP++,
					hsa[sum]->head->pos = begin-a_buf,
					hsa[sum]->head->next = NULL,
					hsa[sum]->cnt = 1,
					hsa[sum]->p = begin,
					hs_idx[tot++] = sum;
			}

			found:;
		}
	}

	int final_tot = 0;
	for (i=0; i<tot; ++i)										// hava a try(unroll-loop)
		for (pA = hsa[hs_idx[i]]; pA; pA=pA->next)
			ans[final_tot].cnt = pA->cnt,
			ans[final_tot].head = pA->head,
			ans[final_tot++].p = pA->p;

	quickSort(ans, final_tot);

	char *p = out_buf;
	char *s;
	int sta[21], top = 0, tp, top2 = 0;
	for (i=0; i<final_tot; ++i)
	{
		for (s=ans[i].p; *s; ++s)
			*p++ = *s;
		*p++ = ' ';


		tp = ans[i].cnt, top = 0;
		do sta[top++] = tp%10;
		while (tp/=10);

		while (top--)
			*p++ = '0'+sta[top];
		*p++ = ' ';


		for (pP=ans[i].head, top2=0; pP; pP=pP->next)
			hs_idx[top2++] = pP->pos;
		while (top2--)
		{
			tp = hs_idx[top2], top = 0;
			do sta[top++] = tp%10;
			while (tp/=10);

			while (top--)
				*p++ = '0'+sta[top];
			*p++ = ' ';
		}

		p[-1] = '\n';
	}

	FILE *fout = fopen("misspelling.txt", "wb");
	bytes = p - out_buf;
	fwrite(out_buf, bytes, 1, fout);
	fclose(fout);

	return 0;
}
