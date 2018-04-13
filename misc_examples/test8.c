#include "../common/queue.h"

int main()
{
	queue_t queue;
	queue_add(&queue, 1, 1);
	queue_add(&queue, 2, 2);
	queue_add(&queue, 3, 3);
	while (!queue_is_empty(&queue)) {
		int val, pos;
		queue_get(&queue, &val, &pos);
		printf("Value: %d\t-\tPosition: %d\n", val, pos);
	}
	return 0;
}
