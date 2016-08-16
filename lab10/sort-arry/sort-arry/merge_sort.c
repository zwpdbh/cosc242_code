//
//  merge_sort.c
//  sort-arry
//
//  Created by zwpdbh on 8/15/16.
//  Copyright © 2016 Otago. All rights reserved.
//

#include "merge_sort.h"
#include <stdlib.h>
#include <stdio.h>

void merge(int *arr, int l, int m, int r) {
    int left_size = m - l + 1;
    int right_size = r - m;
    int size = r - l + 1;
    
    
    int leftArr[left_size];
    int rightArr[right_size];
    int workplace[size];
    
    int i;
    int j;
    int index;
    
    for (i = 0; i < left_size; i++) {
        leftArr[i] = arr[i];
    }
    
    for (j = 0; j < right_size; j++) {
        rightArr[j] = arr[j + left_size];
    }
    
    i = 0;
    j = 0;
    index = 0;
    
    
    while (index < size) {
        if (i < left_size && j < right_size) {
            if (leftArr[i] < rightArr[j]) {
                workplace[index] = leftArr[i];
                i++;
            } else {
                workplace[index] = rightArr[j];
                j++;
            }
        } else if (i == left_size  && j < right_size) {
            workplace[index] = rightArr[j];
            j++;
        } else {
            workplace[index] = leftArr[i];
            i++;
        }
        index++;
    }
    
    index = 0;
    for (index = 0; index < size; index++) {
        arr[index] = workplace[index];
    }
}


void insertion_sort(int *arr, int n) {
    int i;
    for (i = 1; i < n; i++) {
        int j = i - 1;
        int key = arr[i];
        while (j >= 0 && key < arr[j]) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j + 1] = key; 
    }
}

    /**
     merge sort an array, l is the left index, r is the right index
     */
void merge_sor(int *arr, int l, int r) {
    if (l < r) {
        if ((r - l) < 40) {
            insertion_sort(arr + l, r - l + 1);
        } else {
            int m = (l + r) / 2;
            merge_sor(arr, l, m);
            /*trickier, arr + (m - l + 1)*/
            merge_sor(arr + (m - l + 1), m + 1, r);
            merge(arr, l, m, r);	
        }
    }
    
}