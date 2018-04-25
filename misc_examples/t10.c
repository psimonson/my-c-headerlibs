#include "../common/btree.h"

/* program to simply test my binary tree header library */
int main(void)
{
	btree_t *tree; /* without initializing to zero, use init_tree() */

	tree = init_tree();
	tree->insert(1, &tree);
	tree->insert(2, &tree);
	tree->set_opts(tree, 0, "Hello world!");
	tree->set_opts(tree, 1, "Hello again world!");
	tree->set_opts(tree, 2, "Hello for the third time world!");
	tree->print(tree);
	tree->destroy(&tree);

	return 0;
}
