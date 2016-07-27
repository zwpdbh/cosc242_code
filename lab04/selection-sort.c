#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

void sort_smallest(int *arr, int startIndex, int endIndex) {
	int smallestIndex=startIndex;
	int i;
	int tmp; 


	for(i=startIndex+1; i<=endIndex; i++) {
		if(arr[i]<=arr[smallestIndex]) {
			smallestIndex = i;
		}	
	}
	
	tmp = arr[startIndex];
	arr[startIndex] = arr[smallestIndex];
	arr[smallestIndex] = tmp;
}

void sort(int *arr, int size) {
	int i;
	for(i = 0; i<size-1; i++) {
		sort_smallest(arr, i, size-1);
	}
}



int main(void) {
	int size;
	int *arr;
	int i;
	clock_t start, end;
	
	/*
	printf("Enter an integer to create an array of int: ");
	scanf("%d", &size);
	
	arr = malloc(size * sizeof(arr[0]));
	if(arr == NULL) {
		printf("Memory allocation failed!\n");
		return 1;
	}
	for(i = 0; i<size; i++) {
		arr[i] = rand() % size;
	}
	
	for(i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	*/
	size = 0;
	while (size < ARRAY_MAX && 1 == scanf("%d", &arr[size])) {
		size++;
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
