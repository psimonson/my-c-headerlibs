#include "../common/btree.h"

/* program to simply test my binary tree header library */
int main(void)
{
	btree_t *tree; /* without initializing to zero, use init_tree() */

	tree = init_tree(&print_whole_tree, NULL);
/*	tree = init_tree(NULL, NULL); */
	insert_tree(1, &tree);
	insert_tree(2, &tree);
	tree->set_opts(tree, 0, "Hello world!");
	tree->set_opts(tree, 1, "Hello again world!");
	tree->set_opts(tree, 2, "Hello for the third time world!");
	tree->print(tree);
	destroy_tree(tree);

	return 0;
}
