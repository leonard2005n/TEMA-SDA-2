#pragma once

#include <stdio.h>
#include <string.h>
#include "satelite.h"

// BST struct
typedef struct {
	satelite_t *root; // root of the three
	int data_size; // data_size
	int (*cmp)(void *key1, void *key2);

} b_tree_t;

// Function that creates a BST tree
b_tree_t *b_create(int data_size, int (*cmp)(void *, void *));

// Function that deletes the enitre tree recursive
void b_free(satelite_t *bst_node);

// Function that deletes the tree
void b_tree_free(b_tree_t *bst_tree);

// Function that makes the BFS algorithm
void print_levels(b_tree_t *tree, FILE *out);
