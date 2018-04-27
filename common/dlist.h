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

/* declarations for callbacks */
typedef dlist_t *(*create_cb)(void);
typedef void (*add_cb)();
typedef void (*set_cb)();
typedef void (*display_cb)(dlist_t *);
typedef void (*destroy_cb)(dlist_t **);

/* definitions for callbacks */
create_cb dlist_create;
add_cb dlist_add;
set_cb dlist_set;
display_cb dlist_display;
destroy_cb dlist_destroy;

/* function prototypes */
static dlist_t *create_dlist(void);
static void destroy_dlist(dlist_t **);
static void add_dlist(dlist_t *list, const char *data);
static void set_dlist(dlist_t *list, const char *data);
static void display_dlist(dlist_t *list);

/* dlist_init:  initialize dynamic linked list */
#ifdef DLIST_DATA_OPTIONS
static dlist_t *dlist_init(create_cb create_func, add_cb add_func,
	set_cb set_func, destroy_cb destroy_func, display_cb display_func)
#else
static dlist_t *dlist_init(void)
#endif
{
	dlist_t *list;

#ifdef DLIST_DATA_OPTIONS
	dlist_create = (create_func == NULL) ? create_dlist : create_func;
	dlist_add = (add_func == NULL) ? add_dlist : add_func;
	dlist_set = (set_func == NULL) ? set_dlist : set_func;
	dlist_destroy = (destroy_func == NULL) ? destroy_dlist : destroy_func;
	dlist_display = (display_func == NULL) ? display_dlist : display_func;
#else
	dlist_create = create_dlist;
	dlist_add = add_dlist;
	dlist_set = set_dlist;
	dlist_destroy = destroy_dlist;
	dlist_display = display_dlist;
#endif
	list = dlist_create();
	if (list == NULL)
		return NULL;
	return list;
}


/* dlist_create:  create the dynamic linked list */
dlist_t *create_dlist(void)
{
	extern int id;
	dlist_t *list;

	list = (dlist_t*)malloc(sizeof(dlist_t));
	if (list == NULL)
		return NULL;
	list->id = ++id;
	list->data = 0;
	list->next = NULL;
	return list;
}

/* dlist_destroy:  destroy whole list; freeing all memory */
void destroy_dlist(dlist_t **list)
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

/* dlist_cleanup:  cleans all data used from dlist */
void dlist_cleanup(dlist_t *list)
{
	if (list != 0) {
		destroy_dlist(&list);
	}
}

void set_dlist(dlist_t *list, const char *data)
{
	if (list != 0)
		list->data = str_dup(data);
}

/* dlist_add:  add item to end of list */
void add_dlist(dlist_t *list, const char *data)
{
	dlist_t *tmp;

	tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = dlist_create();
	set_dlist(tmp->next, data);
}

/* dlist_display:  displays the Contents of the list */
void display_dlist(dlist_t *list)
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
	return (list != NULL);
}
#endif
