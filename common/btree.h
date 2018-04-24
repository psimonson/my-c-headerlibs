/************************************************************
 * btree.h - Simple binary tree that can be modified easily.
 *
 * Created by Philip R. Simonson
 ************************************************************
 */

#define PRS_BTREE_H

#ifndef PRS_HELPER_H
#include "helper.h"
#endif
#include <stdlib.h>

/* options structure */
struct options {
	char *value;
};

/* btree data structure */
typedef struct btree btree_t;
struct btree {
	int key_value;
	struct options opts;
	void (*print)(btree_t *leaf);
	void (*set_opts)();
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

/* callback function declarations */
typedef void (*print_cb)(btree_t *leaf);
typedef void (*setopt_cb)();

/* init_tree:  call this initialize the tree */
static btree_t *init_tree(print_cb print_func, setopt_cb option_func)
{
	void print_tree(btree_t *tree);
	void setopt_tree(btree_t *tree, int key, const char *text);
	btree_t *leaf;

	leaf = (btree_t*)malloc(sizeof(btree_t));
	if (leaf == 0)
		return NULL;

	leaf->key_value = 0;
	leaf->print = (print_func == NULL) ? print_tree : print_func;
	leaf->set_opts = (option_func == NULL) ? setopt_tree : option_func;

	/* initialize left and right leafs */
	leaf->left = 0;
	leaf->right = 0;
	return leaf;
}

/* insert_tree:  adds a new leaf to the binary tree */
static void insert_tree(int key, btree_t **leaf)
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

/* print_tree:  prints just the key values in the tree */
static void print_tree(btree_t *leaf)
{
	if (leaf != 0) {
		print_tree(leaf->left);
		print_tree(leaf->right);
		printf("Key value: %d\n", leaf->key_value);
	}
}

/* print_whole_tree:  prints everything in the tree */
static void print_whole_tree(btree_t *leaf)
{
	if (leaf != 0) {
		print_whole_tree(leaf->left);
		print_whole_tree(leaf->right);
		printf("Key Value: %d\nString %d: %s\n",
			leaf->key_value, leaf->key_value, leaf->opts.value);
	}
}

/* setopt_tree:  sets data in the options struct of tree */
static void setopt_tree(btree_t *leaf, int key, const char *text)
{
	if (leaf != 0) {
		btree_t *branch;
		branch = search_tree(key, leaf);
		if (branch != 0) {
			branch->opts.value = str_dup(text);
		}
	}
}
