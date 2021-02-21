#ifndef _ALLOCATE_H
#define _ALLOCATE_H

void recurse(void *** reference, int * dim_sizes, int * tier_sizes, int depth, int dimensions, size_t bytesize);

void iterate(void *** reference, int * dim_sizes, int * tier_sizes, int dimensions, size_t bytesize);

void * allocate_n_dimension_array(size_t bytesize, int n, ...);

#endif



