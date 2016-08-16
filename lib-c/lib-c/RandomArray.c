//
//  RandomArray.c
//  lib-c
//
//  Created by zwpdbh on 8/16/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "RandomArray.h"
#include <stdio.h>
#include <stdlib.h>

int generateRandomIntIntoFile(int size) {
    printf("size of random int is %d\n", size);
    int i = 0;
    FILE *infile;
    
    infile = fopen("/Users/zw/Downloads/testIntegerData.txt", "w+");
    if (infile == NULL) {
        fprintf(stderr, "File open failed");
        exit(EXIT_FAILURE);
    }
    
    while (i < size) {
        fprintf(infile, "%d\n", rand() % size);
        i++;
    }
    
    fclose(infile);
    
    
    return 0;
}