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
dlist_t *create(int id, const char *data)
{
	dlist_t *list;

	list = (dlist_t*)malloc(sizeof(dlist_t));
	if (list == 0)
		return NULL;
	list->id = id;
	list->data = str_dup(data);
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

/* dlist_add:  add item to end of list */
void add(dlist_t *list, int id, const char *data)
{
	dlist_t *tmp;

	tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = create(id, data);
}

/* dlist_display:  displays the contents of the list */
void display(dlist_t *list)
{
	/* TODO: Add custom display code here */
}

/* program to test my dynamic linked list */
int main()
{
	struct dlist_data *data;

	/* list create, set, add new node
	 * args for dlist_init(create, add, destroy, display)
	 */
	data = dlist_init(create, add, destroy, NULL);
	data->list = data->create(0, "Hello.");
	data->add(data->list, 1, "Hello world");
	data->add(data->list, 2, "Hello again world!");

	/* now display the list */
	data->display(data->list);
	/* display the count */
	printf("List item count: %d\n", dlist_get_count(data->list));

	/* destroy the list */
/*	data->destroy(&data->list);	* Uncomment to clear list before
 					* status check happens */
	printf("List empty status: %s\n",
		(dlist_is_empty(data->list) == 0) ? "Empty" : "Not Empty");
	/* if data->destroy() not used, this also destroys the list */
	dlist_cleanup(data);
	return EXIT_SUCCESS; /* return success */
}
