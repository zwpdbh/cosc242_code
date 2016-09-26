#include <stdio.h>
#include <stdlib.h>

void checkArray(int *target, int size) {
    int *arr = malloc(sizeof(arr[0]) * size);
    int i;
    
    
    for (i = 0; i < size; i++) {
        arr[i] = 0;
    }
    
    for (i = 0; i < size; i++) {
        arr[target[i]] += 1;
    }
    
    for (i = 0 ; i < size; i++) {
        if (arr[i] >= 1) {
            printf("%d occurs %d times\n", i, arr[i]);
        }
    }

    free(arr);
}

int main(void) {
    int array_size = 0;
    int *my_array;
    int i;
    
    printf("Enter the size of the array");
    scanf("%d", &array_size);
    
    my_array = malloc(array_size * sizeof(my_array[0]));
    if (NULL == my_array) {
        fprintf(stderr, "memeory allocation failed!\n");
    }
    
    for (i = 0; i < array_size; i++) {
        my_array[i] = rand() % array_size;
    }
    
    printf("What's in the array:\n");
    for (i = 0; i < array_size; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");
    
    checkArray(my_array, array_size);
    
    free(my_array);
    return EXIT_SUCCESS;
}