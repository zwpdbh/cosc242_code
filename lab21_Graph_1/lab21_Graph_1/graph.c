#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


struct vertexrec {
    int predecessor;
    int distance;
    state_t state;
    int finish;
};

struct graphrec {
    int **edges;
    int size;
    vertex *vertices;
};

graph graph_new(int size_of_vertices) {
    graph g;
    
    return g;
}