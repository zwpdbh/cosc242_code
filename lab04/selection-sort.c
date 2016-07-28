#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/* given a array, select the smallest one in the range of
 * array and move it to the first position indicated by
 * startIndex
 * @*arr is the pointer to the array
 * @startIndex is the first position for given array
 * @endIndex is the end position for givin array
 * */
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

/* loop through the array, each time, move an
 * smallest item to the front of the array while
 * reduce the loop range of array 
 * @*arr holds the pointer to the array
 * @size is the total number of item in the array
 * */
void sort(int *arr, int size) {
	int i;
	for(i = 0; i<size-1; i++) {
		sort_smallest(arr, i, size-1);
	}
}

/**
 * read integers and store them into an array
 * then sort the array, at last print out the
 * content of array
 * */
int main(void) {
    /**
     * size count the number of items in the array
     * arr[] is the array with max_number 30000
     * start and end is the record for time
     * i is the index for looping via the array
     * */
	int size;
    int arr[ARRAY_MAX];
	clock_t start, end;
    int i;	
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
		printf("%d\n", arr[i]);
	}
	
	fprintf(stderr, "%d %f\n", size, (end-start)/(double)CLOCKS_PER_SEC);
	
 	/*free(arr);*/
	return 0;
}
