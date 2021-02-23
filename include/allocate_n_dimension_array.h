#ifndef _ALLOCATE_H
#define _ALLOCATE_H

typedef void *** ptr_array_ptr;
typedef void ** ptr_array;

//void recurse(void *** reference, int * dim_sizes, int * tier_sizes, int depth, int dimensions, size_t bytesize);

void iterate(ptr_array_ptr reference, int * dim_sizes, int * tier_sizes, int dimensions, size_t bytesize);

void * allocate_n_dimension_array(size_t bytesize, int n, ...);

#endif



