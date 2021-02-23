#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include <allocate_n_dimension_array.h>

// Function I can't get working
/*
void recurse(void *** reference, int * dim_sizes, int * tier_sizes, int depth, int dimensions, size_t bytesize){
	void ** a = *reference;
	void ** b = &(a)[tier_sizes[depth]];
	int current_dimension_size = dim_sizes[depth];
	int next_dimension_size = dim_sizes[depth+1];
	
	if (depth == dimensions - 2){
		char * b = &(a)[tier_sizes[depth]];
		for (int i = 0; i < current_dimension_size; i++){
			a[i] = &b[0] + i * next_dimension_size;
		}
	}
	else {
		for (int i = 0; i < current_dimension_size; i++){
			a[i] = &(b)[i * next_dimension_size];

			recurse((void *** ) &a[i], dim_sizes, tier_sizes, depth +1, dimensions, bytesize);
		}
	}

	return;
}
*/


// Iterative version of the function
	// reference is the memory address of the array
void iterate(const ptr_array_ptr reference, const int dimensions, const size_t bytesize, const int * dim_sizes, const int * tier_sizes){
	// Initializing variables for the loop.
	int depth = 0;
	int next_dimension_size = 0;
	int current_tier_size = 0;
	ptr_array address = *reference; // Location of the first bit of memory in the array
	ptr_array destination = NULL;

	// Linking pointers to memory locations in the rest of the memory block.
	while (depth < dimensions - 2){
		next_dimension_size = dim_sizes[depth+1];
		current_tier_size = tier_sizes[depth];

		// The first destination is the first bit of memory after the current tier
		destination = &(address[current_tier_size]);

		// Link the address of the destination to the current tier
		for (int i = 0; i < current_tier_size; i++){
			address[i] = (void *) &(destination[i * next_dimension_size]);
		}

		// Iterating to the next depth of the loop.
		depth++;
		address = destination; 
	}

	// Explicitly assigning to a char pointer since char has size of 1.
	char * storage_start = (char *) &(address[tier_sizes[depth]]);

	// Assigning memory to the size of the deepest array.
	for (int i = 0; i < tier_sizes[depth]; i++){
		address[i] = storage_start + dim_sizes[dimensions-1] * bytesize * i;
	}
	return;
}

void * allocate_n_dimension_array(const size_t bytesize, const int n, const int * dim_size){
	int * tier_size = malloc(sizeof(int) * n);

	int product = 1;
	int sum = 0;

	for (int i = 0; i < n; i++){
		product *= dim_size[i]; // Size of a tier is the product of all dimensions up to that point
		tier_size[i] = product;

		sum += product; // Running sum for the total size
	}

	// The first tiers are all pointers. The last tier is the stored information.
	size_t total_size = (sum - tier_size[n-1]) * sizeof(void *) + tier_size[n-1] * bytesize;
	void * a = calloc(1, total_size);

	// Explicit casting to void *** since void ** and void * is required
	iterate((ptr_array_ptr) &a, n, bytesize, dim_size, tier_size);

	free(tier_size);

	return a;
}