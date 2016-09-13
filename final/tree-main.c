#include <stdio.h>
#include "mylib.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "getopt.h"
#include <time.h>

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
    printf("Usage: ./tree-asgn [OPTION]... <STDIN>\n");
    printf("\n");
    printf("Perform various operations using a binary tree.  By default, words\n");
    printf("are read from stdin and added to the tree, before being printed out\n");
    printf("alongside their frequencies to stdout.\n");
    printf("\n");
    printf(" -c FILENAME  Check spelling of words in FILENAME using words\n");
    printf(" \t      read from stdin as the dictionary.  Print timing\n");
    printf(" \t      info & unknown words to stderr (ignore -d & -o)\n");
    printf(" -d           Only print the tree depth (ignore -o)\n");
    printf(" -f FILENAME  Write DOT output to FILENAME (if -o given)\n");
    printf(" -o           Output the tree in DOT form to file 'tree-view.dot'\n");
    printf(" -r           Make the tree an RBT (the default is a BST)\n");
    printf(" -h           Print this message\n");
    printf("\n");
}

/**
 * main programme will be excuted.
 * By default, words are read from stdin and 
 * added to tree before being printed out
 * alongside their frequencies to stdout.
 * @param an integer saying how many arguments 
 *  there are argc for “argument count”
 * @param an array of strings in which the arguments 
 *  are stored (argv for “argument vector ”).
 * @return an int to indicate if the programme excuted successfully or not.
 */
int main(int argc, char *argv[]) {
    
    const char *optstring = "c:df:orh";
    char option;
    char word[256];
    int unknownWords = 0;
    
    int withC = 0;
    char *fileToBeChecked = NULL;
    int withD = 0;
    int withO = 0;
    char *outputFileName = "./tree-view.dot";
    tree_t tree_type = BST;
    tree r;
    
    clock_t start, end;
    float fillTime;
    float searchTime;
    FILE *infile;

    /*
     * Begin processing the argument from the command line
     */
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                withC = 1;
                fileToBeChecked = optarg;
                break;
            case 'd':
                withD = 1;
                break;
            case 'f':
                outputFileName = optarg;
                break;
            case 'o':
                withO = 1;
                break;
            case 'r':
                tree_type = RBT;
                break;
            case 'h':
                printHelpInfo();
                return EXIT_SUCCESS;
            default:
                printHelpInfo();
                return EXIT_FAILURE;
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
    
    /* Checks the input file against a dictionary (-c <filename> argument)*/
    if (withC == 1) {
        /*Open file and check if it is valid*/
        if (NULL == (infile = fopen(fileToBeChecked, "r"))) {
            fprintf(stderr, "can’t find file\n");
            tree_free(r);
            return EXIT_FAILURE;
        }
        start = clock();
        /*Get words from input file, and search for them in dictionary*/
        while (getword(word, sizeof word, infile) != EOF) {
            /*If the word isn't in the dictionary*/
            if (!tree_search(r, word)) {
                printf("%s\n", word);
                unknownWords += 1;
            }
        }
        end = clock();
        searchTime = (end-start)/(double)CLOCKS_PER_SEC;
        fprintf(stderr, "Fill time\t:%f\n", fillTime);
        fprintf(stderr, "Search time\t:%f\n", searchTime);
        fprintf(stderr, "Unknown words = %d\n", unknownWords);
        fclose(infile);
        tree_free(r);
        return EXIT_SUCCESS;
        
    } else if (withD == 1) {
        printf("%d\n", tree_depth(r));
        tree_free(r);
        return EXIT_SUCCESS;
    } else if (withO == 1) {
        if (NULL == (infile = fopen(outputFileName, "w"))) {
            fprintf(stderr, "Cannot open file: %s\n", outputFileName);
            tree_free(r);
            return EXIT_FAILURE;
        }
        tree_output_dot(r, infile);
        fclose(infile);
    } else {
        tree_preorder(r, print_info);
    }

    tree_free(r);
    return EXIT_SUCCESS;
}

