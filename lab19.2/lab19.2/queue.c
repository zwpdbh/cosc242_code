//
//  queue.c
//  lab19.2
//
//  Created by zwpdbh on 9/26/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};

static void *emalloc(size_t s) {
    void *result = malloc(s);
    if (result == NULL) {
        fprintf(stderr, "memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

queue queue_new() {
    queue q = emalloc(sizeof(*q));
    q->first = NULL;
    q->last = NULL;
    q->length = 0;
    
    return q;
}

void enqueue(queue q, double item) {
    if (q->length == 0) {
        q->first = emalloc(sizeof(struct q_item));
        q->first->item = item;
        q->first->next = NULL;
        q->last = q->first;
    } else {
        q->last->next = emalloc(sizeof(struct q_item));
        q->last = q->last->next;
        q->last->item = item;
        q->last->next = NULL;
    }

    q->length += 1;
}


double dequeue(queue q) {
    double dequeuedItem;
    q_item tmp;
    
    if (q->length >0) {
        dequeuedItem = q->first->item;
        tmp = q->first;
        q->first = q->first->next;
        free(tmp);
        q->length -= 1;
        return dequeuedItem;
    }
    return -3.14;
}

void queue_print(queue q) {
    q_item each = q->first;
    while (each != NULL) {
        printf("%lg ", each->item);
        each = each->next;
    }
    printf("\n");
}

int queue_size(queue q) {
    return q->length;
}

queue queue_free(queue q) {
    q_item each;
    while (q->first != NULL) {
        each = q->first;
        q->first = q->first->next;
        free(each);
    }
    free(q);
    return q;
}
