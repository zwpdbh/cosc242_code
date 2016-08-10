#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

void print_arr(int *arr, int count) {
	int i = 0;
	for (i = 0;i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void merge(int *arr, int l, int m, int r) {

	int left_size = m - l + 1;
	int right_size = r - m;
	int size = r - l + 1;

	/*
	printf("L: %d--%d,  ", l, m);
	print_arr(arr, left_size);
	printf("R: %d--%d,  ", m + 1, r);
	print_arr(arr + left_size, right_size);
	printf("\n");
	*/
	
	int leftArr[left_size];
	int rightArr[right_size];
	int workplace[size];
	
	int i; 
	int j;
	int index;
	
	for (i = 0; i < left_size; i++) {
		leftArr[i] = arr[i];
	}
	
	for (j = 0; j < right_size; j++) {
		rightArr[j] = arr[j + left_size];
	}
	
	i = 0;
	j = 0;
	index = 0;

	
	while (index < size) {
		if (i < left_size && j < right_size) {
			if (leftArr[i] < rightArr[j]) {
				workplace[index] = leftArr[i];
				i++;
			} else {
				workplace[index] = rightArr[j];
				j++;
			}
		} else if (i == left_size  && j < right_size) {
			workplace[index] = rightArr[j];
			j++;
		} else {
			workplace[index] = leftArr[i];
			i++;
		}
		index++;
	}
	
	index = 0;
	for (index = 0; index < size; index++) {
		arr[index] = workplace[index];
	}
}

void insertion_sort(int *arr, int n) {
	int i;
	for (i = 1; i < n; i++) {
		int j = i - 1;
		int key = arr[i];
		while (j >= 0 && key < arr[j]) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j + 1] = key; 
	}
}

void merge_sor(int *arr, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge_sor(arr, l, m);
		/*trickier, arr + (m - l + 1)*/
		merge_sor(arr + (m - l + 1), m + 1, r);
		merge(arr, l, m, r);	
	}
	
}

int main(void) {
	int arr[SIZE];
	clock_t start, end;
	
	int count = 0;
	while (count < SIZE && 1 == scanf("%d", &arr[count])) {
		count++;
	}
	
	start = clock();
	/*Be careful, it is count - 1*/
	merge_sor(arr, 0, count-1);
	end = clock();

	fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
}