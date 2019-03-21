#include "klist.h"


int main()
{
	List list, *l = &list;
	init(l);

	push_back(l, 1);
	push_back(l, 3);
	push_front(l, 2);
	println(l);

	insert_after(l, 1, 5);
	insert_before(l, 0, 3);
	println(l);

	erase_at(l, 1);
	push_back(l, 3);
	println(l);

	bubble_sort(l);
	unique(l);
	reverse(l);
	println(l);

	clear(l);


	debug_allocate();

	return 0;
}
