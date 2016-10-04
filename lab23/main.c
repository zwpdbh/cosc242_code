
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "getopt.h"

int main(int argc, char *argv[]) {
    int v1;
    int v2;
    graph g;
    char option; 
    int size = 0;
    graph_t type = DIRECTED;
    const char *optstring = "s:";

    while((option = getopt(argc, argv, optstring)) != EOF) {
        switch(option) {
            case 's':
                size = atoi(optarg);
                break;
            default:
                printf("input the number of vertices\n");
                return EXIT_FAILURE;
        }
    }

    g = graph_new(size);
    while(2==scanf("%d%d", &v1, &v2)) {
        g = graph_add_edge(g, v1, v2, type);
    }
    /**
    g = graph_add_edge(g, 0, 1, type);
    g = graph_add_edge(g, 0, 4, type);
    g = graph_add_edge(g, 5, 1, type);
    g = graph_add_edge(g, 5, 2, type);
    g = graph_add_edge(g, 5, 6, type);
    g = graph_add_edge(g, 6, 2, type);
    g = graph_add_edge(g, 6, 3, type);
    g = graph_add_edge(g, 6, 7, type);
    g = graph_add_edge(g, 3, 2, type);
    g = graph_add_edge(g, 3, 7, type);
    */
    graph_print(g);
    graph_dfs(g);
    g = graph_free(g);
    return EXIT_SUCCESS;
}
