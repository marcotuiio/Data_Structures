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

int compareKeys(Chave ch1, Chave ch2) {
    if (!strcmp(getNomeVertex(ch1), getNomeVertex(ch2))) {
        return 1;  // se os nomes forem iguais, retorna 1
    }
    return 0;
}

Node *fullDijkstra(Digraph g, double w, Node src, Node dest, int type) {
    if (src == -1) {
        printf("Source node not found\n");
        return NULL;
    }
    if (dest == -1) {
        printf("Destination node not found\n");
        return NULL;
    }

    Node *path = calloc(1, sizeof(Node) * getGraphSize(g));
    initDijkstra(g, src);

    PQueue *pq = createPQ(getGraphSize(g), compareKeys);
    int prio = 0;

    // printf("Inserting node %d with priority %d, Lista %p\n", src, prio, adjacentEdges(g, src));
    insertPQ(pq, getNodeInfo(g, src), &src, prio);
    
    while (!isEmptyPQ(pq)) {  // !isEmptyPQ(pq)
        PQInfo maxPrio = removeMaximumPQ(pq);
        Node u = *(Node *)(maxPrio);
        setVisited(adjacentEdges(g, u), 'b');  // marca o nó como processado

        for (Edge e = getFirst(adjacentEdges(g, u)); e; e = getNext(e)) {  // percorre a lista de adjacencia do nó atual
            Lista n = adjacentEdges(g, getToNode(g, e));
            if (getVisited(n) == 'w') {  // se o nó adjacente não foi processado
                Node nVert = getNode(g, getId(n));

                if (type == 0) {  // peso é a distancia
                    prio = 10000 / getCMPEdge(getEdgeInfo(g, e));

                } else {
                    prio = 10000 * getVMEdge(getEdgeInfo(g, e));
                }

                relaxDijkstra(g, u, getNode(g, getId(n)), w);  // Compara e atribui os pesos das arestas
                printf("1 - Inserting node %d with priority %d, Lista %p\n", nVert, prio, n);
                Node aux = getNode(g, getId(n));
                insertPQ(pq, getNodeInfo(g, nVert), &aux, prio);
            }
        }
    }
    return path;
}
