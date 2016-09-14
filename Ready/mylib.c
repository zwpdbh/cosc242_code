#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/**
 * a helper function which return the pointer to the allocated memory.
 * @param s is the size of memory will be allocated.
 * @return result is the void pointer to the allocated memory.
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
 * a helper function which return the pointer to the allocated memeory.
 * @param p is the resized pointer to the already allocated memory.
 * @param s is the size of memeory will be re-allocated.
 * @return the void pointer to the allocated memory.
 */
void *remalloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * a helper function get the single word from a specifyed input.
 * @param s is the varible hold the a single word.
 * @param limit is the limit of the size of the word s can hold.
 * @param stream is the stream of the input.
 * @return if the return value is EOF, means it reach the end of input.
 */
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break; }
    }
    *w = '\0';
    return w - s;
}

/**
 * a function which convert a string into int.
 * @param word is the word will be converted.
 * @result which is a unsigned int converted from string word.
 */
unsigned int word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}


/**
 * test whether the specified number x is prime or not.
 * If n can only be devided by 1, return 1, otherwise return 0.
 * @param x the number tested
 * @return if it is prime number, return 1 otherwise return 0.
 */
static int factor(int x) {
    int f = 2;
    while (f <= sqrt(x)) {
        if (x % f == 0) {
            return 0;
        } else {
            f = f + 1;
        }
    }
    return 1;
}

/**
 * return the prime number greater or equal to the int specified.
 * @param n the number specified.
 * @return bound a prime number.
 */
int primegt(int n) {
    int bound = n;
    if (n == 1) {
        return 2;
    }
    while (bound > 0) {
        if (factor(bound)) {
            break;
        } else {
            bound = bound + 1;
        }
    }
    return bound;
}
  
