#include <stdio.h>
#include "getopt.h"
#include "htable.h"
#include "mylib.h"


static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char *argv[]) {
    const char *optstring = "";
    char option;
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        printf("the option is: %c\n", option);
        switch (option) {
            case 'a':
                printf("get option -a\n");
                break;
            case 'b':
                /* the argument after the -b is available
                 in the global variable 'optarg' */
                printf("get option -b with argument: %s\n", optarg);
                break;
            case 'c':
                printf("get option -c\n");
                break;
            default:
                printf("exit programm\n");
                break;
        }
        
    }
    printf("use real default\n");
    
}