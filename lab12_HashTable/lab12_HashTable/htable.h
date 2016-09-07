#ifndef htable_h
#define htable_h

#include <stdio.h>

typedef struct htablerec *htable;

extern  void    htable_free(htable h);
extern  int     htable_insert(htable h, char *str);
extern  htable  htable_new(int capacity);
extern  int     htable_search(htable h, char *str);
extern void     htable_print(htable h, void f(int freq, char *str));

#endif /* htable_h */
