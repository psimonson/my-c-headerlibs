#include "../common/logger.h"
#include "../common/sstack.h"

#define LOG_NAME "log6.txt"

const char key[] = "298374dkfjlsdjfsdkjf893uFKJDFJF";

/* program to test the simple stack header */
int main(int argc, char *argv[])
{
	stack_t *stack;
	int val;

	stack = stack_create(8);
	if (stack == NULL)
		return -1;
	do_log(write_log, LOG_NAME, "Stack created!\n");
	stack_pushback(stack, 1, 2, 3, 4, 5, -1);
	do_log(append_log, LOG_NAME, "Numbers pushed back onto stack.\n");
	while (!stack_is_empty(stack)) {
		val = stack_popback(stack);
		printf("Val is %d\n", val);
		do_log(append_log, LOG_NAME, "Val is %d\n", val);
	}
	stack_destroy(stack);
	return 0;
}
