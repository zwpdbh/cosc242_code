#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "htable.h"
#include "mylib.h"
#include <time.h>
#include <string.h>


static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

void printHelpInfo() {
    printf("Usage: ./htable-asgn [OPTION]... <STDIN>\n");
    printf("\n");
    printf("Perform various operations using a hash table.  By default, words are\n");
    printf("read from stdin and added to the hash table, before being printed out\n");
    printf("alongside their frequencies to stdout.\n");
    printf("\n");
    printf(" -c FILENAME  Check spelling of words in FILENAME using words\n");
    printf(" \t      from stdin as dictionary.  Print unknown words to\n");
    printf(" \t      stdout, timing info & count to stderr (ignore -p)\n");
    printf(" -d           Use double hashing (linear probing is the default)\n");
    printf(" -e           Display entire contents of hash table on stderr\n");
    printf(" -p           Print stats info instead of frequencies & words\n");
    printf(" -s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n");
    printf(" -t TABLESIZE Use the first prime >= TABLESIZE as htable size\n");
    printf("\n");
    printf(" -h           Display this message");
    printf("\n");
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
    int withC = 0;
    int withE = 0;
    int withP = 0;
    int withS = 0;
    
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 't':
                capacity = primegt(atoi(optarg));
                break;
            case 'd':
                method = DOUBLE_H;
                break;
            case 'c':
                withC = 1;
                fileToBeChecked = optarg;
                break;
            case 'e':
                withE = 1;
                break;
            case 's':
                numOfSnapshot = atoi(optarg);
                withS = 1;
                break;
            case 'p':
                withP = 1;
                break;
            case 'h':
                printHelpInfo();
                return EXIT_SUCCESS;
            default:
                printHelpInfo();
                return EXIT_FAILURE;
        }
        
    }
    
    
    h = htable_new(capacity, method);
    start = clock();
    

    while (getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }

    end = clock();
    fillTime = (end-start)/(double)CLOCKS_PER_SEC;
    

    if (withE == 1) {
        htable_content(h, stderr);
    }
    
    if (withC == 1) {
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
        fclose(infile);
        searchTime = (end-start)/(double)CLOCKS_PER_SEC;
        printf("Fill time\t:%f\n", fillTime);
        printf("Search time\t:%f\n", searchTime);
        printf("Unknown words = %d\n", unknowWords);
        
        htable_free(h);
        return EXIT_SUCCESS;
    }
    
    
    if (withP == 1 && withS == 0) {
        htable_print_stats(h, stdout, 10);
    } else if (withP == 1 && withS == 1) {
        htable_print_stats(h, stdout, numOfSnapshot);
    } else {
        htable_print(h, print_info);
    }
    
    htable_free(h);
    
    return EXIT_SUCCESS;
}

