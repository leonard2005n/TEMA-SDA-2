#include <string.h>
#include <stdio.h>
#include "heap.h"
#include "satelite.h"
#include "b_tree.h"
#include "functions.h"

// Function that puts the parents into the nodes
void link_parents(satelite_t *node)
{
	// Link with the left node
	if (node->left) {
		node->left->parent = node;
		link_parents(node->left);
	}

	// Link with the right node
	if (node->right) {
		node->right->parent = node;
		link_parents(node->right);
	}
}

// Function that reads the satelites form the input and genret a bst tree
b_tree_t *create_sateleite_tree(FILE *in)
{
	heap_t *heap = read_satelites(in);

	while (heap->size > 1) {

		satelite_t aux, *a, *b;

		a = heap->arr; // first satelite

		satelite_t *left = malloc(sizeof(satelite_t));
		satelite_t *right = malloc(sizeof(satelite_t));

		if (!left || !right) {
			printf("ERROR CREATE SATELITE\n");
			exit(1);
		}

		// Copy the memory into the left node
		memcpy(left, a, sizeof(satelite_t));
		heap_pop(heap);

		b = heap->arr; // second satelite

		// Copy the memory into the right node
		memcpy(right, b, sizeof(satelite_t));
		heap_pop(heap);

		// Making the new satelite
		aux.data = left->data + right->data;
		aux.name = calloc(1, strlen(left->name) + strlen(right->name) + 1);
		strcpy(aux.name, left->name);
		strcat(aux.name, right->name);
		aux.left = left;
		aux.right = right;

		heap_insert(heap, &aux);

	}

	// Creates the tree
	satelite_t *b = heap_top(heap);
	b_tree_t *tree = b_create(sizeof(satelite_t), satelite_cmp);

	tree->root = malloc(sizeof(satelite_t));

	if (!tree->root) {
		printf("ERROR ROOT\n");
		exit(1);
	}

	memcpy(tree->root, b, tree->data_size);
	heap_pop(heap);

	// Freeing the heap used
	heap_free(heap);

	link_parents(tree->root);
	tree->root->parent = NULL;

	return tree;
}

// Function that decodes the message
void decode(b_tree_t *tree, FILE *in, FILE *out)
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
		if (!p->left && !p->right)
			fprintf(out, "%s", p->name);
		fprintf(out, "\n");
	}
}

// Recursive functiont to determine the message
static void r_encode(satelite_t *node, char *name, FILE *out)
{
	int ok = 0;

	// Breaking function
	if (!node->left && !node->right)
		return;

	// If the node is on the left
	if (node->left && !ok) {
		char *p = strstr(node->left->name, name);
		if (p != 0) {

			// Is a case if the node name is K1 and you need to find K1
			// it can match with K11
			while (strlen(name) == 2 &&
				   strchr("0123456789", p[2]) != 0 && p[2] != 0) {
				p = strstr(p + 1, name);

				if (p == 0)
					break;
			}

			if (p != 0) {
				fprintf(out, "0");
				r_encode(node->left, name, out);
				ok = 1;
			}
		}
	}

	// If the node is on the right
	if (node->right && !ok) {
		char *p = strstr(node->right->name, name);
		if (p != 0) {

			// Is a case if the node name is K1 and you need to find K1
			// it can match with K11
			while (strlen(name) == 2 &&
				   strchr("0123456789", p[2]) != 0 && p[2] != 0) {
				p = strstr(p + 1, name);
				if (p == 0)
					break;
			}

			if (p != 0) {
				fprintf(out, "1");
				r_encode(node->right, name, out);
				ok = 1;
			}
		}
	}
}

// Functiont that encode a message
void encode(b_tree_t *tree, FILE *in, FILE *out)
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
void common_parent(b_tree_t *tree, FILE *in, FILE *out)
{
	int n;
	char name[20];
	satelite_t *p = tree->root;

	fscanf(in, "%d %s", &n, name);

	// Finding the first parent of the first node
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
