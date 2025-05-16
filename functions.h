#pragma once

#include <string.h>
#include <stdio.h>
#include "heap.h"
#include "satelite.h"
#include "b_tree.h"

// Function that reads the satelites form the input and genret a bst tree
b_tree_t *create_sateleite_tree(FILE *in);

// Function that decodes the message
void decode(b_tree_t *tree, FILE *in, FILE *out);

// Functiont that encode a message
void encode(b_tree_t *tree, FILE *in, FILE *out);

// Finds the common parents of a bunch of satelites
void common_parent(b_tree_t *tree, FILE *in, FILE *out);
