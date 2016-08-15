//
//  FLEXARRAY.h
//  sort-arry
//
//  Created by zwpdbh on 8/15/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#ifndef FLEXARRAY_h
#define FLEXARRAY_h

#include <stdio.h>

typedef struct flexarrayrec *flexarray;

extern  void    flexarray_append(flexarray f, int item);
extern  void    flexarray_free(flexarray f);
extern  flexarray   flexarray_new();
extern  void    flexarray_print(flexarray f);
extern  void    flexarray_sort(flexarray f);

#endif /* FLEXARRAY_h */
