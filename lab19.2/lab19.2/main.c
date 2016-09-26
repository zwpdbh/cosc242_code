//
//  main.c
//  lab19.2
//
//  Created by zwpdbh on 9/26/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include <stdio.h>
#include "queue.h"
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    queue q;
    q = queue_new();
    
    double key;
    
    while (1 == scanf("%lg", &key)) {
        enqueue(q, key);
    }
    
    queue_print(q);
    while (queue_size(q) != 0) {
        dequeue(q);
        queue_print(q);
    }
    
    
    return EXIT_SUCCESS;
}
