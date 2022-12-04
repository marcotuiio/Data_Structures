#include "via.h"

typedef struct va {

    char rua[60];
    char ldir[30];
    char lesq[30];
    double cmp;
    double vm;
    char sentido[3];

} ViaAresta;

typedef struct vv {

    char id[15];
    double x, y;

} ViaVertice;

InfoEdge criaArestaVia(char* rua, char* ldir, char* lesq, double cmp, double vm) {

    ViaAresta* via = malloc(sizeof(ViaAresta));
    strcpy(via->rua, rua);
    strcpy(via->ldir, ldir);
    strcpy(via->lesq, lesq);
    via->cmp = cmp;
    via->vm = vm;

    return via;
}

InfoNode criaVerticeVia(char* id, double x, double y) {

    ViaVertice* via = malloc(sizeof(ViaVertice));
    strcpy(via->id, id);
    via->x = x;
    via->y = y;

    return via;
}

double getXvia(InfoNode V) {

    ViaVertice* vertice = (ViaVertice*) V;
    return vertice->x;
}

double getYvia(InfoNode V) {

    ViaVertice* vertice = (ViaVertice*) V;
    return vertice->y;
}

void setSentido(InfoEdge A, char* sentido) {

    ViaAresta* aresta = (ViaAresta*) A;
    strcpy(aresta->sentido, sentido);
}