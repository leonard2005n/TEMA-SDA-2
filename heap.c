#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

// Function that creates an heap
heap_t *heap_create(int (*cmp)(void *, void *), int data_size)
{

	heap_t *heap = (heap_t *)malloc(sizeof(heap_t));

	heap->arr = malloc(5 * data_size);
	heap->capacity = 5;
	heap->data_size = data_size;
	heap->size = 0;
	heap->cmp = cmp;

	return heap;
}

// Function that fixex the inserrion of the heap
void push_up(heap_t *heap, int pos)
{
	char *arr = heap->arr;
	int p = GO_UP(pos);

	if (pos == 0)
		return;

	if (heap->cmp(&arr[p * heap->data_size], &arr[pos * heap->data_size]) > 0) {

		// Switches the value with the parent
		void *aux = malloc(heap->data_size);
		memcpy(aux, &arr[p * heap->data_size], heap->data_size);
		memcpy(&arr[p * heap->data_size],
			   &arr[pos * heap->data_size], heap->data_size);
		memcpy(&arr[pos * heap->data_size], aux, heap->data_size);
		free(aux);

		push_up(heap, p);
	}

}

// Function that iserts a value into the heap
void heap_insert(heap_t *heap, void *data)
{
	char *arr = heap->arr;

	memcpy(&arr[heap->size * heap->data_size], data, heap->data_size);

	for (int i = heap->size; i > 0; i--) {
		if (heap->cmp(&arr[i * heap->data_size], &arr[(i - 1) * heap->data_size]) < 0) {
			void *aux = malloc(heap->data_size);
			memcpy(aux, &arr[i * heap->data_size], heap->data_size);
			memcpy(&arr[i * heap->data_size],
				&arr[(i - 1) * heap->data_size], heap->data_size);
			memcpy(&arr[(i - 1) * heap->data_size], aux, heap->data_size);
			free(aux);
		}
	}

	heap->size++;

	if (heap->size == heap->capacity) {

		heap->capacity *= 2;
		heap->arr = realloc(heap->arr, heap->capacity * heap->data_size);

	}
}

// Function that perfoms the push down
void push_down(heap_t *heap, int pos)
{
	char *arr = heap->arr;
	int p = pos;
	int r = GO_RIGHT(pos); // right son
	int l = GO_LEFT(pos); // left son
	int min = p; // minimu

	// compares with the left child
	if (pos >= heap->size)
		return;

	if (l < heap->size) {

		if (heap->cmp(&arr[min * heap->data_size],
					  &arr[l * heap->data_size]) > 0)
			min = l;

	}

	// compares with the right child
	if (r < heap->size) {

		if (heap->cmp(&arr[min * heap->data_size],
					  &arr[r * heap->data_size]) > 0)
			min = r;

	}

	// Moves the values
	if (min != p) {
		void *aux = malloc(heap->data_size);
		memcpy(aux, &arr[p * heap->data_size], heap->data_size);
		memcpy(&arr[p * heap->data_size],
			   &arr[min * heap->data_size], heap->data_size);
		memcpy(&arr[min * heap->data_size], aux, heap->data_size);
		free(aux);
		push_down(heap, min);
	}

}

// Function that removes the first elemnt of the heap
void heap_pop(heap_t *heap)
{
	char *arr = heap->arr;

	memcpy(&arr[0], &arr[(heap->size - 1) * heap->data_size], heap->data_size);
	heap->size--;

	push_down(heap, 0);
}

// Returns the value at the top of the heap
void *heap_top(heap_t *heap)
{
	return heap->arr;
}

// Checks if the heap is empty
int heap_empty(heap_t *heap)
{
	return heap->size == 0;
}

// Function that frees the heap
void heap_free(heap_t *heap)
{

	free(heap->arr);
	free(heap);

}
