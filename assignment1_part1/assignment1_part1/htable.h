#ifndef htable_h
#define htable_h

#include <stdio.h>

typedef struct htablerec *htable;

extern  void    htable_free(htable h);
extern  int     htable_insert(htable h, char *str);
extern  htable  htable_new(int capacity);
extern  void    htable_print(htable h, FILE *stream);
extern  int     htable_search(htable h, char *str);
static unsigned int htable_step(htable h, unsigned int i_key);

extern void     htable_print_stats(htable h, FILE *stream, int num_stats);
static void     print_stats_line(htable h, FILE *stream, int percent_full);

#endif /* htable_h */
