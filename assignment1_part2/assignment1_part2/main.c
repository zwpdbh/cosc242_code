#include <stdio.h>
#include "mylib.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "getopt.h"
#include <time.h>


static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char *argv[]) {
    const char *optstring = "c:dpf:orh";
    char option;
    char word[256];
    int unknowWords = 0;
    
    int withC = 0;
    char *fileToBeChecked = NULL;
    int withD = 0;
    int withP = 0;
    int withF = 0;
    int withO = 0;
    char *outPutFileName = NULL;
    tree_t tree_type = BST;
    tree r;
    
    clock_t start, end;
    float fillTime;
    float searchTime;
    FILE *infile;
    
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                withC = 1;
                fileToBeChecked = optarg;
                break;
            case 'd':
                withD = 1;
                withP = 0;
                break;
            case 'p':
                withP = 1;
                withD = 0;
            case 'f':
                withF = 1;
                break;
            case 'o':
                withO = 1;
                outPutFileName = optarg;
                break;
            case 'r':
                tree_type = RBT;
                break;
            case 'h':
                printf("should print out the help message");
                break;
            default:
                printf("should use -h to print out help message");
                EXIT_SUCCESS;
        }
    }
    
    r = tree_new(tree_type);
    
    start = clock();
    
    while (getword(word, sizeof word, stdin) != EOF) {
        r = tree_insert(r, word);
        r = setColourBlack(r);
    }
    
    end = clock();
    fillTime = (end-start)/(double)CLOCKS_PER_SEC;
    
    
    if (withD == 1) {
        printf("%d\n", tree_depth(r));
        EXIT_SUCCESS;
    } else if (withC == 1) {
        /**
         -c fileToBeChecked
         */
        if (NULL == (infile = fopen(fileToBeChecked, "r"))) {
            fprintf(stderr, "can’t find file\n");
            return EXIT_FAILURE;
        }
        start = clock();
        while (getword(word, sizeof word, infile) != EOF) {
            if (tree_search(r, word)) {
                printf("%s\n", word);
                unknowWords += 1;
            }
        }
        end = clock();
        searchTime = (end-start)/(double)CLOCKS_PER_SEC;
        printf("Fill time\t:%f\n", fillTime);
        printf("Search time\t:%f\n", searchTime);
        printf("Unknown words = %d\n", unknowWords);
        fclose(infile);
        
        return EXIT_SUCCESS;
    } else if (withP == 1) {
        printf("?");
    } else if (withO == 1 && withF ==0) {
        if (NULL == (infile = fopen("output-dot.txt", "r"))) {
            fprintf(stderr, "can’t find file\n");
            return EXIT_FAILURE;
        }
        tree_output_dot(r, infile);
        fclose(infile);
    } else if (withO == 1 && withF == 1) {
        if (NULL == (infile = fopen(outPutFileName, "r"))) {
            fprintf(stderr, "can’t find file\n");
            return EXIT_FAILURE;
        }
        tree_output_dot(r, infile);
        fclose(infile);
    } else {
        tree_preorder(r, print_info);
    }
    
}

