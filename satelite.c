#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "satelite.h"

// Function that compares two satelites
int satelite_cmp(void *k1, void *k2)
{
	satelite_t *a = k1;
	satelite_t *b = k2;

	if (a->data > b->data) {
		return 1;
	} else if (a->data < b->data) {
		return -1;
	} else {
		return strcmp(a->name, b->name);
	}
}

// Function that read the input and put it in the min heap
heap_t *read_satelites(FILE *in)
{
	int n;
	heap_t *heap = heap_create(satelite_cmp, sizeof(satelite_t));

	fscanf(in, "%d", &n);

	for (int i = 0; i < n; i++) {
		satelite_t aux;
		aux.name = calloc(1, 15);

		if (!aux.name) {
			printf("ERROR AUX");
			exit(1);
		}

		fscanf(in, "%d %s", &aux.data, aux.name);
		aux.left = NULL;
		aux.right = NULL;
		aux.parent = NULL;
		heap_insert(heap, &aux);

	}
	return heap;
}
