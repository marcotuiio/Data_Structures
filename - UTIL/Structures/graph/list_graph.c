#include "list_graph.h"

typedef struct graph {
    int n_vertices;
    int n_edges;
    Lista *adj;
} Graph;

void *createGraph(int numVertex) {
    Graph *g = calloc(1, sizeof(Graph));
    g->n_vertices = numVertex;
    g->n_edges = 0;
    g->adj = calloc(numVertex, sizeof(Lista));

    return g;
}

void insertEdge(void *graph, int from, int to) {
    Graph *g = graph;
    insereFim(g->adj[from], to);
    g->n_edges++;
}

void removeEdge(void *graph, int from, int to) {
    Graph *g = graph;
    removeCelula(g->adj[from], to);
    g->n_edges--;
}

bool hasEdge(void *graph, int from, int to) {
    Graph *g = graph;
    return encontraCelula(g->adj[from], to) != NULL ? true : false;
}

int numEdges(void *graph) {
    Graph *g = graph;
    return g->n_edges;
}

void printGraph(void *graph) {
    Graph *g = graph;
    FILE *dot = fopen("list_graph.dot", "w");
    fprintf(dot, "digraph G {\n\n");
    
    for (int i = 0; i < g->n_vertices; i++) {
        fprintf(dot, "\t[label=\"%d\"] %d;\n", i, i);
        for (void *cell = getFirst(g->adj[i]); cell; cell = getNext(g->adj[i], cell)) {
            void *info = getInfo(cell);
            fprintf(dot, "%d -> %d;\n", i, info);
        }
    }
    fprintf(dot, "\n}");
    fclose(dot);
}