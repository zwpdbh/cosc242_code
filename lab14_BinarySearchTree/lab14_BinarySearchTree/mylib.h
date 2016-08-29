#ifndef mylib_h
#define mylib_h

#include <stddef.h>
#include <stdio.h>

extern void *emalloc(size_t);
extern void *remalloc(void *, size_t);
extern unsigned int word_to_int(char *word);
extern void swap(char *key1, char *key2);
#endif /* mylib_h */


