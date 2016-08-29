#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>


/**
 method which help to mallocate memory
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 method remallocate memeory given by a pointer and the size
 */
void *remalloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return result;
}


unsigned int word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

void swap(char *key1, char *key2) {
    char *word1 = key1;
    char *word2 = key2;
    
    unsigned long len1 = strlen(key1);
    unsigned long len2 = strlen(key2);
    
    key1 = remalloc(key1, len2);
    key2 = remalloc(key2, len1);
    
    strcmp(key1, word2);
    strcmp(key2, word1);
    
    free(word1);
    free(word2);
}