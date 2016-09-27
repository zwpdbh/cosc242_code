#ifndef mylib_h_
#define mylib_h_

#include <stdio.h>
extern void *emalloc(size_t);
extern void *remalloc(void *, size_t);
extern int getword(char *s, int limit, FILE *stream);
#endif
