#ifndef graph_h
#define graph_h

#include <stdio.h>

typedef enum vertext_state { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

typedef struct graphrec *graph;
typedef struct vertexrec vertex;


extern graph graph_new(int size_of_vertices);

#endif /* graph_h */
