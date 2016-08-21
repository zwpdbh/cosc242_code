//
//  main.c
//  lab12_HashTable
//
//  Created by zwpdbh on 8/21/16.
//  Copyright © 2016 Otago. All rights reserved.
//

//#include <stdio.h>
//#include <stdlib.h>
//#include "htable.h"
//
//int main(int argc, const char * argv[]) {
//    htable h = htable_new(11);
//    htable_insert(h, "cat");
//    htable_insert(h, "dog");
//    htable_insert(h, "horse");
//    htable_insert(h, "sparrow");
//    htable_insert(h, "giraffe");
//    htable_insert(h, "camel");
//    htable_insert(h, "goat");
//    
//    htable_print(h, stdout);
//    htable_free(h);
//    
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"

int main(void) {
    htable h = htable_new(18143);
    char word[256];
    while (getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }
    htable_print(h, stdout);
    htable_free(h);
    return EXIT_SUCCESS;
}