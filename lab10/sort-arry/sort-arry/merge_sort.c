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


void insertion_sort(int *arr, int size) {
    /* use j to loop every elements
     * in each loop, use i to do while loop
     * key is the current item being selecting and comparing
     * */
    int j = 1;
    int i;
    for(j = 1; j < size; j++) {
        int key = arr[j];
        i = j - 1;
        while(i >= 0 && arr[i] > key) {
            arr[i+1] = arr[i];
            i--;
        }
        arr[i+1] = key;
    }
}

    /**
     merge sort an array, l is the left index, r is the right index
     */
void merge_sor(int *arr, int l, int r) {
    if (l < r) {
        if ((r - l) < 80) {
            int m = (l + r) / 2;
            insertion_sort(arr, m - l + 1);
            insertion_sort(&arr[m - l + 1], r - m);
            merge(arr, l, m, r);
        } else {
            int m = (l + r) / 2;
            merge_sor(arr, l, m);
            /*trickier, arr + (m - l + 1)*/
            merge_sor(arr + (m - l + 1), m + 1, r);
            merge(arr, l, m, r);	
        }
//        int m = (l + r) / 2;
//        merge_sor(arr, l, m);
//        /*trickier, arr + (m - l + 1)*/
////        merge_sor(arr + (m - l + 1), m + 1, r);
//        merge_sor(&arr[m - l + 1], m+1, r);
//        merge(arr, l, m, r);
    }
    
}