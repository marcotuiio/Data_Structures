#include "list.h"

struct nodeL {
    void *value;
    struct nodeL *next;
    struct nodeL *prev;
};
typedef struct nodeL StListNode;

struct ptrL {
    StListNode *inicio;
    StListNode *fim;
};
typedef struct ptrL StList;

Lista criaLista() {
    StList *novaLista = calloc(1, sizeof(StList));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;

    return novaLista;
}

void printList(Lista l) {
    StList *aux = l;  
    StListNode *temporary = aux->inicio;

    while (temporary) {
        printf("%p ", temporary->value);
        temporary = temporary->next;
    }
    free(temporary);
}

void *encontraCelula(Lista l, void *n) {
    StList *aux = l;
    StListNode *lista = aux->inicio;
    StListNode *result = NULL;

    while (lista) {
        if (lista->value == n) {
            result = lista;
            return result;
        }
        lista = lista->next;
    }
    if (!result) {
        printf("VALOR NÂO ENCONTRADO");
        return NULL;
    }
    return NULL;
}

void insereFim(Lista l, void *n) {
    StList *lista = l;

    // Cria celula
    StListNode *novaCelula = calloc(1, sizeof(StListNode));
    novaCelula->value = n;  // n pode ser int, char etc, recebido com void pointer
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
}

void insereInicio(Lista l, void *n) {
    StList *lista = l;

    // Cria celula
    StListNode *novaCelula = calloc(1, sizeof(StListNode));
    novaCelula->value = n;  // n pode ser int, char etc, recebido com void pointer
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
}

void insereDepois(Lista l, void *n, void *x) {
    StList *aux = l;
    StListNode *lista = aux->inicio;
    StListNode *celulaAnterior;

    // Buscando a celula com valor n desejado
    while (lista) {
        if (lista->value == n) {
            celulaAnterior = lista;
            break;
        }
        lista = lista->next;
    }

    // Criando celula com valor x desejado
    StListNode *novaCelula = calloc(1, sizeof(StListNode));
    novaCelula->value = x;
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
}

void removeCelula(Lista l, void *n, int id, char *tipo) {
    StList *aux = l;
    StListNode *lista = aux->inicio;
    StListNode *celulaARemover = NULL;

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

    free(celulaARemover);
}

void *getFirst(Lista l) {
    StList *lista = l;

    return lista->inicio;
}

void *getLast(Lista l) {
    StList *lista = l;
    return lista->fim;
}

void *getNext(Lista l, void *at) {
    StListNode *node = at;

    return node->next;
}

void *getPrevious(Lista l, void *at) {
    StListNode *node = at;

    return node->prev;
}

void *getInfo(void *x) {
    StListNode *node = x;

    return node->value;
}

void getLenght(Lista l) {
    StList *lista = l;
    StListNode *aux = lista->inicio;
    int contador = 0;

    while (aux) {
        contador++;
        aux = aux->next;
    }
    printf("\nO tamanho da lista é de %d elementos\n", contador);
}

void removeAll(Lista l) {
    StList *lista = (StList *)l;
    if (!lista->inicio) {
        return;
    }

    StListNode *head = lista->inicio;
    StListNode *tmp;

    while (head != NULL) {
        tmp = head;
        head = tmp->next;

        free(tmp->value);
        free(tmp);
    }
}
