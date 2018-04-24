/************************************************************
 * btree.h - Simple binary tree that can be modified easily.
 *
 * To use DATA_OPTIONS define please put this code into your
 * file where you are going to use this.
 *
 * Code:
 *   #undef options
 *   struct options {
 *     char *value; *** You can put anything here this is a
 *                     place holder. ***
 *   };
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
#ifdef DATA_OPTIONS
#define options OPTIONS2
struct options {
	char *value;
};
#else
struct options {
	char *value;
};
#endif

typedef struct btree btree_t;

/* callback function declarations */
typedef void (*insert_callback)(int key, btree_t **leaf);
typedef void (*print_callback)(btree_t *leaf);
typedef void (*setopt_callback)();

/* btree data structure */
struct btree {
	int key_value;
	struct options opts;
	insert_callback insert;
	print_callback print;
	setopt_callback set_opts;
	struct btree *left;
	struct btree *right;
};

/* destroy_tree:  frees all memory; wiping the tree clean */
static void destroy_tree(btree_t *leaf)
{
	if (leaf != 0) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		if (leaf->opts.value != 0)
			free(leaf->opts.value);
		free(leaf);
	}
}

static void insert_tree(int key, btree_t **leaf);
static void print_tree(btree_t *tree);
static void setopt_tree(btree_t *tree, int key, const char *text);

/* init_tree:  call this initialize the tree */
#ifdef DATA_OPTIONS
static btree_t *init_tree(insert_callback insert_func,
	print_callback print_func, setopt_callback option_func)
#else
static btree_t *init_tree(void)
#endif
{
	btree_t *leaf;

	leaf = (btree_t*)malloc(sizeof(btree_t));
	if (leaf == 0)
		return NULL;

	/* initialize custom functions and data */
	leaf->key_value = 0;
#ifdef DATA_OPTIONS
	leaf->insert = (insert_func == NULL) ? insert_tree : insert_func;
	leaf->print = (print_func == NULL) ? print_tree : print_func;
	leaf->set_opts = (option_func == NULL) ? setopt_tree : option_func;
#else
	leaf->insert = insert_tree;
	leaf->print = print_tree;
	leaf->set_opts = setopt_tree;
#endif

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
