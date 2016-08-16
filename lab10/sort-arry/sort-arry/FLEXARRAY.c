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
#include "quicksort.h"
#include <time.h>

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
        printf("%d\n", f->items[i]);
    }
    printf("\n");
}

void flexarray_sort(flexarray f) {
    clock_t start, end;
    start = clock();
//    quicksort(f->items, 0, f->itemcount - 1);
    merge_sor(f->items, 0, f->itemcount - 1);
    end = clock();
    fprintf(stderr, "%d %f\n", f->itemcount, (end - start) / (double)CLOCKS_PER_SEC);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}