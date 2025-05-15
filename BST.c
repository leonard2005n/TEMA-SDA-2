#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BST.h"
#include "satelite.h"
#include "queue.h"

// Create a node for BST
satelite_t *node_create(void *data, int data_size)
{
	satelite_t *node;

	node = calloc(1, sizeof(satelite_t));

	// Copinng the memory to node
	memcpy(node, data, data_size);

	return node;
}

// Function that creates a BST tree
bst_tree_t *bst_create(int data_size, int (*cmp)(void *, void *))
{
	bst_tree_t *tree;

	tree = malloc(sizeof(bst_tree_t));

	tree->root = NULL;
	tree->data_size = data_size;
	tree->cmp = cmp;

	return tree;
}

// Function that isertes a tree
void bst_tree_insert(bst_tree_t *bst_tree, void *data)
{
	int rc;
	satelite_t *root	= bst_tree->root;
	satelite_t *parent	= NULL;
	satelite_t *node	= node_create(data, bst_tree->data_size);

	if (!bst_tree->root) {
		bst_tree->root = node;
		return;
	}

	parent = root;
	while (1) {
		rc = bst_tree->cmp(parent, node);
		if (rc < 0) {
			if (!parent->right) {
				parent->right = node;
				break;
			} else {
				parent = parent->right;
			}
		} else if (rc > 0) {
			if (!parent->left) {
				parent->left = node;
				break;
			} else {
				parent = parent->left;
			}
		} else {
			break;
		}
	}
}

// Function that removes the node
satelite_t *bst_node_remove(satelite_t *bst_node, void *data, int data_size,
							int (*cmp)(void *, void *))
{
	if (!bst_node)
		return NULL;

	satelite_t *tmp, *aux;
	int rc = cmp(data, bst_node);

	if (rc < 0) {
		tmp = bst_node_remove(bst_node->left, data, data_size, cmp);
		bst_node->left = tmp;
	} else if (rc > 0) {
		tmp = bst_node_remove(bst_node->right, data, data_size, cmp);
		bst_node->right = tmp;
	} else {
		aux = NULL;
		if (!bst_node->left && !bst_node->right) {
			tmp = bst_node;
			bst_node = NULL;
		} else if (bst_node->right && bst_node->left) {
			tmp = bst_node->right;

			while (tmp->left) {
				aux = tmp;
				tmp = tmp->left;
			}

			if (aux)
				aux->left = tmp->right;

			tmp->left = bst_node->left;
			if (bst_node->right != tmp)
				tmp->right = bst_node->right;

			aux = bst_node;
			bst_node = tmp;
			tmp = aux;

		} else if (bst_node->left) {

			tmp = bst_node;
			bst_node = bst_node->left;

		} else if (bst_node->right) {

			tmp = bst_node;
			bst_node = bst_node->right;
		}

		free(tmp);
	}

	return bst_node;
}

// Function that removes the node
void bst_tree_remove(bst_tree_t *bst_tree, void *data)
{
	bst_tree->root = bst_node_remove(bst_tree->root, data,
									 bst_tree->data_size, bst_tree->cmp);
}

// Function that deletes the enitre tree recursive
void bst_free(satelite_t *bst_node)
{
	if (!bst_node)
		return;

	bst_free(bst_node->left);
	bst_free(bst_node->right);

	free(bst_node);
}

// Function that deletes the tree
void bst_tree_free(bst_tree_t *bst_tree)
{
	bst_free(bst_tree->root);
	free(bst_tree);
}

// Function that makes the BFS algorithm
void print_levels(bst_tree_t *tree, FILE *out)
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
