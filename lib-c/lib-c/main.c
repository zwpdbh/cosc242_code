//
//  main.c
//  lib-c
//
//  Created by zwpdbh on 8/16/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "FLEXARRAY.h"

int main(void) {
    int item;
    flexarray my_flexarray = flexarray_new();
    while (1 == scanf("%d", &item)) {
        flexarray_append(my_flexarray, item);
    }
    
    flexarray_sort(my_flexarray);
    flexarray_print(my_flexarray);
    flexarray_free(my_flexarray);
    
    return EXIT_SUCCESS;
}