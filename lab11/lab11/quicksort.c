//
//  quicksort.c
//  lab11
//
//  Created by zwpdbh on 8/16/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "quicksort.h"

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(int *arr, int l, int h) {
    int x = arr[h];
    int i = l - 1;
    
    int j;
    for (j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(arr + i, arr + j);
        }
    }
    swap(arr + i + 1, arr + h);
    
    return i + 1;
}

void quicksort(int *arr, int l, int h) {
    int p;
    
    if ((h - l) > 0) {
        p = partition(arr, l, h);
        quicksort(arr, l, p - 1);
        quicksort(arr, p + 1, h);
    }
}

