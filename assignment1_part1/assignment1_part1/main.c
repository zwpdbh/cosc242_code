#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "htable.h"
#include "mylib.h"
#include <time.h>


static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char *argv[]) {
    const char *optstring = "ht:c:deps:";
    char option;
    char word[256];
    int capacity = 113;
    
    FILE *infile = NULL;
    clock_t start, end;
    
    hashing_t method = LINEAR_P;
    
    float fillTime;
    float searchTime;
    
    int unknowWords = 0;
    int numOfSnapshot = 0;
    
    htable  h;
    char *fileToBeChecked = NULL;
    int displayContentOfHashTable = 0;
    int withP = 0;
    int withS = 0;
    
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 't':
                capacity = primegt(atoi(optarg));
                break;
            case 'd':
                printf("get option -d: using DOUBLE HASHING\n");
                method = DOUBLE_H;
                break;
            case 'c':
                printf("get option -c with argument: %s\n", optarg);
                fileToBeChecked = optarg;
                break;
            case 'e':
                displayContentOfHashTable = 1;
                break;
            case 's':
                printf("get option -s with argument: %s\n", optarg);
                numOfSnapshot = atoi(optarg);
                withS = 1;
                break;
            case 'p':
                withP = 1;
                break;
            case 'h':
                /**print out usage*/
                printf("get option -h\n");
                break;
            default:
                printf("can not get corrent option, exit programm\n");
                return EXIT_FAILURE;
        }
        
    }
    
    
    h = htable_new(capacity, method);
    start = clock();
    
    if (NULL == (infile = fopen("/Users/zw/Documents/Otago/COSC242/cosc242_code/assignment1_part1/assignment1_part1/dictionary.txt", "r"))) {
        fprintf(stderr, "can’t find file\n");
        return EXIT_FAILURE;
    }

    int i = 0;
    while (getword(word, sizeof word, infile) != EOF) {
        printf("\n\n%d\t", i);
        htable_insert(h, word);
        i += 1;
    }

    end = clock();
    fillTime = (end-start)/(double)CLOCKS_PER_SEC;
    fclose(infile);
    /**
     if -c
     */
//    fileToBeChecked = "/Users/zw/Documents/Otago/COSC242/cosc242_code/assignment1_part1/assignment1_part1/document.txt";
    if (fileToBeChecked != NULL) {
        if (NULL == (infile = fopen(fileToBeChecked, "r"))) {
            fprintf(stderr, "can’t find file\n");
            return EXIT_FAILURE;
        }
        start = clock();
        while (getword(word, sizeof word, infile) != EOF) {
            if (htable_search(h, word) == 0) {
                printf("%s\n", word);
                unknowWords += 1;
            }
        }
        end = clock();
        searchTime = (end-start)/(double)CLOCKS_PER_SEC;
        printf("Fill time\t:%f\n", fillTime);
        printf("Search time\t:%f\n", searchTime);
        printf("Unknown words = %d\n", unknowWords);
    }
    
    if (withP == 0 && displayContentOfHashTable == 1) {
        htable_content(h, stdout);
        htable_print(h, print_info);
    } else if (withP !=0 && withS == 0) {
        htable_print_stats(h, stdout, 10);
    } else if (withP != 0 && withS != 0) {
        htable_print_stats(h, stdout, numOfSnapshot);
    }
    
    fclose(infile);
    free(h);
    
    return EXIT_SUCCESS;
}

