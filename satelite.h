#pragma once

#include "heap.h"

// The struct for the setilites
typedef struct satelite_t satelite_t;
struct satelite_t {
	int data;
	char *name;
	satelite_t *left, *right, *parent;
};

// Function that compares two satelites
int satelite_cmp(void *k1, void *k2);

// Function that read the input and put it in the min heap
heap_t *read_satelites(FILE *in);
