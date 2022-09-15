#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

#define QUEUE_EMPTY INT_MIN

// struct nodeF{
//     int value;
//     struct nodeF *next;
// };
// typedef struct nodeF celula;

// struct control{
//     celulaF *head;
//     celulaF *tail;
// };
// typedef struct control fila;

void init(fila *minhafila){
    minhafila->head = NULL;
    minhafila->tail = NULL; 
}

bool enfila(fila *minhafila, int n){
    //crio uma nova celula
    celulaF *novaCelula = malloc(sizeof(celulaF));
    if (novaCelula == NULL){
        return false;
    }
    novaCelula->value = n;
    novaCelula->next = NULL;
    //se existe um rabo, ligo esse rabo na nova celula
    if (minhafila->tail != NULL){
        minhafila->tail->next = novaCelula;
    }
    minhafila->tail = novaCelula;
    //conferir se o começo da fila ainda faz sentido
    if (minhafila->head == NULL){
        minhafila->head = novaCelula;
    }
    return true;
}

int desenfila(fila *minhafila){
    //conferir se a fila está ou não vazia
    if (minhafila->head == NULL){
        return QUEUE_EMPTY;
    }
    //salvo o começo da fila
    celulaF *tmp = minhafila->head;
    //salvo o valor a ser removido
    int result = tmp->value;
    //removo o valor
    minhafila->head = minhafila->head->next;
    if (minhafila->head == NULL){
        minhafila->tail = NULL;
    }
    free(tmp);
    return result;
}

void printFila(fila *minhafila){
    int q;
    printf("\n");
    while ((q = desenfila(minhafila)) != QUEUE_EMPTY){
        printf("q = %d\n", q);
    }
}

