#include "list.h"

struct nodeL {
    int value;
    struct nodeL *next;
    struct nodeL *prev;
};
typedef struct nodeL celulaL;

struct ptrL {
    celulaL *inicio;
    celulaL *fim;
};
typedef struct ptrL ImpList;

Lista criaLista() {
    ImpList *novaLista = calloc(1, sizeof(ImpList));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;

    return novaLista;
}

void printList(Lista l) {
    ImpList *aux = l;  // celulaL *temporary = (celulaL*) l
    celulaL *temporary = aux->inicio;

    while (temporary) {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

int encontraCelula(Lista from, int to) {
    ImpList *aux = from;
    celulaL *lista = aux->inicio;
    celulaL *result = NULL;

    while (lista) {
        if (lista->value == to) {
            result = lista;
            return result->value;
        }
        lista = lista->next;
    }
    if (!result) {
        printf("VALUE NOT FOUND");
        return -999;
    }
    return -999;
}

void insereFim(Lista l, int n) {
    ImpList *lista = l;

    // Cria celula
    celulaL *novaCelula = calloc(1, sizeof(celulaL));

    novaCelula->value = n;  // n pode ser int, char etc, recebido com void pointer
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    if (lista->fim != NULL) {  // fim <-> nova --
        novaCelula->prev = lista->fim;
        novaCelula->prev->next = novaCelula;
        lista->fim = novaCelula;
    } else {  // lista vazia
        lista->fim = novaCelula;
        lista->inicio = novaCelula;
    }
}

void insereInicio(Lista l, int n) {
    ImpList *lista = l;

    // Cria celula
    celulaL *novaCelula = calloc(1, sizeof(celulaL));

    novaCelula->value = n;  // n pode ser int, char etc, recebido com void pointer
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    if (lista->inicio != NULL) {
        novaCelula->next = lista->inicio;  // nova <-> primeira
        novaCelula->next->prev = novaCelula;
        lista->inicio = novaCelula;
    } else {  //(Lista vazia)
        lista->fim = novaCelula;
        lista->inicio = novaCelula;  //(inicio)nova(fim)
    }
}

void insereDepois(Lista l, int n, int x) {
    ImpList *aux = l;
    celulaL *lista = aux->inicio;
    celulaL *celulaAnterior;

    // Buscando a celula com valor n desejado
    while (lista != NULL) {
        if (lista->value == n) {
            celulaAnterior = lista;
            break;
        }
        lista = lista->next;
    }

    // Criando celula com valor x desejado
    celulaL *novaCelula = calloc(1, sizeof(celulaL));

    novaCelula->value = x;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    novaCelula->next = celulaAnterior->next;  // ant -> nova -> aux

    if (novaCelula->next != NULL) {  // ant -> new <- next
        novaCelula->next->prev = novaCelula;
    } else if (celulaAnterior == aux->fim) {
        aux->fim = novaCelula;  // ant <-> new -> fim
    }
    novaCelula->prev = celulaAnterior;
    celulaAnterior->next = novaCelula;
}

void removeCelula(Lista from, int to) {
    ImpList *aux = from;
    celulaL *lista = aux->inicio;
    celulaL *celulaARemover = NULL;
    // Buscando a celula com valor desejado

    while (lista) {
        if (lista->value == to) {  // se n inteiro ou char
            celulaARemover = lista;
        }
        lista = lista->next;
    }

    if (celulaARemover == NULL) {
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
        if (celulaARemover->next != NULL) {
            celulaARemover->next->prev = celulaARemover->prev;
        }
    }

    free(celulaARemover);
}

Cell getFirst(Lista l) {
    ImpList *lista = l;
    celulaL *aux = lista->inicio;

    return aux;
}

Cell getLast(Lista l) {
    ImpList *lista = l;
    celulaL *aux = lista->fim;

    return aux;
}

Cell getNext(Lista l, Cell at) {
    celulaL *node = at;

    return node->next;
}

Cell getPrevious(Lista l, Cell at) {
    celulaL *node = at;

    return node->prev;
}

int getInfo(Cell x) {
    celulaL *node = x;

    return node->value;
}

void getLenght(Lista l) {
    ImpList *lista = l;
    celulaL *aux = lista->inicio;
    int contador = 0;

    while (aux) {
        contador++;
        aux = aux->next;
    }
    printf("\nO tamanho da lista é de %d elementos\n", contador);
}

void freeList(Lista l) {
    ImpList *lista = l;
    if (!lista->inicio) {
        return;
    }
    celulaL *head = lista->inicio;
    celulaL *tmp;

    while (head) {
        tmp = head;
        head = tmp->next;
        free(tmp);
    }
}
