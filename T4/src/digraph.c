#include "digraph.h"
#include "queue.h"
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
        g->adjacency[i] = criaLista();  // inicializa listas de cada vertice
    }

    return g;
}

Digraph cloneOnlyVertices(Digraph g, bool keepInfo) {
    StDigraph *graph = g;
    Digraph newGraph = createGraph(graph->nVertex);

    for (int i = 0; i < graph->nVertex; i++) {
        if (keepInfo) {
            setNodeInfo(newGraph, i, getNodeInfo(g, i));
        }
    }

    return newGraph;
}

Digraph cloneOnlyEnabled(Digraph g, bool keepInfo) {
    StDigraph *graph = g;
    Digraph newGraph = cloneOnlyVertices(g, keepInfo);

    for (int i = 0; i < graph->nVertex; i++) {
        for (int j = 0; j < graph->nVertex; j++) {
            Edge o = getEdge(g, i, j);
            if (o && !isDisabled(g, o)) {
                addEdge(newGraph, i, j, NULL);
                if (keepInfo) {
                    Edge e = getEdge(newGraph, i, j); 
                    setEdgeInfo(newGraph, e, getEdgeInfo(g, o));
                }
            }
        }
    }

    return newGraph;
}

Digraph cloneAll(Digraph g, bool keepInfo) {
    StDigraph *graph = g;
    Digraph newGraph = cloneOnlyVertices(g, keepInfo);

    for (int i = 0; i < graph->nVertex; i++) {
        for (int j = 0; j < graph->nVertex; j++) {
            Edge o = getEdge(g, i, j);
            if (o) {
                addEdge(newGraph, i, j, NULL);
                if (keepInfo) {
                    Edge e = getEdge(newGraph, i, j); 
                    setEdgeInfo(newGraph, e, getEdgeInfo(g, o));
                }
            }
        }
    }

    return newGraph;
}

void setNodeName(Digraph g, Node n, char *nome) {
    StDigraph *graph = g;
    setName(graph->adjacency[n], nome);
}

void addVerticesNames(Digraph g, char *nomes[], int nNomes) {
    StDigraph *graph = g;
    for (int i = 0; i < nNomes; i++) {
        setName(graph->adjacency[i], nomes[i]);
    }
}

Node getNode(Digraph g, char *nome) {
    StDigraph *graph = g;

    for (int i = 0; i < graph->nVertex; i++) {
        if (!strcmp(getName(graph->adjacency[i]), nome)) {
            return i;
        }
    }
    return -1;
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

    Edge newEdge = insereFim(graph->adjacency[from], info, from, to);  // inserindo na lista de adjacencia de from o nó to (from-aresta-to)
    graph->nEdges++;
    setEdgeInfo(g, newEdge, info);

    return newEdge;
}

Edge getEdge(Digraph g, Node from, Node to) {
    StDigraph *graph = g;
    Edge e = NULL;
    for (int i = 0; i < from; i++) {
        e = encontraAresta(graph->adjacency[from], from, to);
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
    return !getEnabled(e); // se for falso retorna verdadeiro
}

void delEdge(Edge e) {
    return;
}

bool isAdjacent(Digraph g, Node from, Node to) {
    StDigraph *graph = g;
    return encontraAresta(graph->adjacency[from], from, to);
}

void adjacentNodes(Digraph g, Node node, Lista nosAdjacentes) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        if (isAdjacent(g, node, i)) {
            insereFim(nosAdjacentes, getNodeInfo(g, i), node, i);
        }
    }
}

void adjacentEdges(Digraph g, Node node, Lista arestasAdjacentes) {
    StDigraph *graph = g;
    for (Edge e = getFirst(graph->adjacency[node]); e; e = getNext(graph->adjacency[node])) {
        if (getFromAresta(e) == node) {
            insereFim(arestasAdjacentes, getEdgeInfo(g, e), node, getToAresta(e));
        }
    }
}

void getNodeNames(Digraph g, Lista nomesNodes) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        insereInicio(nomesNodes, (void *)getName(graph->adjacency[i]));
    }
}

void getEdges(Digraph g, Lista arestas) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        for (Edge e = getFirst(graph->adjacency[i]); e; e = getNext(graph->adjacency[i])) {
            insereFim(arestas, e, getFromAresta(e), getToAresta(e));
        }
    }
}

bool dfs(Digraph g, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, int start, void *extra) {
    StDigraph *graph = g;

    setVisited(graph->adjacency[start], true);
    // fazer varios ifs in invocar cada função corretamente
    // treeEdge(graph->adjacency[0], NULL, 0, 0, extra);
    // forwardEdge(graph->adjacency[0], NULL, 0, 0, extra);
    // returnEdge(graph->adjacency[0], NULL, 0, 0, extra);
    // crossEdge(graph->adjacency[0], NULL, 0, 0, extra);

    for (int i = 0; i < graph->nVertex; i++) {
        if (!getVisited(graph->adjacency[start])) {
            dfs(graph, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, start, extra);
        }
    }
    return true;
}

bool bfs(Digraph g, procEdge discoverNode, int start) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        setVisited(graph->adjacency[i], false);
    }

    void *queue = createQueue();

    setVisited(graph->adjacency[start], true);
    enfila(queue, getInfoFromVertex(graph->adjacency[start]));

    while (!isEmpty(queue)) {
        void *currentVertex = desenfila(queue);
        printf("Visiting vetex %p\n", currentVertex);

        for (int adjVertex = 0; adjVertex < graph->nVertex; adjVertex++) {
            if (!getVisited(graph->adjacency[adjVertex])) {
                setVisited(graph->adjacency[adjVertex], true);
                enfila(queue, graph->adjacency[adjVertex]);
            }
        }
    }
    return true;
}

void killGraph(Digraph g) {
    StDigraph *graph = g;

    for (int i = 0; i < graph->nVertex; i++) {
        freeList(graph->adjacency[i]);
        free(getInfoFromVertex(graph->adjacency[i]));
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    free(graph);
}
