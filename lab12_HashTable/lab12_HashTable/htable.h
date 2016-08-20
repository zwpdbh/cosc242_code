//
//  htable.h
//  lab12_HashTable
//
//  Created by zwpdbh on 8/21/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#ifndef htable_h
#define htable_h

#include <stdio.h>

typedef struct htablerec *htable;

extern  void    htable_free(htable h);
extern  int     htable_insert(htable h, char *str);
extern  htable  htable_new(int capacity);
extern  void    htable_print(htable h, FILE *stream);
extern  int     htable_search(htable h, char *str);

#endif /* htable_h */
