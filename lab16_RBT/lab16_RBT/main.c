#include <stdio.h>
#include "mylib.h"
#include "rbt.h"
#include <stdlib.h>
#include <stdio.h>


void print_key(char *s) {
    printf("%s\n", s);
}


int main(void) {
    char word[256];
    char op;
    
    int count = 1;
    while (count > 0) {
        rbt r =  rbt_new();
        
        /**
         if (NULL == (infile = fopen("/Users/zw/Documents/Otago/COSC242/cosc242_code/lab16_RBT/lab_test.txt", "r"))) {
         fprintf(stderr, "can’t find file\n");
         return EXIT_FAILURE;
         }
         */
        
        while (2 == fscanf(stdin, " %c %255s", &op, word)) {
            if ('+' == op) {
                printf("\nInsert %s: \n", word);
                r =  rbt_insert(r, word);
                rbt_preorder(r, print_key);
            } else if ('?' == op) {
                printf("%d %s\n", rbt_search(r, word), word);
            } else if ('-' == op){
                r =  rbt_delete(r, word);
                printf("After delete %s, the rbt is:\n", word);
                rbt_preorder(r, print_key);
            }
        }
        
        
        rbt_free(r);
        
        count = count - 1;
    }
    
    return EXIT_SUCCESS;
}
