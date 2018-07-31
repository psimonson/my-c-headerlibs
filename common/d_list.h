#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdlib.h>

struct DLIST {
    int count;
    void *data;
    struct DLIST *next;
};

enum DLIST_STATE { DLIST_STATE_START, DLIST_STATE_NEXT, DLIST_STATE_END };

/* --------- don't touch these definitions --------- */

enum DLIST_STATE _dlist_state = DLIST_STATE_START;
struct DLIST *_dlist_last_node = NULL;

/* ------------ End of Definitions ----------------- */

static struct DLIST *dlist_iterator_next();
static void dlist_iterator_reset(struct DLIST *root);

static struct DLIST *dlist_init()
{
    struct DLIST *list;
    list = (struct DLIST *)malloc(sizeof(struct DLIST));
    if (!list)
        return NULL;
    list->count = 0;
    list->data = NULL;
    list->next = NULL;
    return list;
}

void dlist_iterator_reset(struct DLIST *root)
{
    _dlist_last_node = (root) ? root : NULL;
    _dlist_state = DLIST_STATE_START;
}

struct DLIST *dlist_iterator_next()
{
    struct DLIST *node;

    switch(_dlist_state) {
    case DLIST_STATE_START:
        node = (_dlist_last_node) ? _dlist_last_node : NULL;
        _dlist_state = DLIST_STATE_NEXT;
        break;
    case DLIST_STATE_NEXT:
        node = (_dlist_last_node->next) ? _dlist_last_node->next : NULL;
        if (node)
            _dlist_state = DLIST_STATE_NEXT;
        else
            _dlist_state = DLIST_STATE_END;
        break;
    case DLIST_STATE_END:
        node = (_dlist_last_node) ? _dlist_last_node : NULL;
        _dlist_state = DLIST_STATE_END;
        break;
    }
    return node;
}

static void dlist_destroy(struct DLIST **root)
{
    if ((*root)->next == NULL) {
        free(*root);
        *root = NULL;
    }
}

#endif
