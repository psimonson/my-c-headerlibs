struct dlist {
	char *data;
	int id;
	struct dlist *next;
};
#define DLIST_DATA_OPTIONS
#include "../common/dlist.h"

/* program to test my dynamic linked list */
int main()
{
	struct dlist_data *data;

	/* list create, set, add new node */
	data = dlist_init(NULL, NULL, NULL, NULL);
	data->list = dlist_create("Hello.");
	data->add(data->list, "Hello world");
	data->add(data->list, "Hello again world!");

	/* now display the list */
	data->display(data->list);
	/* display the count */
	printf("List item count: %d\n", dlist_get_count(data->list));

	/* destroy the list */
/*	data->destroy(&data->list);	* Uncomment to clear list before
 					* status check happens */
	printf("List empty status: %s\n",
		(dlist_is_empty(data->list) == 0) ? "Empty" : "Not Empty");
	dlist_cleanup(data);
	return EXIT_SUCCESS; /* return success */
}
