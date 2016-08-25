#include "htable.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 20


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
        table->frequencies[i] = 0;
    }
    
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
    unsigned int wordInteger = htable_word_to_int(str);
    printf("%s->%d->%d\n", str, wordInteger, wordInteger % h->capacity);
    unsigned int wordIndex = wordInteger % h->capacity;
    
    if (h->frequencies[wordIndex] == 0) {
        h->items[wordIndex] = remalloc(h->items[wordIndex],
                                      (strlen(str) + 1) * sizeof(h->items[0][0]));
        strcpy(h->items[wordIndex], str);
        h->frequencies[wordIndex] = 1;
        h->num_keys++;
        return 1;
    } else if (htable_word_to_int(h->items[wordIndex]) == wordInteger) {
        h->frequencies[wordIndex] = h->frequencies[wordIndex] + 1;
        return h->frequencies[wordIndex];
    } else if (htable_word_to_int(h->items[wordIndex]) != wordInteger){
        int count = 0;
        unsigned int index = wordIndex;
        while (count != h->capacity) {
            if (h->frequencies[index] == 0) {
                h->items[index] = remalloc(h->items[index],
                                               (strlen(str) + 1) * sizeof(h->items[0][0]));
                strcpy(h->items[index], str);
                h->frequencies[index] = 1;
                h->num_keys++;
                return 1;
            } else if (htable_word_to_int(h->items[wordIndex]) == wordInteger) {
                h->frequencies[index]++;
                return h->frequencies[index];
            }
            index = (index + 1) % h->capacity;
            count++;
        }
        return 0;
    }
    return 0;
}

void htable_print(htable h, FILE *stream) {
    int i;
    for (i = 0 ; i < h->capacity; i++) {
        if (h->frequencies[i] != 0) {
            printf("Index:%d -> %s, Frequencies: %d\n", i, h->items[i], h->frequencies[i]);
        }
    }
}

int htable_search(htable h, char *str) {
    int collision = 0;
    unsigned int wordInt = htable_word_to_int(str);
    int searchIndex = wordInt % h->capacity;
    
    while (htable_word_to_int(h->items[searchIndex]) != wordInt && collision != h->capacity) {
        searchIndex++;
        collision++;
    }
    
    if (collision == h->capacity) {
        return 0;
    }
    
    return h->frequencies[searchIndex];
}