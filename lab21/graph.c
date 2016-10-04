#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"

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
    int j;
    graph g = emalloc(sizeof(*g));
    g->size = vertices_s;
    g->vertices = emalloc(g->size * sizeof(g->vertices[0]));
    g->edges = emalloc(g->size * sizeof(g->edges[0]));
    for (i = 0; i < vertices_s; i++) {
        g->edges[i] = emalloc(g->size * sizeof(g->edges[0][0]));
    }
    for(i = 0; i < g->size; i++) {
        for(j = 0; j < g->size; j++) {
            g->edges[i][j] = 0;
        }
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
    int i = 0;
    int j = 0;
    printf("adjacency list:\n");
    for (i = 0; i < g->size; i++) {
        printf("%d | ", i);
        for (j = 0; j < g->size; j++) {
            if (g->edges[i][j] == 1) {
                printf("%d, ", j);
            }
        }
        printf("\n");
    }
}

void graph_bfs(graph g, int source) {
    queue q = queue_new();
    int i = -1;
    state_t unv = UNVISITED;
    state_t vis = VISITED_SELF;
    state_t vid = VISITED_DESCENDANTS;
    
    int u = -1;
   

    for(i = 0; i < g->size; i++) {
        g->vertices[i].state = unv;
        g->vertices[i].distance = -1;
        g->vertices[i].predecessor = -1;
    }

   g->vertices[source].state = vis;
   g->vertices[source].distance = 0;
   
   enqueue(q, source);

   while(queue_size(q) > 0) {
        u = dequeue(q);
        
        for(i = 0; i < g->size; i++) {
            if(g->edges[u][i] == 1 && g->vertices[i].state == unv) {
               g->vertices[i].state = vis;
               g->vertices[i].distance = 1 + g->vertices[u].distance;
               g->vertices[i].predecessor = u;
               enqueue(q, i);
            }
        }
        g->vertices[u].state = vid;
   }

   for(i = 0; i < g->size; i++) {
    printf("%d\t%d   %d\n", i, g->vertices[i].distance, g->vertices[i].predecessor);
   }
   q = queue_free(q);
}
