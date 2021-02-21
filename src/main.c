#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include <main.h>
#include <allocate_n_dimension_array.h>



int main(void){
	int dims[3] = {2, 100};
	char ** array = allocate_n_dimension_array(sizeof(int), 2, dims[0], dims[1]);

	free(array);
	return 0;
}
