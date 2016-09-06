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
    unsigned int step = htable_step(h, wordInteger);
    
    if (h->frequencies[wordIndex] == 0) {
        h->items[wordIndex] = remalloc(h->items[wordIndex],
                                      (strlen(str) + 1) * sizeof(h->items[0][0]));
        strcpy(h->items[wordIndex], str);
        h->frequencies[wordIndex] = 1;
        h->num_keys++;
        return 1;
    } else if (strcmp(str, h->items[wordIndex]) == 0) {
        h->frequencies[wordIndex] = h->frequencies[wordIndex] + 1;
        return h->frequencies[wordIndex];
    } else if (strcmp(str, h->items[wordIndex]) != 0){
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
            } else if (strcmp(str, h->items[wordIndex]) == 0) {
                h->frequencies[index]++;
                return h->frequencies[index];
            }
            index = (index + count * step) % h->capacity;
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
            fprintf(stream, "Index:%d -> %s, Frequencies: %d\n", i, h->items[i], h->frequencies[i]);
        }
    }
}


int htable_search(htable h, char *str) {
    int collision = 0;
    int searchIndex = htable_word_to_int(str) % h->capacity;
    int step = htable_step(h, htable_word_to_int(str));
    
    while (h->items[searchIndex] != NULL && strcmp(str, h->items[searchIndex]) != 0 && collision <= h->capacity) {
        searchIndex = (searchIndex + collision * step ) % h->capacity;
        collision++;
    }
    
    if (collision == h->capacity) {
        return 0;
    } else {
        return h->frequencies[searchIndex];
    }
}

static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}


/* These functions should be added to your htable.c file */


/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;
    
    fprintf(stream, "\n%s\n\n",
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing");
    fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
    fprintf(stream, "-----------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "-----------------------------------------------------\n\n");
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;
    
    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            }
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
        
        fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full,
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}
