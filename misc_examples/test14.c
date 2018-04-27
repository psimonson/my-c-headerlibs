/******************************************************
 * test14.c - Example two of using my dlist header    *
 *            library. This shows you how to override *
 *            my dlist, using your own functions and  *
 *            data structure.                         *
 *                                                    *
 * Created by Philip R. Simonson                      *
 ******************************************************
 */

struct dlist {
	char *data;
	int id;
	struct dlist *next;
};
#define DLIST_DATA_OPTIONS
#include "../common/dlist.h"

/* create:  creates first element of dlist */
dlist_t *create(void)
{
	dlist_t *list;

	list = (dlist_t*)malloc(sizeof(dlist_t));
	if (list == 0)
		return NULL;
	list->id = -1;
	list->data = 0;
	list->next = NULL;
	return list;
}

/* destroy:  destroys entire dlist */
void destroy(dlist_t **list)
{
	dlist_t *cur, *next;

	cur = *list;
	while (cur != NULL) {
		next = cur->next;
		free(cur->data);
		free(cur);
		cur = next;
	}
	*list = NULL;
}

/* set:  custom set data function */
void set(dlist_t *list, int id, const char *data)
{
	if (list == 0)
		return;
	list->id = id;
	list->data = str_dup(data);
}

/* add:  add item to end of list */
void add(dlist_t *list, int id, const char *data)
{
	dlist_t *tmp;

	tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = create();
	set(tmp->next, id, data);
}

/* dlist_display:  displays the contents of the list */
void display(dlist_t *list)
{
	/* TODO: Add custom display code here */
}

/* program to test my dynamic linked list */
int main()
{
	dlist_t *list;

	/* list create, set, add new node
	 * args for dlist_init(create, add, destroy, display)
	 */
	list = dlist_init(create, add, set, destroy, NULL);
	dlist_set(list, 0, "Hello.");
	dlist_add(list, 1, "Hello world");
	dlist_add(list, 2, "Hello again world!");

	/* now display the list */
	dlist_display(list);
	/* display the count */
	printf("List item count: %d\n", dlist_get_count(list));

	/* destroy the list */
/*	dlist_destroy(&list);	* Uncomment to clear list before
 				* status check happens */
	printf("List empty status: %s\n",
		(dlist_is_empty(list) == 0) ? "Empty" : "Not Empty");
	dlist_cleanup(list);
	return EXIT_SUCCESS; /* return success */
}
