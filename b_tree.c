#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b_tree.h"
#include "satelite.h"
#include "queue.h"

// Function that creates a BST tree
b_tree_t *b_create(int data_size, int (*cmp)(void *, void *))
{
	b_tree_t *tree;

	tree = malloc(sizeof(b_tree_t));

	tree->root = NULL;
	tree->data_size = data_size;
	tree->cmp = cmp;

	return tree;
}

// Function that deletes the enitre tree recursive
void b_free(satelite_t *bst_node)
{
	if (!bst_node)
		return;

	b_free(bst_node->left);
	b_free(bst_node->right);
	free(bst_node->name);
	free(bst_node);
}

// Function that deletes the tree
void b_tree_free(b_tree_t *bst_tree)
{
	b_free(bst_tree->root);
	free(bst_tree);
}

// Function that makes the BFS algorithm
void print_levels(b_tree_t *tree, FILE *out)
{
	// Check if the tree is empty
	if (!tree->root)
		return;

	int count = 1, k = 1, l = 0;
	queue_t *q = q_create(sizeof(satelite_t *), 100);
	q_enqueue(q, &tree->root);

	while (!q_is_empty(q)) {
		satelite_t **b = q_fornt(q);
		satelite_t *a = *b;

		//Prints the information
		fprintf(out, "%d-%s ", a->data, a->name);

		if (a->left) {
			q_enqueue(q, &a->left);
			l++;
		}

		if (a->right) {
			q_enqueue(q, &a->right);
			l++;
		}

		if (count == k) {
			k = l;
			l = 0;
			fprintf(out, "\n");
			count = 0;
		}

		count++;
		q_dequeue(q);
	}

	fprintf(out, "\n");
	q_free(q);
}
