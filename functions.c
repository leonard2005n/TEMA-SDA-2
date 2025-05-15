#include <string.h>
#include <stdio.h>
#include "tasks.h"
#include "heap.h"
#include "satelite.h"
#include "BST.h"
#include "functions.h"

// Function that puts the parents into the nodes
void link_parents(satelite_t *node)
{
	if (node->left) {
		node->left->parent = node;
		link_parents(node->left);
	}

	if (node->right) {
		node->right->parent = node;
		link_parents(node->right);
	}
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
		// printf("%d %s, %d %s\n", a->data, a->name, b->data, b->name);

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

	link_parents(tree->root);
	tree->root->parent = NULL;

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
		while (j < len) {

			char c = line[j];

			if (c == '0') {
				if (!p->left) {
					fprintf(out, "%s ", p->name);
					p = tree->root;
				} else {
					p = p->left;
					j++;
				}
			} else {
				if (!p->right) {
					fprintf(out, "%s ", p->name);
					p = tree->root;
				} else  {
					p = p->right;
					j++;
				}
			}
		}
		fprintf(out, "%s\n", p->name);
	}
}

// Recursive functiont to determine the message
static void r_encode(satelite_t *node, char *name, FILE *out)
{
	if (!node->left && !node->right)
		return;

	if (node->left) {
		if (strstr(node->left->name, name) != 0) {
			fprintf(out, "0");
			r_encode(node->left, name, out);
		}
	}

	if (node->right) {
		if (strstr(node->right->name, name) != 0) {
			fprintf(out, "1");
			r_encode(node->right, name, out);
		}
	}
}

// Functiont that encode a message
void encode(bst_tree_t *tree, FILE *in, FILE *out)
{
	int n;
	char name[20];

	fscanf(in, "%d", &n);

	for (int i = 0; i < n; i++) {
		fscanf(in, "%s", name);

		satelite_t *p = tree->root;
		r_encode(p, name, out);
	}

	fprintf(out, "\n");
}

// Finds the common parents of a bunch of satelites
void common_parent(bst_tree_t *tree, FILE *in, FILE *out)
{
	int n;
	char name[20];

	fscanf(in, "%d %s", &n, name);

	satelite_t *p = tree->root;

	while (strcmp(p->name, name) != 0) {
		if (p->left) {
			if (strstr(p->left->name, name) != 0) {
				p = p->left;
			}
		}

		if (p->right) {
			if (strstr(p->right->name, name) != 0) {
				p = p->right;
			}
		}
	}

	// Finding the comun parent
	for (int i = 1; i < n; i++) {

		fscanf(in, "%s", name);

		while (1) {

			if (!p->parent)
				break;

			if (strstr(p->name, name) != 0)
				break;

			p = p->parent;
		}
	}

	fprintf(out, "%s\n", p->name);
}
