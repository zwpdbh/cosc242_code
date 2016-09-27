#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue {
    double *items;
    int num_items;
    int capacity;
    int head;
};

static void *emalloc(size_t s) {
    void *result = malloc(s);
    if(result == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

queue queue_new() {
    int default_size = 7;
    int i;

    queue result = emalloc(sizeof(*result));
    result->capacity = default_size;
    result->num_items = 0;
    result->head = 0;
    result->items = emalloc(sizeof(result->items[0]) * result->capacity);
   
    for(i = 0; i<result->capacity; i++) {
        result->items[i] = 0.0;
    }
    return result;
}

void enqueue(queue q, double item) {
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q) {
    double dequeuedItem;
    int dequeueIndex;

    if(q->num_items > 0) {
        dequeueIndex = q->head;
        dequeuedItem = q->items[dequeueIndex];
        q->num_items--;
        q->head = (q->head + 1) % q->capacity;
        return dequeuedItem;
    }

    return -3.14;
}

void queue_print(queue q) {

    /* print queue contents one per line to 2 decimal places */
    int index = 0;
    int i;
    for(i = 0; i < q->num_items; i++) {
        index = (q->head + i) % q->capacity;
        printf("%.2f\n", q->items[index]);
    }
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q) {
    return q->num_items;
}

queue queue_free(queue q) {
    free(q->items);
    free(q);
    return q;
}
