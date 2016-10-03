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

static void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

graph graph_new(int vertices_s) {
    int i;
    graph g = emalloc(sizeof(*g));
    g->size = vertices_s;
    g->vertices = emalloc(g->size * sizeof(g->vertices[0]));
    g->edges = emalloc(g->size * sizeof(g->edges[0]));
    for (i = 0; i < vertices_s; i++) {
        g->edges[i] = emalloc(g->size * sizeof(g->edges[0][0]));
    }
    return g;
}

graph graph_free(graph g) {
    int i;
    for (i = 0; i < g->size; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->vertices);
    free(g);
    return g;
}