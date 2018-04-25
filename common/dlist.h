/************************************************
 * dlist.h - Simple Dynamic Linked List
 * Created by Philip "5n4k3" Simonson
 ************************************************
 */

#ifndef PRS_DLIST_H
#define PRS_DLIST_H

#ifndef PRS_HELPER_H
#include "helper.h"
#endif
#include <stdlib.h>

/* used for id inside struct */
static int id;

/* data structure for list */
#ifndef DLIST_DATA_OPTIONS
struct dlist {
	int id;
	char *data;
	struct dlist *next;
};
#endif
typedef struct dlist dlist_t;
struct dlist_data;

/* definitions for callbacks */
typedef dlist_t *(*create_cb)();
typedef void (*remove_cb)(dlist_t *);
typedef dlist_t *(*destroy_cb)(struct dlist_data *);
typedef void (*add_cb)(dlist_t *, const char *);

/* dlist structure */
struct dlist_data {
	struct dlist *list;
	create_cb create;
	add_cb add;
	remove_cb remove;
	destroy_cb destroy;
};

/* function prototypes */
static dlist_t *dlist_create(const char *data);
static void dlist_remove(dlist_t *list);
static dlist_t *dlist_destroy(struct dlist_data *);
static void dlist_add(dlist_t *list, const char *data);
static void dlist_display(dlist_t *list);

/* dlist_init:  initialize dynamic linked list */
static struct dlist_data *dlist_init(void)
{
	struct dlist_data *data;

	data = (struct dlist_data*)malloc(sizeof(struct dlist_data));
	if (data == 0)
		return NULL;

	data->list = 0;
#ifdef DLIST_DATA_OPTIONS
	data->create = (create_func == NULL) ? dlist_create : create_func;
	data->add = (add_func == NULL) ? dlist_add : add_func;
	data->remove = (remove_func == NULL) ? dlist_remove : remove_func;
	data->destroy = (destroy_func == NULL) ? dlist_destroy : destroy_func;
#else
	data->create = dlist_create;
	data->add = dlist_add;
	data->remove = dlist_remove;
	data->destroy = dlist_destroy;
#endif
	return data;
}


/* dlist_create:  create the dynamic linked list */
dlist_t *dlist_create(const char *data)
{
	extern int id;
	dlist_t *list;

	list = (dlist_t*)malloc(sizeof(dlist_t));
	if (list == NULL)
		return NULL;
	list->id = ++id;
	list->data = str_dup(data);
	list->next = NULL;
	return list;
}

/* dlist_remove:  remove an item; freeing the memory */
void dlist_remove(dlist_t *list)
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
dlist_t *dlist_destroy(struct dlist_data *data)
{
	dlist_t *tmp;
	int i;

	i = 0;
	tmp = data->list;
	while (tmp->next->next != NULL) {
		i++;
		tmp = tmp->next;
	}
	for (; i >= 0; i--)
		data->remove(data->list);
	id = 0;
	return (data->list == NULL) ? NULL : data->list;
}

/* dlist_cleanup:  cleans all data used from dlist */
void dlist_cleanup(struct dlist_data *data)
{
	if (data != 0) {
		if (data->list != 0)
			data->list = data->destroy(data);
		free(data);
	}
}

/* dlist_add:  add item to end of list */
void dlist_add(dlist_t *list, const char *data)
{
	dlist_t *tmp;

	tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = dlist_create(data);
}

/* dlist_display:  displays the Contents of the list */
void dlist_display(dlist_t *list)
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
	while (tmp != NULL) {
		count++;
		tmp = tmp->next;
	}
	return count;
}

/* dlist_is_empty:  checks for elements; returns 0 if empty */
static int dlist_is_empty(dlist_t *list)
{
	return (list != NULL) ? 0 : 1;
}
#endif
