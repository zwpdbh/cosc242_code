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
    FILE *infile;
    
    while (1) {
        rbt b = rbt_new();
        
        if (NULL == (infile = fopen("/Users/zw/Documents/Otago/COSC242/cosc242_code/lab14_BinarySearchTree/lab14_BinarySearchTree/search-test.txt", "r"))) {
            fprintf(stderr, "can’t find file\n");
            return EXIT_FAILURE;
        }
        
        while (2 == fscanf(infile, " %c %255s", &op, word)) {
            if ('+' == op) {
                b = rbt_insert(b, word);
            } else if ('?' == op) {
                printf("%d %s\n", rbt_search(b, word), word);
            } else if ('-' == op){
                b = rbt_delete(b, word);
                printf("After delete %s, the rbt is:\n", word);
                rbt_preorder(b, print_key);
            }
        }
        
        rbt_free(b);
        fclose(infile);
    }
    
    return EXIT_SUCCESS;
}
