#include "digraph.h"

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

    graph->time++;
    setVisited(graph->adjacency[posic], 'g');
    setTD(graph->adjacency[posic], graph->time);
    // setD(graph->adjacency[posic], graph->time);

    for (Edge e = getFirst(graph->adjacency[posic]); e; e = getNext(graph->adjacency[posic])) {  // percorre a lista de adjacencia do nó

        if (getVisited(graph->adjacency[getToAresta(e)]) == 'w') {  // se o nó adjacente não foi visitado
            printf("Tree Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
            if (treeEdge(graph->adjacency, e, getTD(e), getTF(e), extra)) {  // chama a função treeEdge
                return;
            }
            dfsTraverse(g, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, getToAresta(e), extra);

        } else if (getVisited(graph->adjacency[getToAresta(e)]) == 'g') {  // se o nó adjacente é cinza
            printf("Forward Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
            if (forwardEdge(graph->adjacency[posic], e, posic, getToAresta(e), extra)) {  // chama a função forwardEdge
                return;
            } 

        } else if (getVisited(graph->adjacency[getToAresta(e)]) == 'b') {                    // se o nó adjacente é preto
            if (getTD(graph->adjacency[posic]) < getTD(graph->adjacency[getToAresta(e)])) {  // se o nó adjacente foi visitado depois do nó atual
                printf("Return Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
                if (returnEdge(graph->adjacency[posic], e, posic, getToAresta(e), extra)) {  // chama a função returnEdge
                    return;
                }
            } else {  // se o nó adjacente foi visitado antes do nó atual
                printf("Cross Edge: %s -> %s\n", getId(graph->adjacency[posic]), getId(graph->adjacency[getToAresta(e)]));
                if (crossEdge(graph->adjacency[posic], e, posic, getToAresta(e), extra)) {  // chama a função crossEdge
                    return;
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
            newTree(graph, extra);                     // chama fução que deve criar floresta devido ao percurso em profundidade
            dfsTraverse(graph, treeEdge, forwardEdge, returnEdge, crossEdge, newTree, i, extra);
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

    void *queue = createQueue();

    setVisited(graph->adjacency[start], 'g');
    setD(graph->adjacency[start], 0);
    enfila(queue, &start);  // enfileira o nó inicial

    while (!isEmpty(queue)) {
        Node *currentVertex = desenfila(queue);  // desenfila o primeiro nó da fila (Lista *)
        Lista adj = criaLista();
        adjacentNodes(graph, (*currentVertex), adj);        // pega os nós adjacentes do nó atual
        for (Node *n = getFirst(adj); n; n = getNext(n)) {  // percorre a lista de adjacencia do nó atual

            if (getVisited(graph->adjacency[(*n)]) == 'w') {  // se o nó adjacente não foi visitado
                // se o nó atual e o nó adjacente são adjacentes
                // aresta: currentVertex -> n
                Edge e = getEdge(g, getNode(g, getId(graph->adjacency[(*currentVertex)])), (*n));
                // printf("Discovering edge %s -> %s\n", getId(graph->adjacency[(*currentVertex)]), getId(graph->adjacency[(*n)]));
                discoverNode(graph, e, getTD(graph->adjacency[(*n)]), getTF(graph->adjacency[(*n)]), extra);
                setVisited(graph->adjacency[(*n)], 'g');                                     // marca o nó adjacente como visitado
                setD(graph->adjacency[(*n)], getD(graph->adjacency[(*currentVertex)]) + 1);  // marca a distância do nó adjacente
                enfila(queue, n);                                                            // enfileira o nó adjacente
            }
        }
        freeList(adj);
    }
    return true;
}

/////////////////////////// DIJKSTRA ///////////////////////////

void initDijkstra(Digraph g, int start) {
    StDigraph *graph = g;
    for (int i = 0; i < graph->nVertex; i++) {  // para todos os vertices
        setD(graph->adjacency[i], -1);          // marca a distância como infinito
        setVisited(graph->adjacency[i], 'w');   // marca o nó como não processado
    }
    setD(graph->adjacency[start], 0);  // marca a distância do nó inicial como 0
}

void relaxDijkstra(Digraph g, Node u, Node v, double w) {  // u é o nó atual, v é o nó adjacente, w é o peso da aresta
    StDigraph *graph = g;
    if (getD(graph->adjacency[v]) > getD(graph->adjacency[u]) + w) {  // se a distância do nó adjacente for maior que a distância do nó atual + o peso da aresta
        setD(graph->adjacency[v], getD(graph->adjacency[u]) + w);
    }
}

int compareDijkstraSpeed(Chave ch1, Chave ch2) {
    double *d1 = ch1;
    double *d2 = ch2;
    if (d1 < d2) {
        return 1;
    } else if (d1 > d2) {
        return -1;
    } else {
        return 0;
    }
}

int compareDijkstraDistance(Chave ch1, Chave ch2) {
    double *d1 = ch1;
    double *d2 = ch2;
    if (d1 < d2) {
        return -1;
    } else if (d1 > d2) {
        return 1;
    } else {
        return 0;
    }
}

void fullDijkstra(Digraph g, double w, Node src, Node dest, ComparaChavesPQ comparator, int type) {
    StDigraph *graph = g;

    if (src == -1) {
        printf("Source node not found\n");
    }
    if (dest == -1) {
        printf("Destination node not found\n");
    }

    initDijkstra(g, src);

    PQueue *pq = NULL;
    int prio = 0;
    if (type == 0) {  // peso é a distancia
        pq = createPQ(graph->nVertex, compareDijkstraDistance);
        prio = 10000 / getWeightDij(graph->adjacency[src]);

    } else {  // peso é a velocidade
        pq = createPQ(graph->nVertex, compareDijkstraSpeed);
        prio = 10000 * getWeightDij(graph->adjacency[src]);
    }
    insertPQ(pq, getNodeInfo(g, src), graph->adjacency[src], prio);

    while (src != dest) {  // !isEmptyPQ(pq)
        PQInfo maxPrio = removeMaximumPQ(pq);
        Node u = getNode(g, getId(maxPrio));
        setVisited(graph->adjacency[u], 'b');  // marca o nó como processado

        for (void *n = getFirst(graph->adjacency[u]); n; n = getNext(graph->adjacency[u])) {  // percorre a lista de adjacencia do nó atual

            if (getVisited(n) == 'w') {  // se o nó adjacente não foi processado
                // Edge e = getEdge(g, getNode(g, getId(graph->adjacency[u])), j);
                Node nVert = getNode(g, getId(n));

                if (type == 0) {  // peso é a distancia
                    prio = 10000 / getWeightDij(graph->adjacency[src]);

                } else {
                    prio = 10000 * getWeightDij(graph->adjacency[src]);
                }

                relaxDijkstra(g, u, getNode(g, getId(n)), w);  // Compara e atribui os pesos das arestas
                insertPQ(pq, getNodeInfo(g, nVert), graph->adjacency[getNode(g, getId(n))], prio);
            }
        }

        PQInfo *info = getMaximumPQ(pq);
        src = getNode(g, getId(info));
    }
}

/////////////////////////// END_DIJKSTRA ///////////////////////////

int getGraphSize(Digraph g) {
    StDigraph *graph = g;
    return graph->nVertex;
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
