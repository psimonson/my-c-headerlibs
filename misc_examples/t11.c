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
		print(leaf->left);
		print(leaf->right);
		printf("======= Branch [%d] ======\n"
			"String: %s\n"
			"Test Integer: %d\n"
			"==== End Branch [%d] ====\n\n",
			leaf->key_value, leaf->opts.value, leaf->opts.test,
			leaf->key_value);
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
int main(void)
{
	btree_t *tree; /* without initializing to zero, use init_tree() */

	tree = init_tree(&insert, &setopts, &print, &destroy);
	tree->insert(1, &tree);
	tree->insert(2, &tree);
	tree->set_opts(0, 45, "Hello world!", tree);
	tree->set_opts(1, 50, "Hello again world!", tree);
	tree->set_opts(2, 65, "Hello for the third time world!", tree);
	tree->print(tree);
	tree->destroy(&tree);

	return 0;
}
