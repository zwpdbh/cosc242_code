

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getopt.h"

void *emalloc(size_t s) {
    void *result = malloc(s);
    
    if (NULL == result) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int **lcs_length(int **table, char *rowSeq, char *colSeq) {

    int indexCol;
    int indexRow;

    long sizeOfCol = strlen(rowSeq);
    long sizeOfRow = strlen(colSeq);

    
    for (indexRow = 1; indexRow <= sizeOfRow; indexRow++) {
        for (indexCol = 1; indexCol <= sizeOfCol; indexCol++) {
            if (colSeq[indexRow - 1] ==rowSeq[indexCol - 1]) {
                table[indexRow][indexCol] = table[indexRow - 1][indexCol - 1] + 1;
            } else if (table[indexRow][indexCol - 1] >= table[indexRow - 1][indexCol]) {
                table[indexRow][indexCol] = table[indexRow][indexCol - 1];
            } else {
                table[indexRow][indexCol] = table[indexRow - 1][indexCol - 1];
            }
        }
    }
    
    return table;
}

void print_table(char *rowSeq, char *seq2, int **table, int rows, int cols) {
    int i = 0, j = 0;
    int width = table[rows][cols] > 9 ? 2 : 1;
    printf("%*c ", width+1,  ' ');
    while (seq2[i] != '\0') {
        printf("%*c", width+1, seq2[i++]);
    }
    printf("\n");
    for (i = 0; i <= rows; i++) {
        for (j = 0; j <= cols; j++) {
            if (j == 0) {
                printf("%c ", (i==0) ? ' ' : rowSeq[i-1]);
            }
            printf("%*d ", width, (table[i][j]));
        }
        printf("\n");
    }
}


int main(int argc, char *argv[]) {
    char *rowSeq = NULL;
    char *colSeq = NULL;
    int **table;
    int i = 0;
    int j = 0;
    
    /** use command line argument to get two strings
    char option;

    const char *optstring = "x:y:";
    
    while((option = getopt(argc, argv, optstring)) != EOF) {
        switch(option) {
            case 'x':
                s1 = optarg;
                break;
            case 'y':
                s2 = optarg;
                break;
            default:
                printf("-x string1 -y string2\n");
                return EXIT_FAILURE;
        }
    }
    */
    
    rowSeq = "abcdefg";
    colSeq = "abcdefg";
    
    /*create a table, size is the lenght of string + 1*/
    table = emalloc((strlen(colSeq) + 1) * sizeof(table[0]));
    
    for (i = 0; i <= strlen(colSeq); i++) {
        table[i] = emalloc((strlen(rowSeq) + 1) * sizeof(table[0][0]));
    }
    
    for (i = 0; i <= strlen(colSeq); i++) {
        for (j = 0; j <=strlen(rowSeq); j++) {
            table[i][j] = 0;
        }
    }
    
    
    table = lcs_length(table, rowSeq, colSeq);
    print_table(colSeq, rowSeq, table, i - 1, j - 1);

    return EXIT_SUCCESS;
}
