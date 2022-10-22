#include "digraph.h"

typedef struct StNode {
    Lista adjacentes;
    InfoNode info;
} StNode;

typedef struct StDigraph {
    StNode *nodes;
    Hashtable nodeNames;
    int nVertex, nEdges;
} StDigraph;

typedef struct StEdge {
    bool habilitada;
    double peso;
    Node adjacentes;
    InfoEdge info;
    char* from;
    char* to;
} StEdge;

Digraph createGraph(int nVert) {
    StDigraph *g = calloc(1, sizeof(StDigraph));
    g->nVertex = nVert;
    g->nodes = calloc(nVert, sizeof(StNode));  // aloca espaço para nVert nodes

    for (int i = 0; i < nVert; i++) {
        g->nodes[i].adjacentes = createList();  // inicializa listas de cada vertice
    }

    return g;
}

Edge addEdge(Digraph g, Node from, Node to, InfoEdge info) {
       
}