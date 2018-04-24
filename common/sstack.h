/**********************************************************
 * Simple Stack Structure
 * Create by Philip Simonson
 **********************************************************
 */

#ifndef PRS_SSTACK_H
#define PRS_SSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

struct stack {
	int top;
	unsigned capacity;
	int *array;
};
typedef struct stack stack_t;

static stack_t *stack_create(int capacity)
{
	stack_t *stack;
	stack = (stack_t*)malloc(sizeof(stack_t));
	if (stack == NULL)
		return NULL;
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*) malloc(stack->capacity * sizeof(int));
	if (stack->array == NULL) {
		free(stack);
		return NULL;
	}
	return stack;
}

static void stack_destroy(stack_t *stack)
{
	if (stack != NULL) {
		free(stack->array);
		free(stack);
	}
}

static int stack_is_full(stack_t *stack)
{
	return stack->top == stack->capacity-1;
}

static int stack_is_empty(stack_t *stack)
{
	return stack->top == -1;
}

static void stack_pushback(stack_t *stack, int arg1, ...)
{
	va_list arg_list;
	int arg;
	if (stack == NULL)
		return;

	va_start(arg_list, arg1);
	for (arg = arg1; arg != -1; arg = (int)va_arg(arg_list, int)) {
		if (stack_is_full(stack)) {
			int *p;
			p = (int*)realloc(stack->array, (stack->capacity*2)*sizeof(int));
			if (p == NULL)
				return;
			stack->array = p;
		}
		stack->array[++stack->top] = arg;
	}
	va_end(arg_list);
}

static int stack_popback(stack_t *stack)
{
	if (stack_is_empty(stack))
		return 0;
	return stack->array[stack->top--];
}
#endif
