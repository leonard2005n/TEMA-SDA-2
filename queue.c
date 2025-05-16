#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Function that creates a queue
queue_t *q_create(int data_size, int max_size)
{
	queue_t *queue = calloc(1, sizeof(queue_t));

	if (!queue) {
		printf("ERROR QUEUE\n");
		exit(1);
	}

	queue->max_size = max_size;
	queue->data_size = data_size;
	queue->buff = calloc(max_size, sizeof(void *));

	if (!queue->buff) {
		printf("ERROR QUEUE\n");
		exit(1);
	}

	for (int i = 0; i < max_size; i++)
		queue->buff[i] = calloc(1, data_size);

	return queue;
}

// Function that returs the size of the queue
int q_get_size(queue_t *q)
{
	return q->size;
}

// Function that return 1 if the queue is empty
int q_is_empty(queue_t *q)
{
	if (q->size == 0)
		return 1;

	return 0;
}

// Function that returns the first value
void *q_fornt(queue_t *q)
{
	if (q->size == 0)
		return NULL;

	return q->buff[q->read_idx % q->max_size];
}

// Function that dequeue an element
int q_dequeue(queue_t *q)
{
	if (q->size == 0)
		return 0;

	q->size--;
	q->read_idx++;
	return 1;
}

// Function that enqueue an element
int q_enqueue(queue_t *q, void *new_data)
{
	if (q->size == q->max_size)
		return 0;

	q->size++;
	memcpy(q->buff[q->write_idx % q->max_size], new_data, q->data_size);
	q->write_idx++;
	return 1;
}

// Function that clears the queue
void q_clear(queue_t *q)
{
	while (q->size)
		q_dequeue(q);
}

// Function that frees the queue
void q_free(queue_t *q)
{
	for (int i = 0; i < q->max_size; i++)
		free(q->buff[i]);
	free(q->buff);
	free(q);
}
