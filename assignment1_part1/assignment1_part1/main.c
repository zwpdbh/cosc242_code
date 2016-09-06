#include <stdio.h>
#include <stdlib.h>
#include "getopt.h"
#include "htable.h"
#include "mylib.h"


static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char *argv[]) {
    const char *optstring = "hc:deps:t:";
    char option;
    
    int capacity = 113;
    hashing_t method = LINEAR_P;
    
    htable h;
    
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        printf("the option is: %c\n", option);
        switch (option) {
            case 'd':
                /**
                 -d use double hashing
                 */
                printf("get option -d\n");
                method = DOUBLE_H;
            case 't':
                /**
                 Use the first prime >= tablesize as the size of your hash table.
                 You can assume that tablesize will be a number greater than 0.
                 */
                capacity = primegt(atoi(optarg));
                h = htable_new(capacity, method);
            case 'c':
                /** -c filename
                 Check the spelling of words in filename using words read from 
                 stdin as the dictionary. Print all unknown words to stdout.
                 Print timing information and unknown word count to stderr.
                 When this option is given then the -p option should be ignored.
                 */
                printf("get option -c with argument: %s\n", optarg);
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
                break;
            case 'p':
                /**
                 Print stats info using the functions provided in print-stats
                 instead of printing the frequencies and words
                 */
                break;
            case 's':
                /**
                 Display up to the given number of stats snapshots when given 
                 -p as an argument. If the table is not full then fewer 
                 snapshots will be displayed. 
                 Snapshots with 0 entries are not shown.
                 */
                break;
            case 'h':
                /**print out usage*/
                printf("get option -h\n");
                break;
            default:
                printf("exit programm\n");
                break;
        }
        
    }
    /**
     By default, words are read from stdin and added to your data structure 
     before being printed out alongside their frequencies to stdout.
     */
    printf("use real default\n");
    
}