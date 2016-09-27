#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}


htable htable_new(int capacity) {
    int i;
    htable h = emalloc(capacity * sizeof(*h));
    h->capacity = capacity;
    h->num_keys = 0;
    h->keys = emalloc(h->capacity * sizeof(h->keys[0]));
    
    for(i = 0; i < h->capacity; i++) {
        h->keys[i] = NULL;
    }
    return h;
}

void htable_free(htable h) {
    int i = 0;
    for(i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }
    free(h->keys);
    free(h);
}

int htable_insert(htable h, char *key) {
    unsigned int wordInt = htable_word_to_int(key);
    unsigned int wordIndex = wordInt % h->capacity;
    int collisionCount = 0;

    while(collisionCount <= h->capacity && h->num_keys <= h->capacity) {
        if(h->keys[wordIndex] == NULL) {
            h->keys[wordIndex] = emalloc((strlen(key) + 1) * sizeof(h->keys[0][0]));
            strcpy(h->keys[wordIndex], key);
            h->num_keys += 1;
            return 1;
        } else if (strcmp(key, h->keys[wordIndex]) == 0) {
            return 1;
        } else {
            wordIndex = (wordIndex + 1) % h->capacity;
            collisionCount += 1;
        }
    }
    return 0;
}

void htable_print(htable h, FILE *stream) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
