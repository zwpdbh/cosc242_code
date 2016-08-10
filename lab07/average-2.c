#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define array_size 100
#define word_len 80

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(result == NULL) {
        fprintf(stderr, "Mallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


void printArr(char **arr, double average_len, int count) {
    if(count > 0) {
        if(strlen(arr[0]) > average_len) {
            printf("%s\n", arr[0]);
        }
        printArr(arr + 1, average_len, count - 1);
    }
}

int main(void) {
    int i = 0;
    int count = 0;
    double total = 0.0;
    char *arr[array_size];
    char word[word_len];

    while(count < array_size && 1 == scanf("%s", word)) {
        arr[count] = emalloc((strlen(word) + 1) * sizeof arr[0][0]);
        strcpy(arr[count], word);
        total += strlen(word);
        count++;
    }

    if(count != 0) {
        fprintf(stderr, "%.2f\n", total / count);
        printArr(arr, total / count, count);
    }

    for(i = 0; i < count; i++) {
        free(arr[i]);
    }

    return  EXIT_SUCCESS;
}
