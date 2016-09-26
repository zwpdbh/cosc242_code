//
//  main.c
//  lab19.1
//
//  Created by zwpdbh on 9/26/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
    
    queue q;
    q = queue_new();
    
    int i;
    int count = 0;
    
    printf("qeueue has size 5.\n");
    for (count = 0; count <5 ; count++) {
        enqueue(q, count + 0.1);
    }
    
    
    queue_print(q);
    dequeue(q);
    dequeue(q);
    
    queue_print(q);
    
    enqueue(q, 0.8);
    enqueue(q, 0.9);
    enqueue(q, 0.11);
    
    queue_print(q);
    for (i = 1; i <= 5; i++) {
        dequeue(q);
    }
    queue_print(q);
    for (count = 0; count <5 ; count++) {
        enqueue(q, count + 0.1);
    }
    queue_print(q);
    queue_free(q);
    
    return EXIT_SUCCESS;
}
