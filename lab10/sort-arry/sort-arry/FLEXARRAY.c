//
//  FLEXARRAY.c
//  sort-arry
//
//  Created by zwpdbh on 8/15/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "FLEXARRAY.h"
#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "merge_sort.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof(*result));
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof(result->items[0]));
    return result;
}

void flexarray_append(flexarray f, int num) {
    f->itemcount++;
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        // remalloc on 'f->items'
        f->items = remalloc(f->items, f->capacity * sizeof(f->items[0]));
    }
    f->items[f->itemcount - 1] = num;
}

void flexarray_print(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%d ", f->items[i]);
    }
    printf("\n");
}

void flexarray_sort(flexarray f) {
    merge_sor(f->items, 0, f->itemcount - 1);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}