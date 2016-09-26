//
//  queue.c
//  lab19.1
//
//  Created by zwpdbh on 9/26/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};

static void *emalloc(size_t s) {
    void *result = malloc(s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


queue queue_new() {
    queue result = emalloc(sizeof(*result));
    result->head = 0;
    result->capacity = 5;
    result->num_items = 0;
    result->items = emalloc(sizeof(result->items[0]) * result->capacity);
    
    return result;
}

void enqueue(queue q, double item) {
    int index;
    
    if (q->num_items < q->capacity) {
        index = (q->head + q->num_items) % q->capacity;
        printf("enqueue: %lg at index %d\n", item, index);
        q->items[index] = item;
        q->num_items += 1;
    }
}

double dequeue(queue q) {
    double dequeueValue;
    int dequeueIndex;
    if (q->num_items > 0) {
        dequeueIndex = q->head;
        dequeueValue = q->items[q->head];
        q->num_items -= 1;
        q->head = (q->head + 1) % q->capacity;
        printf("dequeue item: %lg at index %d, set head at: %d\n", dequeueValue, dequeueIndex, q->head);
        return dequeueValue;
    }
    return -0.314;
}

void queue_print(queue q) {
    printf("the content of q is: \n");
    int i;
    int index;
    for (i = 0; i < q->num_items; i++) {
        index = (q->head + i) % q->capacity;
        printf("%lg ", q->items[index]);
    }
    printf("\n");
}

int queue_size(queue q) {
    return q->num_items;
}

queue queue_free(queue q) {
    free(q->items);
    free(q);
    return q;
}
