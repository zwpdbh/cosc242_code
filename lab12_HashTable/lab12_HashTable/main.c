//
//  main.c
//  lab12_HashTable
//
//  Created by zwpdbh on 8/21/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

int main(int argc, const char * argv[]) {
    htable h = htable_new(11);
    htable_free(h);
    
    return 0;
}
