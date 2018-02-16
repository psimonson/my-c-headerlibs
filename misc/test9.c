#include "../common/stack.h"

int main()
{
	stack_t stack;
	stack_push(&stack, 1, 1);
	stack_push(&stack, 2, 2);
	stack_push(&stack, 3, 3);
	while (!stack_is_empty(&stack)) {
		int val, pos;
		stack_pop(&stack, &val, &pos);
		printf("Value: %d\t-\tPosition: %d\n", val, pos);
	}
	return 0;
}
