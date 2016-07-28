#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_MAX 30000

/* sort an array which takest
 * @*arr holds the pointer to the array
 * @size holds the size of the array
 * */
void sort(int *arr, int size) {
    /* use j to loop every elements
     * in each loop, use i to do while loop
     * key is the current item being selecting and comparing
     * */
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
