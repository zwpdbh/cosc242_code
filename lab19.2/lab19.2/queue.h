//
//  queue.h
//  lab19.2
//
//  Created by zwpdbh on 9/26/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>


typedef struct q_item *q_item;
typedef struct queue *queue;

extern queue queue_new();
extern void enqueue(queue q, double item);
extern double dequeue(queue q);
extern void queue_print(queue q);
extern int queue_size(queue q);
extern queue queue_free(queue q);


#endif /* queue_h */
