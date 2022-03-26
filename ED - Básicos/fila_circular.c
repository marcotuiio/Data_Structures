#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "fila_circular.h"

#define QUEUE_EMPTY INT_MIN

// struct control{
//     int *values;
//     int head, tail, num_entries, size;
// };
// typedef struct control fila;

void init_circ(fila_circ *q, int max_size){
    q->size = max_size;
    q->values = malloc(sizeof(int) * q->size);    
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;
}

bool fila_vazia(fila_circ *q){
    return (q->num_entries == 0);
}

bool fila_cheia(fila_circ *q){
    return (q->num_entries == q->size);
}

void destoi_fila(fila_circ *q){
    free(q->values);
}

bool enfila_circ(fila_circ *q, int x){
    //crio uma nova celula
    if (fila_cheia(q)){
        printf("Sua fila esta cheia\n");
        return false;
    }

    q->values[q->tail] = x;
    q->num_entries++;
    q->tail = (q->tail + 1) % q->size;
    return true;
}

int desenfila_circ(fila_circ *q){
    int result;

    if (fila_vazia(q)){
        //printf("Sua fila esta vazia\n");
        return QUEUE_EMPTY;
    }

    result = q->values[q->head];
    q->head = (q->head + 1) % q->size;
    q->num_entries--;
    return result;
}

void printFila_circ(fila_circ *q){
    int cq;
    printf("\n");
    while ((cq = desenfila_circ(q)) != QUEUE_EMPTY){
        printf("q = %d\n", cq);
    }
}