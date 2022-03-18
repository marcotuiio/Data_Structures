#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "pilha.h"

#define STACK_EMPTY INT_MIN

// struct node{
//     int value;
//     struct node *next;
// };
// typedef struct node celulaP;

bool empilha(pilha *minhapilha, int n){
    celulaP *novaCelula = malloc(sizeof(celulaP));
    if (novaCelula == NULL)
        return false;
        
    novaCelula->value = n;
    novaCelula->next = *minhapilha;
    *minhapilha = novaCelula;
    return true;
}

int desempilha(pilha *minhapilha){
    if (*minhapilha == NULL){
        return STACK_EMPTY;
    }else{
        int result = (*minhapilha)->value;
        celulaP *tmp = *minhapilha;
        *minhapilha = (*minhapilha)->next;
        free(tmp);
        return result;
    }
}

void printPilha(pilha *minhapilha){
    int x;
    printf("\n");
    while ((x = desempilha(minhapilha)) != STACK_EMPTY){
        printf("x = %d\n", x);
    }
}