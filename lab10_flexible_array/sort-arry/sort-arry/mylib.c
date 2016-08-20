//
//  mylib.c
//  sort-arry
//
//  Created by zwpdbh on 8/15/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *remalloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return result;
}
