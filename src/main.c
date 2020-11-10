#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

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

void iterate(void *** reference, int * dim_sizes, int * tier_sizes, int dimensions, size_t bytesize){
	// Initializing variables for the loop.
	int depth = 0;
	int next_dimension = 0;
	int current_tier = 0;
	void ** a = *reference;
	void ** b = NULL;

	// Linking pointers to memory locations in the rest of the memory block.
	while (depth < dimensions - 2){
		next_dimension = dim_sizes[depth+1];
		current_tier = tier_sizes[depth];
		b = &(a)[tier_sizes[depth]];

		for (int i = 0; i < current_tier; i++){
			a[i] = &(b)[i * next_dimension];
		}

		// Iterating to the next depth of the loop.
		depth++;
		a = &b[0];
	}

	// Explicitly assigning to a char ptr.
	char * c = &(a)[tier_sizes[dimensions-2]];

	// Assigning memory to the size of the byte.
	for (int i = 0; i < tier_sizes[dimensions-2]; i++){
		a[i] = c + bytesize * i * dim_sizes[dimensions-1];
	}
	return;
}

void * allocate_n_dimension_array(size_t bytesize, int n, ...){
	va_list valist;
	va_start(valist, n);

	int * dim_size = malloc(sizeof(int) * n);
	int * tier_size = malloc(sizeof(int) * n);

	int product = 1;
	int sum = 0;
	for (int i = 0; i < n; i++){
		dim_size[i] = va_arg(valist, int);
		product *= dim_size[i];
		tier_size[i] = product;
		sum += product;
	}

	size_t total_size = (sum - tier_size[n-1]) * sizeof(void*) + tier_size[n-1] * bytesize;

	void * a = calloc(1, total_size);

	//recurse((void ***) &a, dim_size, tier_size, 0, n, bytesize);
	iterate((void ***) &a, dim_size, tier_size, n, bytesize);

	va_end(valist);
	free(dim_size);
	free(tier_size);
	return a;
}



int main(void){
	char *** array = allocate_n_dimension_array(sizeof(char), 3,2,3,4);

	unsigned int n = 0;
	for (int a = 0; a < 2; a++){
		for (int b = 0; b < 3; b++){
			for (int c = 0; c < 4; c++){
				array[a][b][c] = n++;
			}
		}
	}

	for (int a = 0; a < 2; a++){
		for (int b = 0; b < 3; b++){
			for (int c = 0; c < 4; c++){
				printf("%d, ", array[a][b][c]);
			}
		}
	}

	free(array);
	return 0;
}

int foo(void)
{
	int dim_sizes[3] = {2, 3, 4};
	int tier_sizes[3] = {2, 6, 24};

    char *** a = malloc(2 * sizeof(char**) + 2 * 3 * sizeof(char*) + 2 * 3 * 4 * sizeof(char));

	recurse((void ***) &a, dim_sizes, tier_sizes, 0, 3, sizeof(char));

	int n = 0;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 4; k++){
				a[i][j][k] = n++;
				printf("%d, ", a[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
    return 0;
}

/*
int main(void)
{
    char *** a = malloc(2 * sizeof(char**));
    char ** b = malloc(2 * 3 * sizeof(char*));
    char * c = malloc(2 * 3 * 4 * sizeof(char));
    
    for (int i = 0; i < 2; i++)
        a[i] = &b[i * 3];

    for (int j = 0; j < 6; j++)
        b[j] = &c[j * 4];

    int n = 0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 4; k++){
                a[i][j][k] = n++;
                printf("%d, ", a[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}*/

/*
	char ** b = &a[2];
	char * c = &b[6];
  
    for (int i = 0; i < 2; i++)
        a[i] = &(&a[2])[i * 3];

    for (int j = 0; j < 6; j++)
        b[j] = &(&b[6])[j * 4];
*/