#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_MAX 30000

void sort(int *arr, int size) {
	int j = 1;
	int i;
	for(j = 1; j < size; j++) {
		int key = arr[j];
		i = j - 1;
		while(i >= 0 && arr[i] > key) {
			arr[i+1] = arr[i];
			i--;
		}
		arr[i+1] = key;
	}
}

int main(void) {
	int size;
	int *arr;
	int i;
	clock_t start, end;
	
	/*
	printf("Enter the number to create a dynamic int array: ");
		
		scanf("%d", &size);
		
		arr = malloc(size * sizeof(arr[0]));
		if(NULL == arr) {
			printf("error for allocation");
			return 1;
		}
		

		for(i = 0; i < size; i++) {
			arr[i] = rand() % size;
		}
		for(i = 0; i < size; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");

	*/
	size = 0; 
	while (size < ARRAY_MAX && 1 == scanf("%d", &arr[size])) {
		statements
	}
	
	start = clock();
	sort(arr, size);
	end = clock();
	
	for(i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	fprintf(stderr, "%d %f\n", size, (end-start)/(double)CLOCKS_PER_SEC);
	/*free(arr);*/
	return 0;
}
