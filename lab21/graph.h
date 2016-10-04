#ifndef graph_h
#define graph_h

#include <stdio.h>

typedef enum vertext_state { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;
typedef enum graph_type {DIRECTED, UNDIRECTED} graph_t;

typedef struct graphrec *graph;
typedef struct vertexrec vertex;


extern graph graph_new(int vertices_s);
extern graph graph_free(graph g);
extern graph graph_add_edge(graph g, int v1, int v2, graph_t t);
extern void graph_print(graph g);
extern void graph_bfs(graph g, int source);

#endif /* graph_h */
