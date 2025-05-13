#pragma once

#include <string.h>
#include <stdio.h>
#include "tasks.h"
#include "heap.h"
#include "satelite.h"
#include "BST.h"

// Function that reads the satelites form the input and genret a bst tree
bst_tree_t *create_sateleite_tree(FILE *in);

// Function that decodes the message
void decode(bst_tree_t *tree, FILE *in, FILE *out);