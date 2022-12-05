#include "dijkstra.h"

#define DISTANCIA 0
#define VELOCIDADE 1

void initDijkstra(Digraph g, Node* distancia, Node* pai, Node src) {
    for (int i = 0; i < getGraphSize(g); i++) {
        distancia[i] = INT_MAX;
        pai[i] = -1;
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

void relaxDijkstra(Digraph g, Node* distancia, Node* pai, Node u, Node v, double w) {
    Lista adj = adjacentEdges(g, u);
    Edge aresta = getFirst(adj);

    while (aresta && getToNode(g, aresta) != v) {
        aresta = getNext(aresta);
    }

    if (aresta) {
        if (distancia[v] > distancia[u] + w) {
            distancia[v] = distancia[u] + w;
            pai[v] = u;
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

void fullDijkstra(Digraph g, Node src, Node dest, int type, FILE* svg, FILE* txt, char* cmr, char* cmc) {
    if (src == -1) {
        printf("Source node not found\n");
        return;
    }
    if (dest == -1) {
        printf("Destination node not found\n");
        return;
    }

    Node* distancia = calloc(getGraphSize(g), sizeof(Node));
    int* caminho = calloc(getGraphSize(g), sizeof(int));
    int pai[getGraphSize(g)];
    int menor;
    Node aux;
    PQueue pq = createPQ(getGraphSize(g), compareKeys);
    bool aberto[getGraphSize(g)];
    Edge aresta = NULL;

    initDijkstra(g, distancia, pai, src);

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
                relaxDijkstra(g, distancia, pai, menor, getToAresta(aresta), w);
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
        aux = pai[aux];
    }

    double x1, y1, x2, y2;
    for (i = 0; i < getGraphSize(g) - 1; i++) {
        if (caminho[i] == -1)
            continue;
        if (type == VELOCIDADE) {
            x1 = getXVertex(getNodeInfo(g, caminho[i]));
            y1 = getYVertex(getNodeInfo(g, caminho[i]));
            x2 = getXVertex(getNodeInfo(g, caminho[i + 1]));
            y2 = getYVertex(getNodeInfo(g, caminho[i + 1]));
            fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke:%s; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n", x1, y1, x2, y2, cmr, x1, y1, x2, y2);

        } else if (type == DISTANCIA) {
            x1 = getXVertex(getNodeInfo(g, caminho[i])) - 4;
            y1 = getYVertex(getNodeInfo(g, caminho[i])) - 4;
            x2 = getXVertex(getNodeInfo(g, caminho[i + 1])) - 4;
            y2 = getYVertex(getNodeInfo(g, caminho[i + 1])) - 4;
            fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke:%s; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n", x1, y1, x2, y2, cmc, x1, y1, x2, y2);
        }
    }

    if (type == 1) {
        fprintf(txt, "\nCaminho mais curto:");
    } else {
        fprintf(txt, "\nCaminho mais rapido:");
    }

    char direcaoAnterior[30] = "direcaoAnterior";
    char direcaoAtual[30] = "direcaoAtual";

    for (i = 0; i < getGraphSize(g) - 1; i++) {
        if (caminho[i] == -1) {
            continue;
        }
        aresta = getEdge(g, caminho[i], caminho[i + 1]);
        InfoEdge info = getEdgeInfo(g, aresta);
        x1 = getXVertex(getNodeInfo(g, caminho[i]));
        y1 = getYVertex(getNodeInfo(g, caminho[i]));
        x2 = getXVertex(getNodeInfo(g, caminho[i + 1]));
        y2 = getYVertex(getNodeInfo(g, caminho[i + 1]));

        if (x1 < x2) {
            strcpy(direcaoAtual, "Oeste");

        } else if (x1 > x2) {
            strcpy(direcaoAtual, "Leste");

        } else if (y1 < y2) {
            strcpy(direcaoAtual, "Norte");

        } else if (y2 > y2) {
            strcpy(direcaoAtual, "Sul");
        }

        if (!strcmp(direcaoAnterior, "direcaoAnterior")) {
            fprintf(txt, "\nSiga na direcao %s na Rua %s", direcaoAtual, getNomeEdge(info));

        } else if (strcmp(direcaoAtual, direcaoAnterior) == 1) {
            fprintf(txt, " ate o cruzamento com a Rua %s.\n", getNomeEdge(info));
            fprintf(txt, "Siga na direcao %s na Rua %s", direcaoAtual, getNomeEdge(info));
        }

        strcpy(direcaoAnterior, direcaoAtual);
    }

    if (!strcmp(direcaoAnterior, "direcaoAnterior")) {
        fprintf(txt, "NÃO FOI POSSÍVEL ENCONTRAR UM CAMINHO ENTRE OS ENDEREÇOS\n");
        fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:1; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"6s\" repeatCount=\"indefinite\" /> </circle>\n", x1, y1, x2, y2, x1, y1, x2, y2);

    } else {
        fprintf(txt, ". Chegou em seu destino.\n");
    }

    free(distancia);
    free(caminho);
    killPQ(pq);
}