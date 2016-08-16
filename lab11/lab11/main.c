//
//  main.c
//  lab11
//
//  Created by zwpdbh on 8/16/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include <stdio.h>
#include "quicksort.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    int arr[5];
    int i;
    for (i = 5; i >= 1; i--) {
        arr[5-i] = i;
    }
    
    for (i = 0; i < 5; i++) {
        printf("%d\n", arr[i]);
    }
    
    quicksort(arr, 0, 4);
    
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
