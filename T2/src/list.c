#include "list.h"

struct nodeL {
    Info value;
    struct nodeL *next;
    struct nodeL *prev;
    double x, y;
};
typedef struct nodeL celulaL;

struct ptrL {
    celulaL *inicio;
    celulaL *fim;
};
typedef struct ptrL ImpList;

Lista createList() {
    // printf("--- INICIO CRIA LISTA ---\n");
    ImpList *novaLista = calloc(1, sizeof(ImpList));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;

    return novaLista;
}

void printList(Lista l) {
    ImpList *aux = (ImpList *)l;  // celulaL *temporary = (celulaL*) l
    celulaL *temporary = aux->inicio;

    while (temporary != NULL) {
        // printf("%p - ", temporary->value);
        temporary = temporary->next;
    }
    // printf("\n");
    free(temporary);
}

Info encontraCelula(Lista l, Info n) {
    ImpList *aux = (ImpList *)l;
    celulaL *lista = aux->inicio;
    celulaL *result = NULL;

    while (lista != NULL) {
        if (lista->value == n) {
            result = lista;
            // printf("Valor encontrado -> %s", result->value);
            return result;
        }
        lista = lista->next;
    }
    if (result == NULL) {
        printf("VALOR NÂO ENCONTRADO");
        exit(1);
    }
    return NULL;
}

void insereFim(Lista l, Info n, double x, double y) {
    // printf("--- INICIO INSERE FIM ---\n");
    ImpList *lista = (ImpList *)l;

    // Cria celula
    celulaL *novaCelula = calloc(1, sizeof(celulaL));

    novaCelula->value = n;  // n pode ser int, char etc, recebido com void pointer
    novaCelula->next = NULL;
    novaCelula->prev = NULL;
    novaCelula->x = x;
    novaCelula->y = y;

    if (lista->fim != NULL) {  // fim <-> nova --
        novaCelula->prev = lista->fim;
        novaCelula->prev->next = novaCelula;
        lista->fim = novaCelula;
    } else {  // lista vazia
        lista->fim = novaCelula;
        lista->inicio = novaCelula;
    }
}

void insereInicio(Lista l, Info n) {
    // printf("--- INICIO INSERE INICIO ---\n");
    ImpList *lista = (ImpList *)l;

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

void insereDepois(Lista l, Info n, Info x) {
    // printf("--- INICIO INSERE DEPOIS ---\n");
    ImpList *aux = (ImpList *)l;
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

void removeCelula(Lista l, Info n, int id, char *tipo) {
    // printf("--- INICIO REMOVE CELULA ---\n");
    ImpList *aux = (ImpList *)l;
    celulaL *lista = aux->inicio;
    celulaL *celulaARemover = NULL;
    Info info = n;

    while (lista != NULL) {
        if (lista->next == n) {  // se n inteiro ou char
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
    ImpList *lista = (ImpList *)l;
    celulaL *aux = lista->inicio;

    return aux;
}

Cell getLast(Lista l) {
    ImpList *lista = (ImpList *)l;
    celulaL *aux = lista->fim;

    return aux;
}

Cell getNext(Cell at) {
    celulaL *node = (celulaL *)at;

    return node->next;
}

Cell getPrevious(Cell at) {
    celulaL *node = (celulaL *)at;

    return node->prev;
}

Info getInfo(Cell x) {
    celulaL *node = (celulaL *)x;

    return node->value;
}

int getLenght(Lista l) {
    ImpList *lista = (ImpList *)l;
    celulaL *aux = lista->inicio;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->next;
    }
    // printf("\nO tamanho da lista é de %d elementos\n", contador);
    free(aux);
    return contador;
}

// double *toArray(Lista l) {
//     ImpList *lista = l;

//     int size = getLenght(lista);
//     double arr_x[size];
//     void* arr_infos[size];
//     double x, y;

//     for (Cell node = getFirst(lista); node; node = getNext(lista)) {
//         x = getXL(node);
        
//     }
// }

// double getXL(Cell node) {
//     celulaL *my_node = node;

//     return my_node->x;
// }

// double getYL(Cell node) {
//     celulaL *my_node = node;

//     return my_node->y;
// }

void freeList(Lista l) {
    ImpList *lista = (ImpList *)l;
    if (lista->inicio == NULL) {
        return;
    }

    celulaL *head = lista->inicio;
    celulaL *tmp;

    while (head != NULL) {
        tmp = head;
        head = tmp->next;

        free(tmp->value);
        free(tmp);
    }
}
