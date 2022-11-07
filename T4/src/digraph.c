#include "digraph.h"

#include "list.h"
#include "queue.h"

typedef struct StDigraph {
    Lista *adjacency;
    int nVertex, nEdges;
    int time;
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
    setId(graph->adjacency[n], nome);
}

void addVerticesNames(Digraph g, char *nomes[], int nNomes) {
    StDigraph *graph = g;
    for (int i = 0; i < nNomes; i++) {
        setId(graph->adjacency[i], nomes[i]);
    }
}

Node getNode(Digraph g, char *nome) {
    StDigraph *graph = g;

    for (int i = 0; i < graph->nVertex; i++) {
        if (!strcmp(getId(graph->adjacency[i]), nome)) {
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

    if (graph->adjacency[from]) {
        Edge newEdge = insereFim(graph->adjacency[from], info, from, to);  // inserindo na lista de adjacencia de from o nó to (from-aresta-to)
        graph->nEdges++;
        // printf("%p\n", newEdge);
        // setEdgeInfo(g, newEdge, info);
        return newEdge;
    }
    return NULL;
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
    return !getEnabled(e);  // se for falso retorna verdadeiro
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
        insereInicio(nomesNodes, (void *)getId(graph->adjacency[i]));
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

void dfsTraverse(Digraph g, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, int posic, void *extra) {
    StDigraph *graph = g;

    newTree(graph, extra);
    setTD(graph->adjacency[posic], graph->time);
    graph->time++;
    setVisited(graph->adjacency[posic], 'g');
    setD(graph->adjacency[posic], graph->time);

    for (Edge e = getFirst(graph->adjacency[posic]); e; e = getNext(graph->adjacency[posic])) {  // percorre a lista de adjacencia do nó

        if (getVisited(graph->adjacency[getToAresta(e)]) == 'w') {     // se o nó adjacente não foi visitado
            treeEdge(graph->adjacency, e, getTD(e), getTF(e), extra);  // chama a função treeEdge
            dfsTraverse(g, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, getToAresta(e), extra);

        } else if (getVisited(graph->adjacency[getToAresta(e)]) == 'g') {           // se o nó adjacente é cinza
            forwardEdge(graph->adjacency[posic], e, posic, getToAresta(e), extra);  // chama a função forwardEdge

        } else if (getVisited(graph->adjacency[getToAresta(e)]) == 'b') {                    // se o nó adjacente é preto
            if (getTD(graph->adjacency[posic]) < getTD(graph->adjacency[getToAresta(e)])) {  // se o nó adjacente foi visitado depois do nó atual
                returnEdge(graph->adjacency[posic], e, posic, getToAresta(e), extra);        // chama a função returnEdge

            } else {                                                                  // se o nó adjacente foi visitado antes do nó atual
                crossEdge(graph->adjacency[posic], e, posic, getToAresta(e), extra);  // chama a função crossEdge
            }
        }
    }
    setVisited(graph->adjacency[posic], 'b');
    setTF(graph->adjacency[posic], graph->time);
    graph->time++;
}

bool dfs(Digraph g, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra) {  // profundidade
    StDigraph *graph = g;

    graph->time = 0;
    for (int j = 0; j < graph->nVertex; j++) {
        setVisited(graph->adjacency[j], 'w');
    }

    for (int i = 0; i < graph->nVertex; i++) {
        if (getVisited(graph->adjacency[i]) == 'w') {
            dfsTraverse(graph, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, i, extra);
        }
    }
    return true;
}

bool bfs(Digraph g, procEdge discoverNode) {  // largura
    StDigraph *graph = g;
    int start = 0;
    for (int i = 0; i < graph->nVertex; i++) {
        setVisited(graph->adjacency[i], 'w');
        setD(graph->adjacency[i], -1);
    }

    void *queue = createQueue();

    setVisited(graph->adjacency[start], 'g');
    setD(graph->adjacency[start], 0);
    enfila(queue, graph->adjacency[start]);

    while (!isEmpty(queue)) {
        void *currentVertex = desenfila(queue);

        for (int adjVertex = 0; adjVertex < graph->nVertex; adjVertex++) {
            if (getVisited(graph->adjacency[adjVertex]) == 'w') {
                discoverNode(currentVertex, graph->adjacency[adjVertex], getTD(graph->adjacency[adjVertex]), getTD(graph->adjacency[adjVertex]), NULL);
                setVisited(graph->adjacency[adjVertex], 'g');
                setD(graph->adjacency[adjVertex], getD(currentVertex) + 1);
                enfila(queue, graph->adjacency[adjVertex]);
            }
        }
    }
    return true;
}

void killGraph(Digraph g) {
    StDigraph *graph = g;
    printf("Killing graph with %d nodes and %d edges\n", graph->nVertex, graph->nEdges);
    for (int i = 0; i < graph->nVertex; i++) {
        freeList(graph->adjacency[i]);
        free(getInfoFromVertex(graph->adjacency[i]));
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    free(graph);
}
