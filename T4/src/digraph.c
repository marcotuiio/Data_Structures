#include "digraph.h"

#include "infos.h"
#include "list.h"
#include "priority_queue.h"
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
        setNodeName(newGraph, i, getNomeVertex(getNodeInfo(g, i)));
    }

    return newGraph;
}

Digraph cloneOnlyEnabled(Digraph g, bool keepInfo) {
    StDigraph *graph = g;
    Digraph newGraph = cloneOnlyVertices(g, keepInfo);

    for (int i = 0; i < graph->nVertex; i++) {
        setNodeInfo(newGraph, i, getNodeInfo(g, i));
        setNodeName(newGraph, i, getNomeVertex(getNodeInfo(g, i)));
    }

    for (int j = 0; j < graph->nVertex; j++) {
        for (Edge e = getFirst(graph->adjacency[j]); e; e = getNext(e)) {
            if (getEnabled(e)) {
                if (keepInfo) {
                    addEdge(newGraph, getFromNode(g, e), getToNode(g, e), getEdgeInfo(g, e));
                } else {
                    addEdge(newGraph, getFromNode(g, e), getToNode(g, e), NULL);
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
        if (keepInfo) {
            setNodeInfo(newGraph, i, getNodeInfo(g, i));
        }
        setNodeName(newGraph, i, getNomeVertex(getNodeInfo(g, i)));
    }

    for (int j = 0; j < graph->nVertex; j++) {
        for (Edge e = getFirst(graph->adjacency[j]); e; e = getNext(e)) {
            if (keepInfo) {
                addEdge(newGraph, getFromNode(g, e), getToNode(g, e), getEdgeInfo(g, e));
            } else {
                addEdge(newGraph, getFromNode(g, e), getToNode(g, e), NULL);
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

Node getGraphSize(Digraph g) {
    StDigraph *graph = g;
    return graph->nVertex;
}

Node getNodeGivenXY(Digraph g, double x, double y) {
    StDigraph *graph = g;
    for (Node i = 0; i < graph->nVertex; i++) {
        if (fabs(getXVertex(getNodeInfo(g, i)) - x) <= 50.0 && fabs(getYVertex(getNodeInfo(g, i)) - y) <= 50.0) {
            return i;
        }
    }
    return -1;
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

    if (node < 0 || node >= graph->nVertex) {
        printf("Erro: getNodeInfo: node %d não existe tamanho %d\n", node, graph->nVertex);
        return NULL;
    }
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
        return newEdge;
    }
    return NULL;
}

Edge getEdge(Digraph g, Node from, Node to) {
    StDigraph *graph = g;
    Edge e = encontraAresta(graph->adjacency[from], from, to);
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
    removeAresta(graph->adjacency[getFromAresta(e)], e);
}

void disableEdge(Digraph g, Edge e) {
    StDigraph *graph = g;
    graph->nEdges--;
    setEnabled(e, false);
}

void enableEdge(Digraph g, Edge e) {
    StDigraph *graph = g;
    graph->nEdges++;
    setEnabled(e, true);
}

void enableAllEdges(Digraph g) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        for (Edge e = getFirst(graph->adjacency[i]); e; e = getNext(graph->adjacency[i])) {
            setEnabled(e, true);
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
            insereAux(nosAdjacentes, i);
        }
    }
}

// void adjacentEdges(Digraph g, Node node, Lista arestasAdjacentes) {
//     StDigraph *graph = g;
//     for (Edge e = getFirst(graph->adjacency[node]); e; e = getNext(graph->adjacency[node])) {
//         if (getFromAresta(e) == node) {
//             insereFim(arestasAdjacentes, getEdgeInfo(g, e), node, getToAresta(e));
//         }
//     }
// }

Lista adjacentEdges(Digraph g, Node node) {
    StDigraph *graph = g;
    return graph->adjacency[node];
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

    graph->time++;
    setVisited(graph->adjacency[posic], 'g');
    setTD(graph->adjacency[posic], graph->time);

    for (Edge e = getFirst(graph->adjacency[posic]); e; e = getNext(e)) {  // percorre a lista de adjacencia do nó
        // printf("getTo %d || graph->adjacency[getTo] = %p\n", getToAresta(e), graph->adjacency[getToAresta(e)]);
        if (getEnabled(e)) {
            if (getVisited(graph->adjacency[getToAresta(e)]) == 'w') {  // se o nó adjacente não foi visitado
                // printf("Tree Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
                if (treeEdge(graph, e, getTD(e), getTF(e), extra)) {  // chama a função treeEdge
                    return;
                }
                dfsTraverse(g, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, getToAresta(e), extra);

            } else if (getVisited(graph->adjacency[getToAresta(e)]) == 'g') {  // se o nó adjacente é cinza
                // printf("Forward Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
                if (forwardEdge(graph, e, getTD(e), getTF(e), extra)) {  // chama a função forwardEdge
                    return;
                }

            } else if (getVisited(graph->adjacency[getToAresta(e)]) == 'b') {                    // se o nó adjacente é preto
                if (getTD(graph->adjacency[posic]) < getTD(graph->adjacency[getToAresta(e)])) {  // se o nó adjacente foi visitado depois do nó atual
                    // printf("Return Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
                    if (returnEdge(graph, e, getTD(e), getTF(e), extra)) {  // chama a função returnEdge
                        return;
                    }
                } else {  // se o nó adjacente foi visitado antes do nó atual
                    // printf("Cross Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
                    if (crossEdge(graph, e, getTD(e), getTF(e), extra)) {  // chama a função crossEdge
                        return;
                    }
                }
            }
        }
    }
    graph->time++;
    setVisited(graph->adjacency[posic], 'b');
    setTF(graph->adjacency[posic], graph->time);
}

bool dfs(Digraph g, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra) {  // profundidade
    StDigraph *graph = g;

    graph->time = 0;
    for (int j = 0; j < graph->nVertex; j++) {
        setVisited(graph->adjacency[j], 'w');  // marca todos os nós como não visitados
    }

    for (int i = 0; i < graph->nVertex; i++) {
        if (getVisited(graph->adjacency[i]) == 'w') {  // se o nó não foi visitado
            void **data = extra;
            Node aux = i;
            data[5] = &aux;
            newTree(graph, data);  // chama função que deve criar floresta devido ao percurso em profundidade
            dfsTraverse(graph, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, i, data);
        }
    }
    return true;
}

bool bfs(Digraph g, Node start, procEdge discoverNode, void *extra) {  // largura
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {
        setVisited(graph->adjacency[i], 'w');  // marca todos os nós como não visitados
        setD(graph->adjacency[i], -1);
    }

    Queue queue = createQueue();

    setVisited(graph->adjacency[start], 'g');
    setD(graph->adjacency[start], 0);
    enfila(queue, start);  // enfileira o nó inicial
    // printf("Enfileirou %d\n", start);

    while (!isEmpty(queue)) {
        Node currentVertex = desenfila(queue);  // desenfila o primeiro nó da fila (Lista *)
        // printf("currentVertex: %d\n", currentVertex);
        Lista adj = criaListaAux();
        adjacentNodes(graph, currentVertex, adj);  // pega os nós adjacentes do nó atual

        for (void *cell = getFirstAux(adj); cell; cell = getNext(cell)) {  // percorre a lista de adjacencia do nó atual
            Node adjVertex = getValueAux(cell);                            // pega o nó adjacente
            if (getVisited(graph->adjacency[adjVertex]) == 'w') {          // se o nó adjacente não foi visitado
                // se o nó atual e o nó adjacente são adjacentes
                // aresta: currentVertex -> n
                Edge e = getEdge(g, getNode(g, getId(graph->adjacency[currentVertex])), adjVertex);
                // printf("Discover Edge: %s -> %s\n", getId(graph->adjacency[currentVertex]), getId(graph->adjacency[adjVertex]));
                if (getEnabled(e)) {
                    if (discoverNode(graph, e, getTD(graph->adjacency[adjVertex]), getTF(graph->adjacency[adjVertex]), extra)) {  // chama a função discoverNode
                        return false;
                    }
                }
                setVisited(graph->adjacency[adjVertex], 'g');                              // marca o nó adjacente como visitado
                setD(graph->adjacency[adjVertex], getD(graph->adjacency[adjVertex]) + 1);  // marca a distância do nó adjacente
                enfila(queue, adjVertex);                                                  // enfileira o nó adjacente
            }
        }
        freeListaAux(adj);
    }
    free(queue);
    return true;
}

void printGraph(Digraph g) {
    StDigraph *graph = g;
    printf("Graph with %d nodes and %d edges\n", graph->nVertex, graph->nEdges);
    for (int i = 0; i < graph->nVertex; i++) {
        printf("Node %s: ", getId(graph->adjacency[i]));
        for (Edge e = getFirst(graph->adjacency[i]); e; e = getNext(e)) {
            printf("\n\t%s ", getNomeEdge(getEdgeInfo(g, e)));
        }
        printf("\n");
    }
}

void killGraph(Digraph g) {
    StDigraph *graph = g;
    printf("Killing graph with %d nodes and %d edges\n", graph->nVertex, graph->nEdges);
    // printGraph(g);
    for (int i = 0; i < graph->nVertex; i++) {
        freeList(graph->adjacency[i]);
        free(getInfoFromVertex(graph->adjacency[i]));
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    free(graph);
}
