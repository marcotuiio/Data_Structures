#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "fila_circ.h"

#define QUEUE_EMPTY INT_MIN

struct queue{
    int *value;
    int head, tail, num_entries, size;
};
typedef struct queue fila_circ;

Fila_Circular criaFila(int max_size){
    //Criando nova fila circular
    fila_circ *q = calloc(1, sizeof(fila_circ*));

    q->size = max_size;
    q->value = malloc(sizeof(Item) * max_size);    
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;

    return q;
}

bool fila_vazia(Fila_Circular q){
    fila_circ *fila = (fila_circ*) q;

    return (fila->num_entries == 0);
}

bool fila_cheia(Fila_Circular q){
    //printf("--- FILA CHEIA ---\n");
    fila_circ *fila = (fila_circ*) q;

    return (fila->num_entries == fila->size);
}

void destroi_fila(Fila_Circular q){
    fila_circ *fila = (fila_circ*) q;

    free(fila->value);
}

bool enfila_circ(Fila_Circular q, Item x){
    fila_circ *fila = (fila_circ*) q;
    //Preencho uma nova celula
    if (fila_cheia(fila)){
        printf("Sua fila esta cheia\n");
        return false;
    }

    fila->value[fila->tail] = x;
    fila->num_entries++;
    fila->tail = (fila->tail + 1) % fila->size;
    printf("Inserido com sucesso\n");
    return true;
}

Item desenfila_circ(Fila_Circular q){
    fila_circ *fila = (fila_circ*) q;
    fila_circ *result = NULL;

    if (fila_vazia(fila)){
        //printf("Sua fila esta vazia\n");
        return QUEUE_EMPTY;
    }

    result = fila->value[fila->head];
    fila->head = (fila->head + 1) % fila->size;
    fila->num_entries--;
    return result;
}

void printFila_circ(Fila_Circular q){
    fila_circ *fila = (fila_circ*) q;
    
    Item cq;  //Usar 'ITEM' pois essa fila deve armazar qualquer tipo de valor
    printf("\n");
    while ((cq = desenfila_circ(fila)) != QUEUE_EMPTY){
        printf("q = %d\n", cq);
    }
}