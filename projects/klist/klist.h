#ifndef INC_K_LIST
#define INC_K_LIST


#include <stdio.h>
#include <malloc.h>

#include "config.h"


typedef struct _Node
{
	bool tag;
	Data data;
	struct _Node *next;
	struct _Node *prev;
} Node;

typedef struct
{
	cint cnt;
	Node *head;
	Node *tail;
} List;


// constructor
#define init_node(_p, _data, _prev, _next) \
	_p->tag = false,  \
	_p->data = _data, \
	_p->prev = _prev, \
	_p->next = _next


// comparison operator
#define equal(n1, n2) n1 == n2
#define greater(n1, n2) n1 > n2


// swapping for any type
#define swap(Type, v1, v2) \
	do \
	{ \
		Type temp = v1; \
		v1 = v2; \
		v2 = temp; \
	} while (0)



// basic functions
void init(List *pL);
void clear(List *pL);
bool empty(const List *pL);
cint size(const List *pL);
List *copy(List *pDest, const List *pSrc);
List *append(List *pDest, const List *pSrc);


// pushing and popping
bool push_front(List *pL, Data data);
bool push_back(List *pL, Data data);

Data pop_front(List *pL);
Data pop_back(List *pL);


// find
xint find(const List *pL, const Data key);
xint rfind(const List *pL, const Data key);
Data at(const List *pL, const xint index);


// insertion and erasion
bool insert_before(List *pL, const xint index, const Data data);
bool insert_after(List *pL, const xint index, const Data data);

Data erase_node(List *pL, Node *p);
cint erase_tagged(List *pL);
xint erase_first_key(List *pL, const Data key);
xint erase_last_key(List *pL, const Data key);
cint erase_keys(List *pL, const Data key);
Data erase_at(List *pL, const xint index);
cint erase_interval(List *pL, const xint lb, const xint ub);


// other operations to the data
Data add_at(List *pL, const xint index, const Data data);
cint add_interval(List *pL, const xint lb, const xint ub, const Data data);
Data assign_at(List *pL, const xint index, const Data data);
cint assign_interval(List *pL, const xint lb, const xint ub, const Data data);
cint replace(List *pL, const Data oldData, const Data newData);
bool swap_at(List *pL, const xint left, const xint right);


// other operations to the whole list
void reverse(List *pL);
void unique(List *pL);
void bubble_sort(List *pL);
void println(const List *pL);


// debug function (print the the number of times that the free and malloc functions are called)
void debug_allocate();


#endif
