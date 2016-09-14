#ifndef mylib_h
#define mylib_h

#include <stddef.h>
#include <stdio.h>

extern void *emalloc(size_t);
extern void *remalloc(void *, size_t);
extern int getword(char *s, int limit, FILE *stream);
extern int primegt(int n);
extern unsigned int word_to_int(char *word);
#endif /* mylib_h */
