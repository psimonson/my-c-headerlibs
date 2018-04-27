struct options {
	char *value;
	int test;
};

#define DATA_OPTIONS
#include "../common/btree.h"

/* insert:  example custom btree insert function */
void insert(int key, btree_t **leaf)
{
	if (*leaf == 0) {
		*leaf = (btree_t*)malloc(sizeof(btree_t));
		(*leaf)->key_value = key;
		(*leaf)->opts.value = 0;
		(*leaf)->opts.test = 0;
		(*leaf)->left = 0;
		(*leaf)->right = 0;
	}
	else if (key < (*leaf)->key_value)
		insert(key, &(*leaf)->left);
	else if (key > (*leaf)->key_value)
		insert(key, &(*leaf)->right);
}

void setopts(int key, int value, const char *data, btree_t *leaf)
{
	if (leaf != 0) {
		btree_t *branch;
		branch = search_tree(key, leaf);
		if (branch != 0) {
			branch->opts.value = str_dup(data);
			branch->opts.test = value;
		}
	}
}

void print(btree_t *leaf)
{
	if (leaf != 0) {
		printf("====== Branch [%d] ======\n"
			"String: %s\n"
			"Test Integer: %d\n"
			"==== End Branch [%d] ====\n",
			leaf->key_value, leaf->opts.value, leaf->opts.test,
			leaf->key_value);
	}
}

void print_whole(btree_t *leaf)
{
	if (leaf != 0) {
		print(leaf);
		print_whole(leaf->left);
		print_whole(leaf->right);
	}
}

void destroy(btree_t **leaf)
{
	if (*leaf != 0) {
		destroy(&(*leaf)->left);
		destroy(&(*leaf)->right);
		if ((*leaf)->opts.value != 0)
			free((*leaf)->opts.value);
		free(*leaf);
	}
}

/* program to simply test my binary tree header library */
int main(int argc, char *argv[])
{
	btree_t *tree; /* without initializing to zero, use init_tree() */

	tree = init_tree(&insert, &setopts, &print_whole, &destroy);
	btree_insert(1, &tree);
	btree_insert(2, &tree);
	btree_insert(3, &tree);
	btree_insert(4, &tree);
	btree_setopt(0, 45, "Hello world!", tree);
	btree_setopt(1, 50, "Hello again world!", tree);
	btree_setopt(2, 65, "Hello for the third time world!", tree);
	btree_setopt(3, 75, "This is another test!", tree);
	btree_setopt(4, 100, "Binary search tree example.", tree);
	if (argc > 1)
		while (*++argv != 0) {
			btree_t *branch;
			
			branch = search_tree(atoi(*argv), tree);
			if (branch != 0)
				print(branch);
			else
				printf("%d not found in tree.\n", atoi(*argv));
		}
	else
		btree_print(tree);
	btree_destroy(&tree);
	return 0;
}
