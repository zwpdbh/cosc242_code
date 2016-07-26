#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 10

void multiple_by_3(int *a, int n) {
	int i;
	
	for(i = 0; i < n; i++) {
		a[i] *= 3;
	}
}

int main(void) {
	
	int my_array[ARRAY_SIZE];
	int counter = 0;
	int i;
	
	while (counter < ARRAY_SIZE && 1 == scanf("%d", &my_array[counter])) {
		counter++;
	}
	
	multiple_by_3(my_array, counter);
	for (i=0;i<counter;i++) {
		printf("%d\n", my_array[i]);
	}
	
	return 0;
}
