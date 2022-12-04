#include "list.h"

typedef struct StListEdge {
    InfoEdge valueEdge;
    struct StListEdge *next;
    struct StListEdge *prev;
    Node from, to;
    bool enabled;
} StListEdge;

typedef struct StListVertex {
    InfoNode valueNode;
    int td, tf, d;  // tempo de descoberta, tempo de finalização e distância
    double weightDij;
    char visitedType;  // 'w' = white, 'g' = gray, 'b' = black
    char id[40];
    StListEdge *inicio;
    StListEdge *fim;
} StListVertex;

typedef struct StCellAux {
    Node value;
    struct StCellAux *next;
    struct StCellAux *prev;
} StCellAux;

typedef struct StListAux {
    StCellAux *inicio;
    StCellAux *fim;
} StListAux;

Lista criaListaAux() {
    StListAux *lista = calloc(1, sizeof(StListAux));
    return lista;
}

void insereAux(Lista l, Node n) {
    StListAux *lista = l;
    StCellAux *novaCelula = calloc(1, sizeof(StCellAux));
    novaCelula->value = n;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    if (lista->fim) {  // fim <-> nova --
        novaCelula->prev = lista->fim;
        novaCelula->prev->next = novaCelula;
        lista->fim = novaCelula;
    } else {  // lista vazia
        lista->fim = novaCelula;
        lista->inicio = novaCelula;
    }
    // printf("Inseriu %d, inicio: %d, fim: %d\n", n, lista->inicio->value, lista->fim->value);
}

void removeCell(Lista l, Node n) {
    StListAux *aux = l;
    StCellAux *lista = aux->inicio;
    StCellAux *celulaARemover = NULL;

    // Buscando a celula com valor desejado
    while (lista) {
        if (lista->next->value == n) {  // se n inteiro ou char
            celulaARemover = lista;
        }
        lista = lista->next;
    }

    if (!celulaARemover) {
        // printf("ELEMENTO INEXISTENTE NA LISTA\n");
        return;
    }

    if (aux->inicio == celulaARemover && aux->fim == celulaARemover) {
        aux->inicio = NULL;
        aux->fim = NULL;

    } else if (aux->inicio == celulaARemover) {  // celula a remover -> slkkefd
        aux->inicio = celulaARemover->next;
        celulaARemover->next->prev = NULL;

    } else if (aux->fim == celulaARemover) {  // vfbvff -> celula a remover
        aux->fim = celulaARemover->prev;
        celulaARemover->prev->next = NULL;

    } else {  // ant -> remove -> next
        celulaARemover->prev->next = celulaARemover->next;
        if (celulaARemover->next) {
            celulaARemover->next->prev = celulaARemover->prev;
        }
    }

    free(celulaARemover);
}

void *getFirstAux(Lista l) {
    StListAux *aux = l;
    return aux->inicio;
}

void *getNextAux(void *cell) {
    StCellAux *celula = cell;
    return celula->next;
}

Node getValueAux(void *cell) {
    StCellAux *celula = cell;
    return celula->value;
}

void freeListaAux(Lista l) {
    StListAux *lista = l;
    StCellAux *celula = lista->inicio;
    StCellAux *aux;

    while (celula) {
        aux = celula;
        celula = celula->next;
        free(aux);
    }
    free(lista);
}

Lista criaLista() {
    StListVertex *novaLista = calloc(1, sizeof(StListVertex));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;
    return novaLista;
}

void setId(Lista l, char *id) {
    StListVertex *lista = l;
    strcpy(lista->id, id);
}

char *getId(Lista l) {
    StListVertex *lista = l;
    if (!lista) {
        return NULL;
    }
    return lista->id;
}

void setTD(Lista l, int td) {
    StListVertex *lista = l;
    lista->td = td;
}

int getTD(Lista l) {
    StListVertex *lista = l;
    if (lista->td == 0) {
        return -1;
    }
    return lista->td;
}

void setTF(Lista l, int tf) {
    StListVertex *lista = l;
    lista->tf = tf;
}

int getTF(Lista l) {
    StListVertex *lista = l;
    return lista->tf;
}

void setD(Lista l, int d) {
    StListVertex *lista = l;
    lista->d = d;
}

int getD(Lista l) {
    StListVertex *lista = l;
    return lista->d;
}

void setWeightDij(Lista l, double weightDij) {
    StListVertex *lista = l;
    lista->weightDij = weightDij;
}

double getWeightDij(Lista l) {
    StListVertex *lista = l;
    return lista->weightDij;
}

void printList(Lista l) {
    StListVertex *aux = l;
    StListEdge *temporary = aux->inicio;

    while (temporary) {
        printf("%p ", temporary->valueEdge);
        temporary = temporary->next;
    }
    free(temporary);
}

Edge encontraAresta(Lista l, Node from, Node to) {
    StListVertex *aux = l;
    StListEdge *edge = aux->inicio;
    StListEdge *result = NULL;
    while (edge) {
        if (edge->to == to && edge->from == from) {
            result = edge;
            // printf("Aresta encontrada: %d -> %d\n", result->from, result->to);
            return result;
        }
        edge = edge->next;
    }
    return NULL;
}

Edge insereFim(Lista l, InfoEdge n, Node from, Node to) {
    StListVertex *lista = l;

    // Cria celula
    StListEdge *novaCelula = calloc(1, sizeof(StListEdge));
    novaCelula->valueEdge = n;  // n pode ser int, char etc, recebido com void pointer
    novaCelula->next = NULL;
    novaCelula->prev = NULL;
    novaCelula->enabled = true;
    novaCelula->from = from;
    novaCelula->to = to;

    if (lista->fim) {  // fim <-> nova --
        novaCelula->prev = lista->fim;
        novaCelula->prev->next = novaCelula;
        lista->fim = novaCelula;
    } else {  // lista vazia
        lista->fim = novaCelula;
        lista->inicio = novaCelula;
    }
    return novaCelula;
}

Edge insereInicio(Lista l, void *n) {
    StListVertex *lista = l;

    // Cria celula
    StListEdge *novaCelula = calloc(1, sizeof(StListEdge));
    novaCelula->valueEdge = n;  // n pode ser int, char etc, recebido com void pointer
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    if (lista->inicio) {
        novaCelula->next = lista->inicio;  // nova <-> primeira
        novaCelula->next->prev = novaCelula;
        lista->inicio = novaCelula;
    } else {  //(Lista vazia)
        lista->fim = novaCelula;
        lista->inicio = novaCelula;  //(inicio)nova(fim)
    }
    return novaCelula;
}

Edge insereDepois(Lista l, void *n, void *x) {
    StListVertex *aux = l;
    StListEdge *lista = aux->inicio;
    StListEdge *celulaAnterior;

    // Buscando a celula com valor n desejado
    while (lista) {
        if (lista->valueEdge == n) {
            celulaAnterior = lista;
            break;
        }
        lista = lista->next;
    }

    // Criando celula com valor x desejado
    StListEdge *novaCelula = calloc(1, sizeof(StListEdge));
    novaCelula->valueEdge = x;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    novaCelula->next = celulaAnterior->next;  // ant -> nova -> aux

    if (novaCelula->next) {  // ant -> new <- next
        novaCelula->next->prev = novaCelula;
    } else if (celulaAnterior == aux->fim) {
        aux->fim = novaCelula;  // ant <-> new -> fim
    }
    novaCelula->prev = celulaAnterior;
    celulaAnterior->next = novaCelula;
    return novaCelula;
}

void removeAresta(Lista l, void *n) {
    StListVertex *aux = l;
    StListEdge *lista = aux->inicio;
    StListEdge *celulaARemover = NULL;

    // Buscando a celula com valor desejado

    while (lista) {
        if (lista->next == n) {  // se n inteiro ou char
            celulaARemover = lista;
        }
        lista = lista->next;
    }

    if (!celulaARemover) {
        // printf("ELEMENTO INEXISTENTE NA LISTA\n");
        return;
    }

    if (aux->inicio == celulaARemover && aux->fim == celulaARemover) {
        aux->inicio = NULL;
        aux->fim = NULL;

    } else if (aux->inicio == celulaARemover) {  // celula a remover -> slkkefd
        aux->inicio = celulaARemover->next;
        celulaARemover->next->prev = NULL;

    } else if (aux->fim == celulaARemover) {  // vfbvff -> celula a remover
        aux->fim = celulaARemover->prev;
        celulaARemover->prev->next = NULL;

    } else {  // ant -> remove -> next
        celulaARemover->prev->next = celulaARemover->next;
        if (celulaARemover->next) {
            celulaARemover->next->prev = celulaARemover->prev;
        }
    }

    free(celulaARemover->valueEdge);
    free(celulaARemover);
}

void setVisited(Lista l, char b) {
    StListVertex *lista = l;
    lista->visitedType = b;
}

char getVisited(Lista l) {
    StListVertex *lista = l;
    if (!lista) {
        return '0';
    }
    return lista->visitedType;
}

void setEnabled(Edge e, bool b) {
    StListEdge *aux = e;
    aux->enabled = b;
}

bool getEnabled(Edge e) {
    StListEdge *aux = e;
    return aux->enabled;
}

Node getFromAresta(Edge e) {
    StListEdge *aux = e;
    return aux->from;
}

Node getToAresta(Edge e) {
    StListEdge *aux = e;
    return aux->to;
}

Edge getFirst(Lista l) {
    StListVertex *lista = l;
    return lista->inicio;
}

Edge getLast(Lista l) {
    StListVertex *lista = l;
    return lista->fim;
}

Edge getNext(Edge at) {
    StListEdge *node = at;
    return node->next;
}

Edge getPrevious(Edge at) {
    StListEdge *node = at;
    return node->prev;
}

void setInfoFromVertex(Lista l, InfoNode info) {
    StListVertex *list = l;
    list->valueNode = info;
}

InfoNode getInfoFromVertex(Lista l) {
    StListVertex *list = l;
    return list->valueNode;
}

void setInfoFromEdge(Edge e, InfoEdge info) {
    StListEdge *edge = e;
    edge->valueEdge = info;
}

InfoEdge getInfoFromEdge(Edge e) {
    StListEdge *edge = e;
    return edge->valueEdge;
}

void freeEdgeInfo(Edge e) {
    StListEdge *edge = e;
    free(edge->valueEdge);
}

void getLenght(Lista l) {
    StListVertex *lista = l;
    StListEdge *aux = lista->inicio;
    int contador = 0;

    while (aux) {
        contador++;
        aux = aux->next;
    }
    printf("\nO tamanho da lista é de %d elementos\n", contador);
}

void freeAdjList(Lista l) {
    StListVertex *lista = l;
    if (!lista->inicio) {
        return;
    }

    StListEdge *head = lista->inicio;
    StListEdge *tmp;

    while (head != NULL) {
        tmp = head;
        head = tmp->next;
        free(tmp);
    }
}

void freeList(Lista l) {
    StListVertex *lista = l;
    if (!lista->inicio) {
        return;
    }

    StListEdge *head = lista->inicio;
    StListEdge *tmp;

    while (head != NULL) {
        tmp = head;
        head = tmp->next;

        if (tmp->valueEdge) {
            free(tmp->valueEdge);
        }
        free(tmp);
    }
}
