#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 512

struct tree {
	int key_value;
	char line[MAXLINE];
	struct tree *left;
	struct tree *right;
};

void destroy_tree(struct tree *leaf)
{
	if (leaf != 0) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		free(leaf);
	}
}

void insert_tree(int key, const char *text, struct tree **leaf)
{
	if (*leaf == 0) {
		*leaf = (struct tree*) malloc(sizeof(struct tree));
		if (*leaf == 0)
			return;
		(*leaf)->key_value = key;
		strncpy((*leaf)->line, text, MAXLINE-1);
		/* initialize children to null */
		(*leaf)->left = 0;
		(*leaf)->right = 0;
	} else if (key < (*leaf)->key_value) {
		insert_tree(key, text, &(*leaf)->left);
	} else if (key > (*leaf)->key_value) {
		insert_tree(key, text, &(*leaf)->right);
	}
}

struct tree *search_tree(int key, struct tree *leaf)
{
	if (leaf != 0) {
		if (key == leaf->key_value) {
			return leaf;
		} else if (key < leaf->key_value) {
			return search_tree(key, leaf->left);
		} else {
			return search_tree(key, leaf->right);
		}
	}
	return 0;
}

void print_tree(struct tree *leaf)
{
	if (leaf != 0) {
		struct tree *node;
		for (node = leaf->left; node != 0; node = node->left)
			printf("%s\n", node->line);
		for (node = leaf->right; node != 0; node = node->right)
			printf("%s\n", node->line);
		printf("%s\n", leaf->line);
	}
}

int main()
{
	struct tree *root = 0;
	insert_tree(0, "Hello world.", &root);
	insert_tree(1, "This is a test.", &root);
	insert_tree(-1, "Hello again.", &root);
	print_tree(root);
	destroy_tree(root);
	return 0;
}
