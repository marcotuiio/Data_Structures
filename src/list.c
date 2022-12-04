#include "libs.h"
#include "digraph.h"
#include "list.h"

typedef struct celula {
    InfoEdge it;
    Node from, to;
    struct celula *ant;
    struct celula *prox;
    bool ativada;

} Celula; // edge

typedef struct {
    int tamanho;
    InfoNode info;
    char nome[30];
    Celula *prim, *ult;
} Lista; // vertex

List criaLista() {

    Lista *lista;
    lista = (Lista*) malloc(sizeof(Lista));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->tamanho = 0;

    return(lista);
}

Edge insertAresta(List vertice, InfoEdge info, Node from, Node to) {

    Lista* lista = (Lista*) vertice;
    Celula* novoEle = (Celula*) malloc(sizeof(Celula));

    novoEle->it = info;
    novoEle->prox = NULL;
    novoEle->from = from;
    novoEle->to = to;
    novoEle->ativada = true;

    if(lista->tamanho == 0) {

        novoEle->ant = NULL;
        lista->ult = novoEle;
        lista->prim = novoEle;

    } else {

        (lista->ult)->prox = novoEle;
        novoEle->ant = lista->ult;
        lista->ult = novoEle;
    }
    lista->tamanho++;

    return novoEle;

}

void RemoveElemento(List L, Edge C) {

    Lista* lista = (Lista*) L;
    //Celula* auxAnt = malloc(sizeof(Celula));
    Celula* celula = (Celula*) C;
    //auxAnt = celula->ant;
    Celula* auxAnt = celula->ant;

    if (celula == NULL) {
        return;
    }

    if (celula == lista->prim && celula == lista->ult) {
        lista->prim = NULL;
        lista->ult = NULL;

    } else if (celula == lista->prim) {
        lista->prim = celula->prox;
        celula->prox->ant = NULL;

    } else if (celula == lista->ult) {
        lista->ult = auxAnt;
        celula->ant->prox = NULL;

    } else {
        celula->ant->prox = celula->prox;
        celula->prox->ant = celula->ant;

    }

    free(celula);
    lista->tamanho--;
}

Edge getInicio(List L) {
    Lista* lista = (Lista*) L;
    return lista->prim;
}

Edge getNext(Edge C) {
    Celula* celula = (Celula*) C;
    return celula->prox;
}

Edge getPrevious(Edge C) {
    Celula* celula = (Celula*) C; 
    return celula->ant;
}

Edge getLast2(List L) {
    Lista* lista = (Lista*) L;
    return lista->ult;
}

Edge getLast(List L) {
    Lista* lista = (Lista*) L;
    return lista->ult;
}

InfoEdge getItem(Edge C) {
    Celula* celula = (Celula*) C;
    return celula->it;
}

void liberaLista(List lista) {
    Edge celula = getInicio(lista);
    Edge celulaRemovida;

    // percorrendo a lista e dando free em todas as células
    while (celula != NULL) {

        celulaRemovida = celula;
        celula = getNext(celula);
        free(celulaRemovida);
    }
    // depois de ter liberado todas as células, libera a lista
    free(lista);
}

void setNomeVert(List vertice, char* nome) {

    Lista* lista = (Lista*) vertice;
    strcpy(lista->nome, nome);

}

char* getNomeVert(List vertice) {

    Lista* lista = (Lista*) vertice;
    return (lista->nome);
}

void setInfoVert(List vertice, InfoNode info) {

    Lista* lista = (Lista*) vertice;
    lista->info = info;
     
}

InfoNode getInfoVert(List vertice) {

    Lista* lista = (Lista*) vertice;
    return lista->info;
}

Node getArestaTo(Edge E) {

    Celula* aresta = (Celula*) E;
    return aresta->to;
}

Node getArestaFrom(Edge E) {

    Celula* aresta = (Celula*) E;
    return aresta->from;
}

Edge searchEdge(List L, Node from, Node to) {

    Lista* lista = (Lista*) L;
    Celula* aresta = getInicio(lista);
    while (getNext(aresta) != NULL) {
        if (aresta->from == from && aresta->to == to) {
            return aresta;
        } 
    }
    return NULL;
}

void setArestaDesativada(Edge E) {

    Celula* aresta = (Celula*) E;
    aresta->ativada = false;
}