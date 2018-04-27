/************************************************************
 * btree.h - Simple binary tree that can be modified easily.
 *
 * To use DATA_OPTIONS define please put this code into your
 * file above where you include this header, and define
 * DATA_OPTIONS before you include this header also if you
 * want it custom.
 *
 * Code:
 *   struct options { ... };
 *
 * Created by Philip R. Simonson
 ************************************************************
 */

#ifndef PRS_BTREE_H
#define PRS_BTREE_H

#ifndef PRS_HELPER_H
#include "helper.h"
#endif
#include <stdlib.h>

/* options structure */
#ifndef DATA_OPTIONS
struct options {
	char *value;
};
#endif

typedef struct btree btree_t;

/* callback function declarations */
typedef void (*insert_callback)(int key, btree_t **leaf);
typedef void (*print_callback)(btree_t *leaf);
typedef void (*setopt_callback)();
typedef void (*destroy_callback)(btree_t **leaf);

/* btree data structure */
struct btree {
	int key_value;
	struct options opts;
	struct btree *left;
	struct btree *right;
};

insert_callback btree_insert;
print_callback btree_print;
setopt_callback btree_setopt;
destroy_callback btree_destroy;

/* destroy_tree:  frees all memory; wiping the tree clean */
static void destroy_tree(btree_t **leaf)
{
	if (*leaf != 0) {
		destroy_tree(&(*leaf)->left);
		destroy_tree(&(*leaf)->right);
		if ((*leaf)->opts.value != 0)
			free((*leaf)->opts.value);
		free(*leaf);
	}
}

static void insert_tree(int key, btree_t **leaf);
static void print_tree(btree_t *tree);
static void setopt_tree(btree_t *tree, int key, const char *text);

/* init_tree:  call this initialize the tree */
#ifdef DATA_OPTIONS
static btree_t *init_tree(insert_callback insert_func,
	setopt_callback option_func, print_callback print_func,
	destroy_callback destroy_func)
#else
static btree_t *init_tree(void)
#endif
{
	btree_t *leaf;

	leaf = (btree_t*)malloc(sizeof(btree_t));
	if (leaf == 0)
		return NULL;

#ifdef DATA_OPTIONS
	btree_insert = (insert_func == NULL) ? insert_tree : insert_func;
	btree_print = (print_func == NULL) ? print_tree : print_func;
	btree_setopt = (option_func == NULL) ? setopt_tree : option_func;
	btree_destroy = (destroy_func == NULL) ? destroy_tree : destroy_func;
#else
	btree_insert = insert_tree;
	btree_print = print_tree;
	btree_setopt = setopt_tree;
	btree_destroy = destroy_tree;
#endif

	/* initialize custom functions and data */
	leaf->key_value = 0;
	p_zero(&leaf->opts, sizeof(leaf->opts));
	/* initialize left and right leafs */
	leaf->left = 0;
	leaf->right = 0;
	return leaf;
}

/* insert_tree:  adds a new leaf to the binary tree */
void insert_tree(int key, btree_t **leaf)
{
	if (*leaf == 0) {
		*leaf = (btree_t*)malloc(sizeof(btree_t));
		(*leaf)->key_value = key;
		(*leaf)->opts.value = 0;
		/* initialize the children */
		(*leaf)->left = 0;
		(*leaf)->right = 0;
	}
	else if (key < (*leaf)->key_value)
		insert_tree(key, &(*leaf)->left);
	else if (key > (*leaf)->key_value)
		insert_tree(key, &(*leaf)->right);
}

/* search_tree:  searches given tree; returns leaf, NULL if not found */
static btree_t *search_tree(int key, btree_t *leaf)
{
	if (leaf != 0) {
		if (key == leaf->key_value)
			return leaf;
		else if (key < leaf->key_value)
			return search_tree(key, leaf->left);
		else
			return search_tree(key, leaf->right);
	}
	return 0;
}

/* print_whole_tree:  prints everything in the tree */
static void print_tree(btree_t *leaf)
{
	if (leaf != 0) {
		print_tree(leaf->left);
		print_tree(leaf->right);
		printf("Key Value: %d\nString %d: %s\n",
			leaf->key_value, leaf->key_value, leaf->opts.value);
	}
}

/* setopt_tree:  sets data in the options struct of tree */
void setopt_tree(btree_t *leaf, int key, const char *text)
{
	if (leaf != 0) {
		btree_t *branch;
		branch = search_tree(key, leaf);
		if (branch != 0) {
			branch->opts.value = str_dup(text);
		}
	}
}
#endif
