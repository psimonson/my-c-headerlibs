#include "../common/dlist.h"

/* program to test my dynamic linked list */
int main()
{
	dlist_t *list;

	/* list create, set, add new node */
	list = dlist_init();
	dlist_set(list, "Hello.");
	dlist_add(list, "Hello world!");
	dlist_add(list, "Hello again world!");

	/* now display the list */
	dlist_display(list);
	/* display the count */
	printf("List item count: %d\n", dlist_get_count(list));

	/* destroy the list */
/*	dlist_destroy(&list); * Uncomment to check empty status */
	printf("List empty status: %s\n",
		(dlist_is_empty(list) == 0) ? "Empty" : "Not Empty");
	dlist_cleanup(list);
	return EXIT_SUCCESS; /* return success */
}
