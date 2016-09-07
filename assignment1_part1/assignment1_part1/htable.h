#ifndef htable_h
#define htable_h

#include <stdio.h>

typedef struct htablerec *htable;
typedef enum hashing_e { LINEAR_P, DOUBLE_H } hashing_t;

extern  void    htable_free(htable h);
extern  int     htable_insert(htable h, char *str);
extern  htable  htable_new(int capacity, hashing_t method);
/**
extern  void    htable_print(htable h, FILE *stream);
 */
extern void     htable_print(htable h, void f(int freq, char *str));
extern  int     htable_search(htable h, char *str);
/**
static unsigned int htable_step(htable h, unsigned int i_key);
 */
extern void     htable_print_entire_table(htable h);
extern void     htable_print_stats(htable h, FILE *stream, int num_stats);
extern void     htable_content(htable h, FILE *stream);
/**
static void     print_stats_line(htable h, FILE *stream, int percent_full);
 */

#endif /* htable_h */
