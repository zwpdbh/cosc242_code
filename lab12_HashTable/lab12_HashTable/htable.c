//
//  htable.c
//  lab12_HashTable
//
//  Created by zwpdbh on 8/21/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "htable.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>

struct htablerec {
    int capacity;
    int num_keys;
    char **items;
    int *frequencies;
};


htable htable_new(int capacity) {
    htable table = emalloc(sizeof(*table));
    table->capacity = capacity;
    table->num_keys = 0;
    table->frequencies = emalloc(table->capacity * sizeof(table->frequencies[0]));
    table->items = emalloc(table->capacity * sizeof(table->items[0]));
    
    int i;
    for (i = 0; i < table->capacity; i++) {
        table->items[i] = emalloc(sizeof(table->items[0][0]));
    }
    
    return table;
}

void htable_free(htable h) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        free(h->items[i]);
    }
    free(h->frequencies);
    free(h->items);
    free(h);
}

int htable_insert(htable h, char *str) {
    
    return 0;
}

void htable_print(htable h, FILE *stream) {
    
}

int htable_search(htable h, char *str) {
    return 0;
}