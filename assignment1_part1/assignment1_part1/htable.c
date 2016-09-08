#include "htable.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
    int *freqs;
    int *stats;
    hashing_t method;
};

unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

htable htable_new(int capacity, hashing_t method) {
    int i;
    
    htable table = emalloc(sizeof(*table));
    table->capacity = capacity;
    table->num_keys = 0;
    table->freqs = emalloc(table->capacity * sizeof(table->freqs[0]));
    table->keys = emalloc(table->capacity * sizeof(table->keys[0]));
    table->stats = emalloc(table->capacity * sizeof(table->stats[0]));
    table->method = method;
    
    for (i = 0; i < table->capacity; i++) {
        table->freqs[i] = 0;
        table->keys[i] = NULL;
        table->stats[i] = 0;
    }
    
    return table;
}


void htable_free(htable h) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }
    free(h->freqs);
    free(h->keys);
    free(h->stats);
    free(h);
}


static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

/**
 return 0 means insert failed
 return 1 means insert succeed at the fisrt time
 return >1 means the frequencies the word has been inserted
 */
int htable_insert(htable h, char *str) {
    unsigned int wordInteger = htable_word_to_int(str);
    unsigned int wordIndex = wordInteger % h->capacity;
    unsigned int step = htable_step(h, wordInteger);
    int collision = 0;
    unsigned int index;
    printf("insert word: %s, \twordInteger: %u, \tput into index: %u", str, wordInteger, wordIndex);
    if (h->keys[wordIndex] == NULL) {
        h->keys[wordIndex] = emalloc((strlen(str) + 1) * sizeof(h->keys[0][0]));
        strcpy(h->keys[wordIndex], str);
        h->freqs[wordIndex] += 1;
        h->num_keys += 1;
        h->stats[h->num_keys-1] = 0;
        
        printf("\nindex %u is empty, \tplace '%s' at index: %u, \tcollision is %d\n", wordIndex, str, wordIndex ,h->stats[h->num_keys-1]);
        
        return 1;
    } else if (strcmp(str, h->keys[wordIndex]) == 0) {
        h->freqs[wordIndex] += 1;
        printf("\nindex %u is not empty, word '%s' is at %u, \tplace '%s' at index: %u, \tcollision is %d\n", wordIndex, h->keys[wordIndex], wordIndex, str, wordIndex, h->stats[h->num_keys]);
        return h->freqs[wordIndex];
    } else {
        
        printf("\nput word '%s' at index %u, but word '%s' is at index %u\n", str, wordIndex, h->keys[wordIndex], wordIndex);
        
        
        index = wordIndex;
        while (collision < h->capacity && h->keys[index] != NULL &&
               strcmp(str, h->keys[index]) != 0) {
            
            printf("index %u is occupied with '%s', ", index, h->keys[index]);
            
            if (h->method == LINEAR_P) {
                index += 1;
            } else {
                index += step;
            }
            index = index % h->capacity;
            printf("move to the next index %u\n", index);
            collision++;
        }
        
        if (h->keys[index] == NULL) {
            
            h->keys[index] = emalloc((strlen(str) + 1) * sizeof(h->keys[0][0]));
            strcpy(h->keys[index], str);
            h->freqs[index] += 1;
            h->num_keys += 1;
            h->stats[h->num_keys-1] = collision;
            printf("index %u is %s, so put word '%s' at index %u, with collision: %d\n", index, h->keys[index], str, index, collision);
            printf("table stats %d: max collision is %d", h->num_keys, h->stats[h->num_keys-1]);
            
            return 1;
        } else if (strcmp(str, h->keys[index]) == 0) {
            
            printf("index %u is %s, so put word '%s' at index %u, with collision: %d\n", index, h->keys[index], str, index, collision);
            
            h->freqs[index] += 1;
            return h->freqs[index];
        } else {
            printf("collision time is: %d, table is full\n", collision);
            return 0;
        }
    }
}


void htable_print(htable h, void f(int freq, char *word)) {
    int i;
    for (i = 0 ; i < h->capacity; i++) {
        if (h->freqs[i] != 0) {
            f(h->freqs[i], h->keys[i]);
        }
    }
}

void htable_content(htable h, FILE *stream) {
    int i;
    printf("  Pos  Freq  Stats  Word\n");
    printf("----------------------------------------\n");
    for (i = 0; i < h->capacity; i++) {
        if (h->freqs[i] != 0) {
            fprintf(stream, "%5d %5d %5d   %s\n",
                    i, h->freqs[i], h->stats[i], h->keys[i]);
        } else {
            fprintf(stream, "%5d %5d %5d   %s\n",
                    i, h->freqs[i], h->stats[i], "");
        }
    }
}

int htable_search(htable h, char *str) {
    int collision = 0;
    int searchIndex = htable_word_to_int(str) % h->capacity;
    int step = htable_step(h, htable_word_to_int(str));
    
    while (h->keys[searchIndex] != NULL && strcmp(str, h->keys[searchIndex]) != 0 && collision <= h->capacity) {
        if (h->method == DOUBLE_H) {
            searchIndex = (searchIndex + step ) % h->capacity;
        } else {
            searchIndex = (searchIndex + 1 ) % h->capacity;
        }
        
        collision++;
    }
    
    if (collision == h->capacity) {
        return 0;
    } else {
        return h->freqs[searchIndex];
    }
}


/* These functions should be added to your htable.c file */
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

