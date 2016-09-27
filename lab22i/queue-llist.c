#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct q_item *q_item;

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
    if(result == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

queue queue_new() {
    queue q = emalloc(sizeof(*q));
    q->first = NULL;
    q->last = q->first;
    q->length = 0;

    return q;
}

void enqueue(queue q, double item) {
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q) {
    double dequeuedItem;
    q_item tmp;

    if(q->length > 0) {
        dequeuedItem = q->first->item;
        tmp = q->first;
        q->first = q->first->next;
        free(tmp);
        q->length--;
        return dequeuedItem;
    }

    return -3.14;
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
    q_item each = q->first;
    while(each != NULL) {
        printf("%.2f\n", each->item);
        each = each->next;
    }
}

void queue_print_info(queue q) {
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q) {
    return q->length;
}


queue queue_free(queue q) {
    q_item each;
    while(q->first != NULL) {
        each = q->first;
        q->first = q->first->next;
        free(each);
    }
    free(q);
    return q;
}

