#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Get the index of the parent
#define GO_UP(x) (((x) - 1) >> 1)

// Get the index of the left child
#define GO_LEFT(x) (((x) << 1) + 1)

// Get the index of the right child
#define GO_RIGHT(x) (((x) << 1) + 2)

//
typedef struct {
	void *arr;
	int size;
	int capacity;
	int data_size;
	int (*cmp)(void *key1, void *key2);
} heap_t;


// Function that creates an heap
heap_t *heap_create(int (*cmp)(void *, void *), int data_size);

// Function that fixex the inserrion of the heap
void push_up(heap_t *heap, int pos);

// Function that iserts a value into the heap
void heap_insert(heap_t *heap, void *data);

// Function that perfoms the push down
void push_down(heap_t *heap, int pos);

// Function that removes the first elemnt of the heap
void heap_pop(heap_t *heap);

// Returns the value at the top of the heap
void *heap_top(heap_t *heap);

// Checks if the heap is empty
int heap_empty(heap_t *heap);

// Function that frees the heap
void heap_free(heap_t *heap);
