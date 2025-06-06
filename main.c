#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"
#include "satelite.h"
#include "b_tree.h"
#include "functions.h"

int main(int argc, char **argv)
{

	FILE *in, *out;
	char task =  argv[1][2];

	// Opens the files
	in = fopen(argv[argc - 2], "rt");

	// Check if the file has open
	if (!in) {
		printf("ERROR OPEN FILE\n");
		exit(1);
	}

	out = fopen(argv[argc - 1], "wt");

	// Check if the file has open
	if (!out) {
		printf("ERROR OPEN FILE\n");
		exit(1);
	}

	b_tree_t *tree = create_sateleite_tree(in);

	// Choose the task
	if (task == '1') {
		print_levels(tree, out);
	} else if (task == '2') {
		decode(tree, in, out);
	} else if (task == '3') {
		encode(tree, in, out);
	} else if (task == '4') {
		common_parent(tree, in, out);
	}

	// Closes the opened files
	b_tree_free(tree);
	fclose(in);
	fclose(out);
	return 0;
}
