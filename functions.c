#include <string.h>
#include <stdio.h>
#include "tasks.h"
#include "heap.h"
#include "satelite.h"
#include "BST.h"
#include "functions.h"


void
print_data(void *data)
{
	satelite_t *node = data;
    printf("%d %s\n", node->data, node->name);
}

// Function that reads the satelites form the input and genret a bst tree
bst_tree_t *create_sateleite_tree(FILE *in) 
{
	heap_t *heap = read_satelites(in);

	while (heap->size > 1) {
		satelite_t aux, *a, *b;
		a = heap->arr; // first satelite
		b = heap->arr + heap->data_size; // second satelite

		satelite_t *left = malloc(sizeof(satelite_t));
		satelite_t *right = malloc(sizeof(satelite_t));

		memcpy(left, a, sizeof(satelite_t));
		memcpy(right, b, sizeof(satelite_t));

		// Making the new satelite
		aux.data = a->data + b->data;
		strcpy(aux.name, a->name);
		strcat(aux.name, b->name);
		aux.left = left;
		aux.right = right;

		heap_pop(heap);
		heap_pop(heap);

		heap_insert(heap, &aux);
	}

	// Creates the tree
	satelite_t *b = heap_top(heap);
	bst_tree_t *tree = bst_create(sizeof(satelite_t), satelite_cmp);

	tree->root = malloc(sizeof(satelite_t));
	memcpy(tree->root, b, tree->data_size);
	heap_pop(heap);

	// Freeing the heap used
	heap_free(heap);

	return tree;
}

// Function that decodes the message
void decode(bst_tree_t *tree, FILE *in, FILE *out)
{
	int n;
	char line[1001];

	fscanf(in, "%d", &n);

	// Read the lines to decode
	for (int i = 0; i < n; i++) {
		fscanf(in, "%s", line);

		int len = strlen(line);
		satelite_t *p = tree->root;

		int j = 0;
		// The algorithm for the message
		while(j < len) {
				
			char c = line[j];

			if (c == '0') {
					if (p->left == NULL) {
					fprintf(out, "%s ", p->name);
					p = tree->root;
				} else {
					p = p->left;
					j++;
				}
			} else {
				if (p->right == NULL) {
					fprintf(out, "%s ", p->name);
					p = tree->root;
				} else  {
					p = p->right;
					j++;
				}
			}
		}
		fprintf(out ,"%s\n", p->name);
	}
}

// Functiont that encode a message
void encode(bst_tree_t *tree, FILE *in, FILE *out)
{
	
}