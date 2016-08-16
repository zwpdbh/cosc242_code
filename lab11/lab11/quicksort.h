//
//  quicksort.h
//  lab11
//
//  Created by zwpdbh on 8/16/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#ifndef quicksort_h
#define quicksort_h

#include <stdio.h>
extern void quicksort(int *arr, int lowIndex, int highIndex);
int partition(int *arr, int lowIndex, int hightIndex);
void swap(int *x, int *y);
#endif /* quicksort_h */
