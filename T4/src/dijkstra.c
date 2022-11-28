#include "dijkstra.h"

void initDijkstra(Digraph g, int start) {
    for (Node i = 0; i < getGraphSize(g); i++) {  // para todos os vertices
        setWeightDij(adjacentEdges(g, i), DOUBLE_MAX);          // marca a distância como infinito
    }
    setWeightDij(adjacentEdges(g, start), 0.0);  // marca a distância do nó inicial como 0
}

void relaxDijkstra(Digraph g, Node u, Node v, double w) {  // u é o nó atual, v é o nó adjacente, w é o peso da aresta
    if (getWeightDij(adjacentEdges(g, v)) > getWeightDij(adjacentEdges(g, u)) + w) {  // se a distância do nó adjacente for maior que a distância do nó atual + o peso da aresta
        setWeightDij(adjacentEdges(g, v), getWeightDij(adjacentEdges(g, u)) + w);
    }
}

int compareKeys(Chave ch1, Chave ch2) {
    // printf("Comparando %s com %s\n", getNomeVertex(ch1), getNomeVertex(ch2));
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
    Node current = 0;
    initDijkstra(g, src);

    PQueue pq = createPQ(getGraphSize(g), compareKeys);
    int prio = 0;

    // printf("Inserting node %d with priority %d, Lista %p\n", src, prio, adjacentEdges(g, src));
    insertPQ(pq, getNodeInfo(g, src), &src, prio);
    
    while (!isEmptyPQ(pq)) {  // !isEmptyPQ(pq)
        PQInfo maxPrio = removeMaximumPQ(pq);
        // printf("Removed node %d\n", *(Node *)maxPrio);
        Node u;
        if (maxPrio) {
            u = *(Node *)(maxPrio);
        }
        setVisited(adjacentEdges(g, u), 'b');  // marca o nó como processado

        Lista adjacentes = adjacentEdges(g, u);  // nó adjacente
        for (Edge e = getFirst(adjacentes); e; e = getNext(e)) {  // percorre a lista de adjacencia do nó atual
            Node v = getToAresta(e);  // nó adjacente
            // Node nVert = getNode(g, getId(n));

            if (type == 0) {  // peso é a distancia
                w = getCMPEdge(getEdgeInfo(g, e));
                prio = 10000 / w;

            } else {
                w = getVMEdge(getEdgeInfo(g, e));
                prio = 10000 * w;
            }
            path[current] = v;
            current++;
            relaxDijkstra(g, u, v, w);  // Compara e atribui os pesos das arestas
            // printf("1 - Inserting node %d with priority %d\n", v, prio);
            insertPQ(pq, getNodeInfo(g, v), &v, prio);
            setVisited(adjacentEdges(g, v), 'g');  // marca o nó adjacente como processado            
        }
    }
    killPQ(pq);
    return path;
}
