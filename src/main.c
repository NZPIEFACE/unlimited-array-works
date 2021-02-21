#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include <main.h>
#include <allocate_n_dimension_array.h>



int main(void){
	int *** array = allocate_n_dimension_array(sizeof(long int), 3, 2, 2, 2);

	for (int i = 0; i < 14;){
		printf("%p, %p", (void *) &array[i], (void *) array[i]);


		if (i != 0){
			printf(", %ld", (char *) array[i] - (char *) array[i-1]);
		}

		printf("\n");

		i++;

		if (i == 2 || i == 6 || i == 14){
			printf("\n");
		}
	}



	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			for (int k = 0; k < 2; k++){
				array[i][j][k] = 6;

				printf("%p, %d\n", &array[i][j][k], array[i][j][k]);
			}
		}
	}




	free(array);
	return 0;
}
