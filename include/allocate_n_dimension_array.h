#ifndef _ALLOCATE_H
#define _ALLOCATE_H

typedef void *** ptr_array_ptr;
typedef void ** ptr_array;

//void recurse(void *** reference, int * dim_sizes, int * tier_sizes, int depth, int dimensions, size_t bytesize);

void iterate(const ptr_array_ptr reference, const int dimensions, const size_t bytesize, const int * dim_sizes, const int * tier_sizes);

void * allocate_n_dimension_array(const size_t bytesize, const int n, const int * dim_size);

#endif



