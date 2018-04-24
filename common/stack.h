/**************************************************************
 * stack.h - Simple stack fixed size.
 *
 * Created by Philip R. Simonson
 **************************************************************
 */

#ifndef PRS_STACK_H
#define PRS_STACK_H

#include <stdio.h>

#define STACK_MAXVAL 1024			/* MAX stack size */

/* stack data structure */
struct stack {
	int top;
	int val[STACK_MAXVAL];
	int pos[STACK_MAXVAL];
};
typedef struct stack stack_t;

/* stack_is_empty:  check to see if stack is empty */
static int stack_is_empty(stack_t *stack)
{
	return (stack->top == 0);
}

/* stack_is_full:  check to see if stack is full */
static int stack_is_full(stack_t *stack)
{
	return (stack->top == STACK_MAXVAL-1);
}

/* stack_push:  push values onto the stack */
static int stack_push(stack_t *stack, int val, int pos)
{
	if (stack_is_full(stack))
		return 1;
	stack->val[stack->top] = val;
	stack->pos[stack->top] = pos;
	stack->top++;
	return 0;
}

/* stack_pop:  pop values off top of stack */
static int stack_pop(stack_t *stack, int *val, int *pos)
{
	if (stack_is_empty(stack))
		return 1;
	stack->top--;
	*val = stack->val[stack->top];
	*pos = stack->pos[stack->top];
	return 0;
}
#endif
