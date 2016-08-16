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
#include "RandomArray.h"

int main(void) {
    //    int item;
    //    flexarray my_flexarray = flexarray_new();
    //    while (1 == scanf("%d", &item)) {
    //        flexarray_append(my_flexarray, item);
    //    }
    //
    //    flexarray_sort(my_flexarray);
    //    flexarray_print(my_flexarray);
    //    flexarray_free(my_flexarray);
    
    if (generateRandomIntIntoFile(100000) == 0) {
        FILE *infile = fopen("/Users/zw/Downloads/testIntegerData.txt", "r");
        if (NULL == infile) {
            fprintf(stderr, "File Open failed for reading random Number");
            return EXIT_FAILURE;
        } else {
            
            int item;
            flexarray my_flexarray = flexarray_new();
            while (1 == fscanf(infile, "%d", &item)) {
                flexarray_append(my_flexarray, item);
            }
            
            flexarray_sort(my_flexarray);
            flexarray_print(my_flexarray);
            flexarray_free(my_flexarray);
            
        }
        fclose(infile);
    }
    return 0;
}