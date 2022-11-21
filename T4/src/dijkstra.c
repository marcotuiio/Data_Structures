#include "dijkstra.h"

void initDijkstra(Digraph g, int start) {
    for (Node i = 0; i < getGraphSize(g); i++) {  // para todos os vertices
        setD(adjacentEdges(g, i), INT_MIN);          // marca a distância como infinito
        setVisited(adjacentEdges(g, i), 'w');   // marca o nó como não processado
    }
    setD(adjacentEdges(g, start), 0);  // marca a distância do nó inicial como 0
}

void relaxDijkstra(Digraph g, Node u, Node v, double w) {  // u é o nó atual, v é o nó adjacente, w é o peso da aresta
    if (getD(adjacentEdges(g, v)) > getD(adjacentEdges(g, u)) + w) {  // se a distância do nó adjacente for maior que a distância do nó atual + o peso da aresta
        setD(adjacentEdges(g, v), getD(adjacentEdges(g, u)) + w);
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
        pq = createPQ(getGraphSize(g), compareDijkstraDistance);
        prio = 10000 / getWeightDij(adjacentEdges(g, src));

    } else {  // peso é a velocidade
        pq = createPQ(getGraphSize(g), compareDijkstraSpeed);
        prio = 10000 * getWeightDij(adjacentEdges(g, src));
    }
    insertPQ(pq, getNodeInfo(g, src), adjacentEdges(g, src), prio);

    while (src != dest) {  // !isEmptyPQ(pq)
        PQInfo maxPrio = removeMaximumPQ(pq);
        Node u = getNode(g, getId(maxPrio));
        setVisited(adjacentEdges(g, u), 'b');  // marca o nó como processado

        for (void *n = getFirst(adjacentEdges(g, u)); n; n = getNext(n)) {  // percorre a lista de adjacencia do nó atual

            if (getVisited(n) == 'w') {  // se o nó adjacente não foi processado
                // Edge e = getEdge(g, getNode(g, getId(graph->adjacency[u])), j);
                Node nVert = getNode(g, getId(n));

                if (type == 0) {  // peso é a distancia
                    prio = 10000 / getWeightDij(adjacentEdges(g, src));

                } else {
                    prio = 10000 * getWeightDij(adjacentEdges(g, src));
                }

                relaxDijkstra(g, u, getNode(g, getId(n)), w);  // Compara e atribui os pesos das arestas
                insertPQ(pq, getNodeInfo(g, nVert), adjacentEdges(g, getNode(g, getId(n))), prio);
            }
        }

        PQInfo *info = getMaximumPQ(pq);
        src = getNode(g, getId(info));
    }
}
