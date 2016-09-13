#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "getopt.h"
#include "htable.h"
#include "mylib.h"



/**
 * a function will be passed into the tree traversal function.
 * @param freq represent the frequency of the word.
 * @param word is the key in the node.
 */
static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

/**
 * a function will be called when -h option is used. It prints out the helper
 * message.
 */
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

/**
 * main programme will be excuted.
 * By default, words are read from stdin and
 * added to hashtable before being printed out
 * alongside their frequencies to stdout.
 * @param argc an integer saying how many arguments
 *  there are argc for “argument count”
 * @param argv an array of strings in which the arguments
 *  are stored (argv for “argument vector ”).
 * @return integer 1 to indicate if the programme excuted successfully or not.
 */
int main(int argc, char *argv[]) {
    const char *optstring = "ht:c:deps:";
    char option;
    char word[256];
    int capacity = 113;

    FILE *infile = NULL;
    clock_t start, end;

    hashing_t method = LINEAR_P;

    double fillTime;
    double searchTime;

    int unknownWords = 0;
    int numOfSnapshot = 0;

    htable  h;
    char *fileToBeChecked = NULL;
    int withC = 0;
    int withE = 0;
    int withP = 0;
    int withS = 0;
    /*
     * Begin processing the argument from the command line
     */
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 't':
                capacity = primegt(atoi(optarg));
                if(capacity <= 0){
                    return EXIT_FAILURE;
                }
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

    /* prints all the details of the table (-e argument)*/
    if (withE == 1) {
        htable_print_entire_table(h, stderr);
    }

    /* Checks the input file against a dictionary (-c <filename> argument)*/
    if (withC == 1) {
        /*open file and check if it is valid*/
        if (NULL == (infile = fopen(fileToBeChecked, "r"))) {
            fprintf(stderr, "Cannot find file: %s\n", fileToBeChecked);
            htable_free(h);
            return EXIT_FAILURE;
        }
        start = clock();
        /*Get words from input file, and search for them in the dictionary*/
        while (getword(word, sizeof word, infile) != EOF) {
            /*If the word isn't in the dictionary*/
            if (htable_search(h, word) == 0) {
                printf("%s\n", word);
                unknownWords += 1;
            }
        }
        end = clock();
        fclose(infile);
        searchTime = (end-start)/(double)CLOCKS_PER_SEC;
        fprintf(stderr, "Fill time\t:%f\n", fillTime);
        fprintf(stderr, "Search time\t:%f\n", searchTime);
        fprintf(stderr, "Unknown words = %d\n", unknownWords);

        htable_free(h);
        return EXIT_SUCCESS;
    }


    /*Prints table stats (-p -s arguments)*/
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
