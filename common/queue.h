/******************************************************************
 * queue.h - Simple queue header library
 * -------------------------------------
 * Created by Philip "5n4k3" Simonson
 ******************************************************************
 */

#ifndef PRS_QUEUE_H
#define PRS_QUEUE_H

#include <stdio.h>

#define QUEUE_MAXVAL 1024

/* simple queue structure data type */
struct queue {
	int beg;
	int end;
	int val[QUEUE_MAXVAL];
	int pos[QUEUE_MAXVAL];
};
typedef struct queue queue_t;

/* queue_is_full:  check if queue is full */
static int queue_is_full(queue_t *queue)
{
	return (queue->end == QUEUE_MAXVAL-1);
}

/* queue_is_empty:  check if queue is empty */
static int queue_is_empty(queue_t *queue)
{
	return (queue->beg == queue->end);
}

/* queue_add:  add values to the end of a queue */
static int queue_add(queue_t *queue, int val, int pos)
{
	if (queue_is_full(queue))
		return 1;
	queue->val[queue->end] = val;
	queue->pos[queue->end] = pos;
	queue->end++;
	if (queue->end <= queue->beg)
		queue->beg = 0;
	return 0;
}

/* queue_get:  get values from the end of a queue */
static int queue_get(queue_t *queue, int *val, int *pos)
{
	if (queue_is_empty(queue))
		return 1;
	*val = queue->val[queue->beg];
	*pos = queue->pos[queue->beg];
	queue->beg++;
	if (queue->beg >= queue->end)
		queue->beg = queue->end;
	return 0;
}
#endif
