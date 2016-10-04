#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static void *emalloc(size_t s) {
    void *result = malloc(s);
    if(result == NULL) {
        fprintf(stderr, "error\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

struct queue {
    int head;
    int num_items;
    int capacity;
    int *items;
};

queue queue_new() {
    int default_size = 7;
    int i = 0;

    queue q = emalloc(sizeof(*q));
    q->capacity = default_size;
    q->num_items = 0;
    q->items = emalloc(sizeof(q->items[0]) * q->capacity);
    q->head = 0;

    for(i = 0; i<q->capacity; i++) {
        q->items[i] = 0;
    }

    return q;
}

void enqueue(queue q, int item) {
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q) {
    int value;
    if(q->num_items > 0) {
        value = q->items[q->head];
        q->head = (q->head + 1) % q->capacity;
        q->num_items -= 1;
        return value;
    }
    return -1;
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
    int i = 0;
    int index = q->head;
    for(i = 0; i < q->num_items; i++) {
        printf("%d\n", q->items[index]);
        index = (index + 1) % q->capacity;
    }
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%d", i == 0 ? "" : ", ", q->items[i]);
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
