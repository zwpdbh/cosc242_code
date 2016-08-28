#include <stdio.h>
#include "mylib.h"
#include "bst.h"
#include <stdlib.h>

void print_key(char *s) {
    printf("%s\n", s);
}


int main(void) {
    char word[256];
    char op;
    
    bst b = bst_new();
    
    while (2 == scanf(" %c %255s", &op, word)) {
        if ('+' == op) {
            b = bst_insert(b, word);
        } else if ('?' == op) {
            printf("%d %s\n", bst_search(b, word), word);
        }
    }
    bst_preorder(b, print_key);
    
    return EXIT_SUCCESS;
}



