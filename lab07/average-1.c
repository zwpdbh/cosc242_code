#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define array_size 100
#define word_len 80

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "malloc memory failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_arr(char **arr, double average, unsigned int count) {
    if(count > 0) {
        if(strlen(arr[0]) > average) {
            printf("%s\n", arr[0]);
        }
        print_arr(arr + 1, average, count-1);
    }
}

int main(void) {
    int i = 0;
    int count;
    double total = 0.0;
    char *wordArr[array_size];
    char word[word_len];
    
    count = 0;
    while(count < array_size && 1 == scanf("%s", word)) {
        wordArr[count] = emalloc((strlen(word) + 1) * sizeof wordArr);
        strcpy(wordArr[count], word);
        total += strlen(word);
        count++;
    }
    
    if(count != 0) {
        fprintf(stderr, "%.2f\n", total / count);
        print_arr(wordArr, total / count, count);
    }
    
    for(i = 0; i < count; i++) {
        free(wordArr[i]);
    }

    return 0;
}
