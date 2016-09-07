#include "htable.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct htablerec {
    int capacity;
    int num_keys;
    char **items;
    int *frequencies;
};


htable htable_new(int capacity) {
    int i;
    
    htable table = emalloc(sizeof(*table));
    table->capacity = capacity;
    table->num_keys = 0;
    table->frequencies = emalloc(table->capacity * sizeof(table->frequencies[0]));
    table->items = emalloc(table->capacity * sizeof(table->items[0]));
    
    for (i = 0; i < table->capacity; i++) {
        table->frequencies[i] = 0;
        table->items[i] = NULL;
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

    unsigned int wordIndex = wordInteger % h->capacity;
    
    if (h->items[wordIndex] == NULL) {
        h->items[wordIndex] = emalloc((strlen(str) + 1) * sizeof(h->items[0][0]));
        strcpy(h->items[wordIndex], str);
        h->frequencies[wordIndex] += 1;
        h->num_keys += 1;
        return 1;
    } else if (strcmp(str, h->items[wordIndex]) == 0) {
        h->frequencies[wordIndex] += 1;
        return h->frequencies[wordIndex];
    } else {
        int collision = 1;
        unsigned int index = wordIndex;
        while (collision <= h->capacity && h->items[index] != NULL &&
               strcmp(str, h->items[index]) != 0) {
            index += 1;
            index = index % h->capacity;
            index = (index + 1) % h->capacity;
            collision++;
        }
        if (h->items[index] == NULL) {
            h->items[index] = emalloc((strlen(str) + 1) * sizeof(h->items[0][0]));
            strcpy(h->items[index], str);
            h->frequencies[index] += 1;
            h->num_keys += 1;
            if (h->frequencies[index] != 1) {
                fprintf(stderr, "error");
            }
            return 1;
        } else if (strcmp(str, h->items[index]) == 0) {
            h->frequencies[index] += 1;
            return h->frequencies[index];
        } else {
            return 0;
        }
    }
    
//    if (h->frequencies[wordIndex] == 0) {
//        h->items[wordIndex] = remalloc(h->items[wordIndex],
//                                      (strlen(str) + 1) * sizeof(h->items[0][0]));
//        strcpy(h->items[wordIndex], str);
//        h->frequencies[wordIndex] = 1;
//        h->num_keys++;
//        return 1;
//    } else if (strcmp(str, h->items[wordIndex]) == 0) {
//        if (strcmp(str, "to") == 0) {
//            printf("the index for 'to' is at: %d", wordIndex);
//        }
//        h->frequencies[wordIndex] = h->frequencies[wordIndex] + 1;
//        return h->frequencies[wordIndex];
//    } else if (strcmp(str, h->items[wordIndex]) != 0){
//        int count = 0;
//        unsigned int index = wordIndex;
//        while (count != h->capacity) {
//            if (h->frequencies[index] == 0) {
//                h->items[index] = remalloc(h->items[index],
//                                               (strlen(str) + 1) * sizeof(h->items[0][0]));
//                strcpy(h->items[index], str);
//                h->frequencies[index] = 1;
//                h->num_keys++;
//                return 1;
//            } else if (strcmp(str, h->items[wordIndex]) == 0) {
//                h->frequencies[index]++;
//                return h->frequencies[index];
//            }
//            index = (index + 1) % h->capacity;
//            count++;
//        }
//        return 0;
//    }
    return 0;
}


void htable_print(htable h, void f(int freq, char *word)) {
    int i;
    for (i = 0 ; i < h->capacity; i++) {
        if (h->frequencies[i] != 0) {
//            printf("index at: %d ", i);
            f(h->frequencies[i], h->items[i]);
        }
    }
}


int htable_search(htable h, char *str) {
    int collision = 0;
    int searchIndex = htable_word_to_int(str) % h->capacity;
    
    while (h->items[searchIndex] != NULL && strcmp(str, h->items[searchIndex]) != 0 && collision <= h->capacity) {
        searchIndex = (searchIndex + 1 ) % h->capacity;
        collision++;
    }
    
    if (collision == h->capacity) {
        return 0;
    } else {
        return h->frequencies[searchIndex];
    }
}