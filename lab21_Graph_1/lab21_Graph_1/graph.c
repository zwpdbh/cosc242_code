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

graph graph_add_edge(graph g, int v1, int v2, graph_t t) {
    if (t == DIRECTED) {
        g->edges[v1][v2] = 1;
    } else {
        g->edges[v1][v2] = 1;
        g->edges[v2][v1] = 1;
    }
    return g;
}

void graph_print(graph g) {
    int i;
    int j;
    printf("adjacency list:\n");
    for (i = 0; i < g->size; i++) {
        printf("%d | ", i);
        for (j = 0; j < g->size; j++) {
            if (g->edges[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}