/****************************************************************************
 * d_list.h - Simple Universal Dynamic Linked List.
 *
 * Info: Useful if you need a dynamic linked list for any project. Because
 *       I have implemented callbacks for all of the work horse functions.
 *       In other words, you can adapt this with the callbacks and making
 *       your own data structure how ever you wish.
 *
 * Developer: Philip R. Simonson (aka 5n4k3)                    (7/29/2018)
 ****************************************************************************
 */

#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdlib.h>
#include <string.h>

/* callback prototypes */
typedef void *(*add_data_cb)();
typedef void (*remove_data_cb)(void **data);
typedef void (*prepend_node_cb)();
typedef void (*append_node_cb)();

struct DLIST_DATA {
    int value;
    char *message;
};

struct DLIST {
    int count;
    void *data;
    struct DLIST *next;
};

enum DLIST_STATE { DLIST_STATE_START, DLIST_STATE_NEXT, DLIST_STATE_END };

/* --------- don't touch these definitions --------- */

static enum DLIST_STATE _dlist_state = DLIST_STATE_START;
static struct DLIST *_dlist_last_node = NULL;
static struct DLIST *_dlist_last_saved = NULL;

static add_data_cb dlist_add_data = NULL;
static remove_data_cb dlist_remove_data = NULL;
static prepend_node_cb dlist_prepend_node = NULL;
static append_node_cb dlist_append_node = NULL;

extern char *strdup(const char *);

/* ------------ End of Definitions ----------------- */

static void dlist_iterator_init(struct DLIST *root)
{
	_dlist_last_node = (root) ? root : NULL;
	_dlist_last_saved = NULL;
	_dlist_state = DLIST_STATE_START;
}

static void dlist_iterator_reset(void)
{
	_dlist_last_saved = NULL;
	_dlist_state = DLIST_STATE_START;
}

static struct DLIST *dlist_iterator_next(void)
{
	switch(_dlist_state) {
		case DLIST_STATE_START:
			_dlist_last_node = (_dlist_last_node) ? _dlist_last_node : NULL;
			_dlist_last_saved = _dlist_last_node;
			_dlist_state = DLIST_STATE_NEXT;
		break;
		case DLIST_STATE_NEXT:
			_dlist_last_node = (_dlist_last_node->next)
							? _dlist_last_node->next : NULL;
			if (!_dlist_last_node)
				_dlist_state = DLIST_STATE_END;
			else
				_dlist_last_saved = _dlist_last_node;
		break;
		case DLIST_STATE_END:
		default:
		break;
	}
	return _dlist_last_node;
}

static struct DLIST *dlist_iterator_last(void)
{
	return _dlist_last_saved;
}

static void *_dlist_add_data(int num, const char *msg)
{
	struct DLIST_DATA *data;
	data = (struct DLIST_DATA *)malloc(sizeof(struct DLIST_DATA));
	if (!data)
		return NULL;
	data->value = num;
	data->message = strdup(msg);
	return (void*)data;
}

static void _dlist_remove_data(void **dat)
{
	struct DLIST_DATA *data = (struct DLIST_DATA *)*dat;
	if (data->message)
		free(data->message);
	free(*dat);
	*dat = NULL;
}

static void _dlist_prepend_node(void **root, int num, const char *msg);
static void _dlist_append_node(void **root, int num, const char *msg);

static struct DLIST *dlist_init(add_data_cb add_func,
                    remove_data_cb remove_func,
                    prepend_node_cb prepend_func,
                    append_node_cb append_func)
{
	dlist_add_data = (add_func) ? add_func : _dlist_add_data;
	dlist_remove_data = (remove_func) ? remove_func : _dlist_remove_data;
	dlist_prepend_node = (prepend_func) ? prepend_func : _dlist_prepend_node;
	dlist_append_node = (append_func) ? append_func : _dlist_append_node;
	if (!dlist_add_data || !dlist_remove_data ||
		!dlist_prepend_node || !dlist_append_node) {
		error_print("Cannot initialize functions.");
		exit(1);
	}
	return NULL;
}

void _dlist_prepend_node(void **root, int num, const char *msg)
{
	struct DLIST *node, *tmp;
	node = (struct DLIST *)malloc(sizeof(struct DLIST));
	if (!node)
		return;
	if (!(*root)) {
		node->count = 1;
		node->data = dlist_add_data(num, msg);
		node->next = NULL;
		(*root) = node;
	} else {
		((struct DLIST *)*root)->count++;
		tmp = (*root);
		node->count = ((struct DLIST *)*root)->count;
		node->data = dlist_add_data(num, msg);
		node->next = tmp;
		(*root) = node;
	}
}

void _dlist_append_node(void **root, int num, const char *msg)
{
	struct DLIST *node;
	node = (struct DLIST *)malloc(sizeof(struct DLIST));
	if (!node)
		return;
	if (!(*root)) {
		node->count = 1;
		node->data = dlist_add_data(num, msg);
		node->next = NULL;
		(*root) = node;
	} else {
		struct DLIST *tmp = *root;
		while (tmp->next != NULL)
			tmp = tmp->next;
		((struct DLIST *)*root)->count++;
		node->count = ((struct DLIST *)*root)->count;
		node->data = dlist_add_data(num, msg);
		node->next = NULL;
		tmp->next = node;
	}
}

static void dlist_destroy(struct DLIST **root)
{
    if (*root != NULL) {
        struct DLIST *tmp;
        tmp = *root;
        while(tmp != NULL) {
            struct DLIST *next = tmp->next;
            dlist_remove_data(&(tmp->data));
            free(tmp);
            tmp = next;
        }
        *root = NULL;
    }
}

#endif
