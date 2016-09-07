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
    const char *optstring = "hc:deps:t:";
    char option;
    char word[256];
    int capacity = 113;
    hashing_t method = LINEAR_P;
    FILE *infile;
    clock_t start, end;
    float fillTime;
    float searchTime;
    int unknowWords = 0;
    int numOfKeys = 0;
    
    htable h = htable_new(capacity, method);
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        printf("the option is: %c\n", option);
        switch (option) {
            case 't':
                /**
                 Use the first prime >= tablesize as the size of your hash table.
                 You can assume that tablesize will be a number greater than 0.
                 */
                capacity = primegt(atoi(optarg));
            case 'd':
                /**
                 -d use double hashing
                 */
                printf("get option -d\n");
                method = DOUBLE_H;
            case 'c':
                printf("get option -c with argument: %s\n", optarg);
                htable_free(h);
                h = htable_new(capacity, method);
                start = clock();
                while (getword(word, sizeof word, stdin) != EOF) {
                    htable_insert(h, word);
                }
                end = clock();
                fillTime = (end-start)/(double)CLOCKS_PER_SEC;
                

                if (NULL == (infile = fopen(optarg, "r"))) {
                    fprintf(stderr, "can’t find file\n");
                    return EXIT_FAILURE;
                }
                /** -c filename
                 Check the spelling of words in filename using words read from 
                 stdin as the dictionary. Print all unknown words to stdout.
                 Print timing information and unknown word count to stderr.
                 When this option is given then the -p option should be ignored.
                 */
                start = clock();
                while (getword(word, sizeof word, infile) != EOF) {
                    if (htable_search(h, word) == 0) {
                        printf("%s\n", word);
                        unknowWords += 1;
                    }
                }
                end = clock();
                searchTime = (end-start)/(double)CLOCKS_PER_SEC;
                printf("Fill time\t:%f", fillTime);
                printf("Search time\t:%f", searchTime);
                printf("Unknown words = %d", unknowWords);
                break;
            case 'e':
                /**
                 Display entire contents of hash table on stderr using the 
                 format string "%5d %5d %5d   %s\n" to display the index, 
                 frequency, stats, and the key if it exists. 
                 (Note that spaces have been made visible in the format string 
                 so you can see how many there are).
                 */
                printf("get opetion -e\n");
                htable_content(h, stderr);
                break;
            case 's':
                /**
                 Display up to the given number of stats snapshots when given 
                 -p as an argument. If the table is not full then fewer 
                 snapshots will be displayed. 
                 Snapshots with 0 entries are not shown.
                 */
                numOfKeys = atoi(optarg);
                break;
            case 'p':
                /**
                 Print stats info using the functions provided in print-stats
                 instead of printing the frequencies and words
                 */
                if (getNumberOfKeys(h) > 0 && numOfKeys != 0) {
                    htable_print_stats(h, stdout, numOfKeys);
                } else {
                    htable_print_stats(h, stdout, getNumberOfKeys(h));
                }
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
    /**
     By default, words are read from stdin and added to your data structure 
     before being printed out alongside their frequencies to stdout.
     */
    htable_print(h, print_info);
    return EXIT_SUCCESS;
}