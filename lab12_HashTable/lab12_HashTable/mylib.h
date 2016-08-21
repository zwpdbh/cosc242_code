//
//  mylib.h
//  sort-arry
//
//  Created by zwpdbh on 8/15/16.
//  Copyright © 2016 Otago. All rights reserved.
//


#ifndef mylib_h
#define mylib_h

#include <stddef.h>
#include <stdio.h>

extern void *emalloc(size_t);
extern void *remalloc(void *, size_t);
extern unsigned int htable_word_to_int(char *word);
extern int getword(char *s, int limit, FILE *stream);
#endif /* mylib_h */


