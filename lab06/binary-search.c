#include <stdio.h>
#include <stdlib.h>

#define size 10000


void insertionSort(int *arr, int count) {
	int i;
	int j;
	int key;
	for (j = 1; j < count; j++) {
		key = arr[j];
		i = j - 1;
		while (i>=0 && key < arr[i]) {
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i+1] = key;
	}
}

int search(int *arr, int indexL, int indexR, int target) {
	int mid;
	mid = (indexL + indexR) / 2;
	
	if (indexL > indexR) {
		return 0;	
	}
	if (arr[mid] == target) {
		return 1;
	} else if (target < arr[mid]) {
		return search(arr, indexL, mid-1, target);
	} else {
		return search(arr, mid + 1, indexR, target);
	}
}


int main(int argc, char **argv) {
	FILE *infile;
	int arr[size];
	int count;
	int i;
	int target;
	
	if (NULL == (infile = fopen(argv[1], "r"))) {
		fprintf(stderr, "%s: cannot find file(data) %s.\n", argv[0], argv[1]);
		return EXIT_FAILURE;
	}
	
	count = 0;
	while (count < size && 1 == fscanf(infile, "%d", &arr[count])) {
		count++;
	}
	
	fclose(infile);
	
	printf("Before sort, arr is: \n");
	for(i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	insertionSort(arr, count);
	
	printf("After sort, arr is: \n");
	for(i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	
	while (1 == scanf("%d", &target)) {
		if (search(arr, 0, count-1, target) == 1) {
			printf("+\n");
		} else {
			printf("-\n");
			continue;
		}
	}
	
	
	return 0;
}
