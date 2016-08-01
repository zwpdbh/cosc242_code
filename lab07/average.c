#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define size 100
#define length 80

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Allocation Failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_arr(char **arr, int count, double len) {
    if (count > 0) {
        if(strlen(arr[0]) > len) {
            printf("%s\n", arr[0]);
        }
        print_arr(arr + 1, count - 1, len);
    }
}

int main(void) {
    int i;
    char *arr[size];
    char word[80];
    int count = 0;
    double total = 0;

    while(count < size && 1 == scanf("%s", word)) {
        arr[count] = emalloc((strlen(word) + 1) * sizeof arr[0][0]);
        total += strlen(word);
        strcpy(arr[count], word);
        count++;
    }
    if (count != 0) {
        fprintf(stderr, "%.2f\n", total / count);
        print_arr(arr, count, total / count);
    }
    


    for(i = 0; i< count; i++) {
        free(arr[i]);
    }
    return EXIT_SUCCESS;
}
