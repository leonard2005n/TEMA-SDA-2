#pragma once

typedef struct {
 	int max_size;
 	int size;
	int data_size;
	int read_idx;
	int write_idx;
	void **buff;
}queue_t;

// Function that creates a queue
queue_t *q_create(int data_size, int max_size);

// Function that returs the size of the queue
int q_get_size(queue_t *q);

// Function that return 1 if the queue is empty
int q_is_empty(queue_t *q);

// Function that returns the first value
void *q_fornt(queue_t *q);

// Function that dequeue an element
int q_dequeue(queue_t *q);

// Function that enqueue an element
int q_enqueue(queue_t *q, void *new_data);

// Function that clears the queue
void q_clear(queue_t *q);

// Function that frees the queue
void q_free(queue_t *q);