#include "../common/btree.h"

/* program to simply test my binary tree header library */
int main(void)
{
	btree_t *tree; /* without initializing to zero, use init_tree() */

	tree = init_tree();
	btree_insert(1, &tree);
	btree_insert(2, &tree);
	btree_setopt(tree, 0, "Hello world!");
	btree_setopt(tree, 1, "Hello again world!");
	btree_setopt(tree, 2, "Hello for the third time world!");
	btree_print(tree);
	btree_destroy(&tree);

	return 0;
}
