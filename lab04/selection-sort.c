#include <stdio.h>
#include <stdlib.h>



void sort_smallest(int *arr, int startIndex, int endIndex) {
	int smallestIndex=startIndex;
	int i;
	int tmp; 

	printf("start from index: %d, end with index: %d\n", startIndex, endIndex);

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

	sort(arr, size);

	for(i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	
	free(arr);
	return 0;
}
