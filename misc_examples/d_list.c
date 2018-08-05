#include "../common/d_list.h"
#include <stdio.h>

int main()
{
	struct DLIST *list, *tmp;
	list = dlist_create_list(NULL, NULL, NULL, NULL, 1, "Philip");
	dlist_append_node(&list, 2, "Mark");
	dlist_append_node(&list, 3, "Bob");
	dlist_iterator_init(list);
	while ((tmp = dlist_iterator_next()) != NULL) {
		printf("Hello, %s.\n", ((struct DLIST_DATA *)tmp->data)->message);
	}
	if (!tmp)
		printf("No more data slots in list.\n");
	dlist_destroy(&list);
	return 0;
}
