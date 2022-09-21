#include "matrix_graph.h"

typedef struct graph {
    int v;  // number of vertices
    int** e;  // adjacency matrix
} Graph;

void* createGraph(int v) {
    Graph* g = calloc(1, sizeof(Graph));
    g->v = v;
    g->e = calloc(g->v, sizeof(int*));
    for (int i = 0; i < g->v; i++) {
        g->e[i] = calloc(v, sizeof(int));
    }
    return g;
}

void freeGraph(void* g) {
    Graph* graph = g;
    for (int i = 0; i < graph->v; i++) {
        if (graph->e[i]) {
            free(graph->e[i]);
        }
    }
    free(graph->e);
    free(graph);
}

void printGraph(void* g) {
    Graph* graph = g;
    FILE *dot = fopen("graph.dot", "w");
    fprintf(dot, "digraph {\n");
    for (int from = 0; from < graph->v; from++) {
        for (int to = 0; to < graph->v; to++) {
            if (graph->e[from][to]) {
                fprintf(dot, "\t%d -> %d;\n", from, to);
            }
        }   
    }
    fprintf(dot, "}\n");
    fclose(dot);
}   

bool addEdge(void* g, int from, int to) {
    Graph* graph = g;
    if (hasEdge(g, from, to)) {
        return false;
    }
    graph->e[from][to] = 1;
    return true;
}

bool hasEdge(void* g, int from, int to) {
    Graph* graph = g;
    return graph->e[from][to] == 1 ? true : false;
}

int getInfo(void* g, int from, int to) {
    Graph* graph = g;
    return graph->e[from][to];
}

bool removeEdge(void* g, int from, int to) {
    Graph* graph = g;
    if (!hasEdge(g, from, to)) {
        return false;
    }
    graph->e[from][to] = 0;
    return true;
}