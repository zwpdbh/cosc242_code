#include <stdio.h>
#include <stdlib.h>

void display_repeat(int *arr, int size) {
	int i;
	int *record;
	
	record = malloc(size * sizeof(record[0]));
	
	for (i = 0; i<size;i++) {
		record[i] = 0;
	}
	
	for (i=0;i<size;i++) {
		record[arr[i]] += 1;
	}

	
	for(i = 0; i<size; i++) {
		if (record[i] > 1) {
			printf("%d repeat %d\n", i, record[i]);
		}
	}
	
	free(record);
}

int main(int argc, char *argv[]) {
	int array_size = 0;
	int *dyArr;
	int i = 0;
	
	printf("Enter the size of array: \n");
	scanf("%d", &array_size);
	
	dyArr = malloc(array_size * sizeof(dyArr[0]));
	
	if (NULL == dyArr) {
		fprintf(stderr, "memeory allocation failed\n");
		return 1;
	}

	for (i = 0;i < array_size; i++) {
		dyArr[i] = rand() % array_size;
	}
	
	printf("What is in the array ? \n");
	for (i = 0; i < array_size; i++) {
		printf("%d ", dyArr[i]);
	}
	printf("\n");
	
	display_repeat(dyArr, array_size);
	
	/*Release the memory!*/
	free(dyArr);
	
	return 0;
}