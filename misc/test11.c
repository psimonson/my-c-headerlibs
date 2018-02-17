#include "../common/dlist.h"

/* program to test my dynamic linked list */
int main()
{
	dlist_t *list;

	/* list create, set, add new node */
	list = dlist_create("Hello.");
	dlist_add(list, "Hello world");
	dlist_add(list, "Hello again world!");

	/* now display the list */
	dlist_display(list);
	/* display the count */
	printf("List item count: %d\n", dlist_get_count(list));

	/* destroy the list */
	dlist_destroy(list);
	printf("List empty status: %d\n", dlist_is_empty(list));
	return EXIT_SUCCESS; /* return success */
}
