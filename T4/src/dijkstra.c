#include "dijkstra.h"

void initDijkstra(Digraph g, int start, PQueue pq) {
    for (Node i = 0; i < getGraphSize(g); i++) {        // para todos os vertices
        setWeightDij(adjacentEdges(g, i), DOUBLE_MAX);  // marca a distância como infinito
        insertPQ(pq, getNodeInfo(g, i), &i, -1);                            // insere na fila de prioridade
    }
    setWeightDij(adjacentEdges(g, start), 0.0);  // marca a distância do nó inicial como 0
    setPrioPQ(pq, getNodeInfo(g, start), 0.0);                   // atualiza a prioridade do nó inicial
}

void relaxDijkstra(Digraph g, Node u, Node v, double w, int prio, PQueue pq) {        // u é o nó atual, v é o nó adjacente, w é o peso da aresta
    if (getWeightDij(adjacentEdges(g, v)) > getWeightDij(adjacentEdges(g, u)) + w) {  // se a distância do nó adjacente for maior que a distância do nó atual + o peso da aresta
        setWeightDij(adjacentEdges(g, v), getWeightDij(adjacentEdges(g, u)) + w);
        setPrioPQ(pq, getNodeInfo(g, v), prio);
    }
}

int compareKeys(Chave ch1, Chave ch2) {
    // printf("Comparando %s com %s\n", getNomeVertex(ch1), getNomeVertex(ch2));
    if (!strcmp(getNomeVertex(ch1), getNomeVertex(ch2))) {
        return 1;  // se os nomes forem iguais, retorna 1
    }
    return 0;
}

void calcW(Digraph g, Edge e, int type, int *prio, double *w) {
    if (type == 0) {  // peso é a distancia
        *(w) = getCMPEdge(getEdgeInfo(g, e));
        *(prio) = 10000 / *(w);

    } else {  // peso é a velocidade
        *(w) = getVMEdge(getEdgeInfo(g, e));
        *(prio) = 10000 * *(w);
    }
}

Node *fullDijkstra(Digraph g, Node src, Node dest, int type) {
    if (src == -1) {
        printf("Source node not found\n");
        return NULL;
    }
    if (dest == -1) {
        printf("Destination node not found\n");
        return NULL;
    }

    Node *path = calloc(getGraphSize(g), sizeof(Node));
    Node current = 1;

    PQueue pq = createPQ(getGraphSize(g), compareKeys);
    int prio = 0;
    double w = 0;

    initDijkstra(g, src, pq);
    // printf("Inserting node %d with priority %d, Lista %p\n", src, prio, adjacentEdges(g, src));
    // insertPQ(pq, getNodeInfo(g, src), &src, prio);
    path[0] = src;
    while (!isEmptyPQ(pq)) {
        PQInfo maxPrio = removeMaximumPQ(pq);
        // printf("Removed node %d\n", *(Node *)maxPrio);
        Node u = 0;
        if (maxPrio) {
            u = *(Node *)(maxPrio);
            printf("Removed node %d\n", u);
        }

        Lista adjacentes = adjacentEdges(g, u);                   // nó adjacente
        for (Edge e = getFirst(adjacentes); e; e = getNext(e)) {  // percorre a lista de adjacencia do nó atual
            if (getEnabled(e)) {
                Node v = getToAresta(e);  // nó adjacente

                calcW(g, e, type, &prio, &w);
                printf("Relaxing node %d with prio %d\n", v, prio);
                path[current] = v;
                current++;
                relaxDijkstra(g, u, v, prio, w, pq);  // Compara e atribui os pesos das arestas
                // printf("1 - Inserting node %d with priority %d\n", v, prio);
                // insertPQ(pq, getNodeInfo(g, v), &v, prio);
            }
        }
    }
    killPQ(pq);

    // for (int i = 0; i < current; i++) {
    //     printf("%d ", path[i]);
    // }
    // printf("Caminho: src %d dest %d\n", path[0], path[current - 1]);

    if (path[current - 1] != dest) {
        free(path);
        return NULL;
    }
    return path;
}