#include "list_graph.h"
#include "list.h"

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
    for (int i = 0; i < numVertex; i++) {
        g->adj[i] = criaLista();
    }
    return g;
}

void insertEdge(void *graph, int from, int to) {
    Graph *g = graph;
    insereFim(g->adj[from], to);  // inserindo na lista de adjacencia de from o nó to (from-aresta-to)
    g->n_edges++;
}

void removeEdge(void *graph, int from, int to) {
    Graph *g = graph;
    removeCelula(g->adj[from], to);  // removendo da lista de adjacencia de from o nó to (from-x-to)
    g->n_edges--;
}

bool hasEdge(void *graph, int from, int to) {
    Graph *g = graph;
    return encontraCelula(g->adj[from], to) != -999 ? true : false;
}

int numEdges(void *graph) {
    Graph *g = graph;
    return g->n_edges;
}

void printGraph(void *graph) {
    Graph *g = graph;
    FILE *dot = fopen("list_graph.dot", "w");
    fprintf(dot, "digraph G {\n\n");
    fprintf(dot, "\tnode [fontname=\"Helvetica,Arial,sans-serif\" style=\"filled\"]\n");
    fprintf(dot, "\tedge [fontname=\"Helvetica,Arial,sans-serif\" color=\"black\"]\n\n");
    
    for (int i = 0; i < g->n_vertices; i++) {
        fprintf(dot, "\tnode [label=\"%d\"] %d;\n", i, i);
    }
    fprintf(dot, "\n");
    for (int i = 0; i < g->n_vertices; i++) {
        for (void *cell = getFirst(g->adj[i]); cell; cell = getNext(g->adj[i], cell)) {
            int info = getInfo(cell);
            fprintf(dot, "\t%d -> %d;\n", i, info);
        }
    }

    fprintf(dot, "\n}");
    fclose(dot);
}

void printTerminal(void *g) {
    Graph *graph = g;

    for (int i = 0; i < graph->n_vertices; i++) {
        printf("list of vertex %d: ", i);
        printList(graph->adj[i]);
    }
}

void killGraph(void *g) {
    Graph *graph = g;

    for (int i = 0; i < graph->n_vertices; i++) {
        freeList(graph->adj[i]);
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
}
