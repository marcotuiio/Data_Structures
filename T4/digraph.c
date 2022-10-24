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

    Edge newEdge = insereFim(graph->adjacency[from], to, from);  // inserindo na lista de adjacencia de from o nó to (from-aresta-to)
    graph->nEdges++;
    setEdgeInfo(g, newEdge, info);

    return newEdge;
}

Edge getEdge(Digraph g, Node from, Node to) {
    StDigraph *graph = g;
    Edge e = NULL;
    for (int i = 0; i < from; i++) {
        e = encontraAresta(graph->adjacency[from], to);
    }
    return e;
}

Node getFromNode(Digraph g, Edge e) {
    return getFromAresta(e);
}

Node getToNode(Digraph g, Edge e) {
    return getToAresta(e);
}

InfoEdge getEdgeInfo(Digraph g, Edge e) {
    return getInfoFromEdge(e);
}

void setEdgeInfo(Digraph g, Edge e, InfoEdge info) {
    setInfoFromEdge(e, info);
}

void removeEdge(Digraph g, Edge e) {
    StDigraph *graph = g;
    graph->nEdges--;
    removeAresta(g, e);
}

void disableEdge(Digraph g, Edge e) {
    StDigraph *graph = g;
    graph->nEdges--;
    setEnabled(g, false);
}

void enableAresta(Digraph g, Edge e) {
    StDigraph *graph = g;
    graph->nEdges++;
    setEnabled(g, true);
}

void enableAllEdges(Digraph g) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        for (Edge e = getFirst(graph->adjacency[i]); e; e = getNext(graph->adjacency[i])) {
            setEnabled(g, true);
        }
    }
}

bool isDisabled(Digraph g, Edge e) {
    return !getEnabled(e);
}

void delEdge(Edge e) {
    freeEdgeInfo(e);
}

bool isAdjacent(Digraph g, Node from, Node to) {
    StDigraph *graph = g;
    return encontraAresta(graph->adjacency[from], to);
}

void adjacentNodes(Digraph g, Node node, Lista nosAdjacentes) {
    StDigraph *graph = g;
    for (Edge e = getFirst(graph->adjacency[node]); e; e = getNext(graph->adjacency[node])) {
        insereFim(nosAdjacentes, getToAresta(e), getFromAresta(e));
    }
}

void adjacentEdges(Digraph g, Node node, Lista arestasAdjacentes) {
    StDigraph *graph = g;
    for (Edge e = getFirst(graph->adjacency[node]); e; e = getNext(graph->adjacency[node])) {
        insereFim(arestasAdjacentes, getToAresta(e), getFromAresta(e));
    }
}

void getNodeNames(Digraph g, Lista nomesNodes) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        insereInicio(nomesNodes, getNodeName(graph->adjacency[i]));
    }
}

void getEdges(Digraph g, Lista arestas) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        for (Edge e = getFirst(graph->adjacency[i]); e; e = getNext(graph->adjacency[i])) {
            insereFim(arestas, e, getFromAresta(e));
        }
    }
}

bool dfs(Digraph g, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra) {

}

bool bfs(Digraph g, procEdge discoverNode) {
    
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
