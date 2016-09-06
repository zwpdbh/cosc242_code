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
    static tree_t type = RBT;
    
    int count = 1;
    while (1) {
        rbt r =  rbt_new(type);
        
        if (NULL == (infile = fopen("/Users/zw/Documents/Otago/COSC242/cosc242_code/lab16_RBT/lab16_RBT/test_lab.txt", "r"))) {
            fprintf(stderr, "can’t find file\n");
            return EXIT_FAILURE;
        }
        
        while (2 == fscanf(infile, " %c %255s", &op, word)) {
            if ('+' == op) {
                printf("\nInsert %s: \n", word);
                r = rbt_insert(r, word);
                r = setColourBlack(r);
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
        fclose(infile);
        count = count - 1;
    }
    
    return EXIT_SUCCESS;
}
