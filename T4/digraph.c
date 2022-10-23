#include "digraph.h"

#include "list.h"

typedef struct StDigraph {
    Lista *adjacency;
    int nVertex, nEdges;
} StDigraph;

Digraph createGraph(int nVert) {
    StDigraph *g = calloc(1, sizeof(StDigraph));
    g->nVertex = nVert;
    g->adjacency = calloc(nVert, sizeof(Lista));  // aloca espaço para nVert nodes

    for (int i = 0; i < nVert; i++) {
        g->adjacency[i] = createList();  // inicializa listas de cada vertice
    }

    return g;
}

Node getNode(Digraph g, char *nome) {
    StDigraph *graph = g;

    for (int i = 0; i < graph->nVertex; i++) {
        if (!strcmp(getNodeName(graph->adjacency[i]), nome)) {
            return i;
        }
    }
}

InfoNode getNodeInfo(Digraph g, Node node) {
    StDigraph *graph = g;
    return getInfoFromVertex(graph->adjacency[node]);
}

void setNodeInfo(Digraph g, Node node, InfoNode info) {
    StDigraph *graph = g;
    setInfoFromVertex(graph->adjacency[node], info);
}

Edge addEdge(Digraph g, Node from, Node to, InfoEdge info) {
    StDigraph *graph = g;

    Edge newEdge = insereFim(graph->adjacency[from], to);  // inserindo na lista de adjacencia de from o nó to (from-aresta-to)
    graph->nEdges++;

    return newEdge;
}

Edge getEdge(Digraph g, Node from, Node to) {
    StDigraph *graph = g;
    Edge e = NULL;
    for (int i = 0; i < from; i++) {
        e = encontraCelula(graph->adjacency[from], to);
    }
    return e;
}

void killGraph(Lista g) {
    StDigraph *graph = g;

    for (int i = 0; i < graph->nVertex; i++) {
        freeList(graph->adjacency[i]);
        free(getInfoFromVertex(graph->adjacency[i]));
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    free(graph);
}
