/************************************************
 * dlist.h - Simple Dynamic Linked List
 * Created by Philip "5n4k3" Simonson
 ************************************************
 */

#ifndef PRS_DLIST_H
#define PRS_DLIST_H

#include "prs_string.h"

/* used for id inside struct */
static int id;

/* data structure for list */
struct dlist {
	int id;
	char *data;
	struct dlist *next;
};
/* typedef for DLIST structure */
typedef struct dlist dlist_t;

/* dlist_create:  create the dynamic linked list */
static dlist_t *dlist_create(const char *data)
{
	extern int id;
	dlist_t *list;

	list = malloc(sizeof(dlist_t));
	if (list == NULL)
		return NULL;
	list->id = ++id;
	list->data = str_dup(data);
	list->next = NULL;
	return list;
}

/* dlist_remove:  remove an item; freeing the memory */
static void dlist_remove(dlist_t *list)
{
	dlist_t *tmp;

	if (list->next == NULL) {
		free(list->data);
		free(list);
	}

	/* get to the last node */
	tmp = list;
	while (tmp->next->next != NULL) {
		tmp = tmp->next;
	}

	/* now current is last item */
	free(tmp->data);
	free(tmp);
}

/* dlist_destroy:  destroy whole list; freeing all memory */
static void dlist_destroy(dlist_t *list)
{
	dlist_t *tmp;

	tmp = list;
	while (tmp->next != NULL) {
		dlist_remove(tmp);
		tmp = tmp->next;
	}
	free(list);
	list = NULL;
	id = 0;
}

/* dlist_add:  add item to end of list */
static void dlist_add(dlist_t *list, const char *data)
{
	dlist_t *tmp;

	tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = dlist_create(data);
}

/* dlist_display:  displays the Contents of the list */
static void dlist_display(dlist_t *list)
{
	dlist_t *tmp;

	tmp = list;
	printf("=======================================\n"
		">>> List Contents <<<\n=======================================\n");
	while (tmp->next != NULL) {
		printf("Item Number: %d\n>>> Contents <<<\n%s\n"
			"=======================================\n",
			tmp->id, tmp->data);
		tmp = tmp->next;
	}
	printf(">>> End of List <<<\n=======================================\n");
}

/* dlist_get_count:  returns the number of elements */
static int dlist_get_count(dlist_t *list)
{
	dlist_t *tmp;
	int count;

	count = 0;
	tmp = list;
	while (tmp->next != NULL) {
		count++;
		tmp = tmp->next;
	}
	return count;
}

/* dlist_is_empty:  checks for elements; returns 0 if empty */
static int dlist_is_empty(dlist_t *list)
{
	return (list == NULL) ? 0 : dlist_get_count(list) > 0;
}
#endif
