#include "dijkstra.h"

void initDijkstra(Digraph g, Node* distancia, Node* parent, Node src) {
    for (int i = 0; i < getGraphSize(g); i++) {
        distancia[i] = INT_MAX;
        parent[i] = -1;
    }
    distancia[src] = 0;
}

int compareKeys(Chave ch1, Chave ch2) {
    // printf("Comparing %d and %d\n", *(Node*)ch1, *(Node*)ch2);
    if (!strcmp(getNomeVertex(ch1), getNomeVertex(ch2))) {
        return 1;  // se os nomes forem iguais, retorna 1
    }
    return 0;
}

void relaxDijkstra(Digraph g, Node* distancia, Node* parent, Node u, Node v, double w) {
    Lista adj = adjacentEdges(g, u);
    Edge aresta = getFirst(adj);

    while (aresta && getToNode(g, aresta) != v) {
        aresta = getNext(aresta);
    }

    if (aresta) {
        if (distancia[v] > distancia[u] + w) {
            distancia[v] = distancia[u] + w;
            parent[v] = u;
        }
    }
}

bool existeAberto(Digraph g, bool* aberto) {
    for (int i = 0; i < getGraphSize(g); i++) {
        if (aberto[i])
            return true;
    }
    return false;
}

int menorDistancia(Digraph g, bool* aberto, Node* distancia) {
    int i, menor = 0;

    for (i = 0; i < getGraphSize(g); i++) {
        if (aberto[i]) {
            break;
        }
    }

    if (i == getGraphSize(g)) {
        return -1;
    }

    menor = i;

    for (i = i + 1; i < getGraphSize(g); i++) {
        if (aberto[i] && distancia[menor] > distancia[i]) {
            menor = i;
        }
    }
    return menor;
}

double calcW(Digraph g, Edge e, int type) {
    double w;
    if (type == DISTANCIA) {  // peso é a distancia
        w = getCMPEdge(getEdgeInfo(g, e));

    } else if (type == VELOCIDADE) {  // peso é a velocidade
        w = getVMEdge(getEdgeInfo(g, e));
    }
    return w;
}

Node* fullDijkstra(Digraph g, Node src, Node dest, int type) {
    if (src == -1) {
        printf("Source node not found\n");
        return;
    }
    if (dest == -1) {
        printf("Destination node not found\n");
        return;
    }

    Node* distancia = calloc(getGraphSize(g), sizeof(Node));
    Node* caminho = calloc(getGraphSize(g), sizeof(Node));
    int parent[getGraphSize(g)];
    int menor;
    Node aux;
    PQueue pq = createPQ(getGraphSize(g), compareKeys);
    bool aberto[getGraphSize(g)];
    Edge aresta = NULL;

    initDijkstra(g, distancia, parent, src);

    for (int i = 0; i < getGraphSize(g); i++) {
        aberto[i] = true;
    }

    while (existeAberto(g, aberto)) {
        menor = menorDistancia(g, aberto, distancia);
        aberto[menor] = false;

        aresta = getFirst(adjacentEdges(g, menor));
        while (aresta) {
            if (getEnabled(aresta)) {
                double w = calcW(g, aresta, type);
                relaxDijkstra(g, distancia, parent, menor, getToAresta(aresta), w);
            }
            aresta = getNext(aresta);    
        }
    }

    aux = dest;
    int i;
    for (i = 0; i < getGraphSize(g); i++) {
        caminho[i] = -1;
    }

    i = getGraphSize(g) - 1;
    while (aux != -1 && i >= 0) {
        caminho[i] = aux;
        i--;
        aux = parent[aux];
    }

    free(distancia);
    killPQ(pq);
    return caminho;
}