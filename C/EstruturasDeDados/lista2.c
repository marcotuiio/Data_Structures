#include <stdio.h>
#include <stdlib.h>

#include "lista2.h"

// struct node {
//     int value;
//     struct nodeL *next;
//     struct nodeL *prev;
// };
// typedef struct nodeL celulaL;

void printList(celulaL *head){
    celulaL *temporary = head;

    while (temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

celulaL *criaCelula(int n){
    celulaL *result = malloc(sizeof(celulaL));
    result->value = n;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

celulaL *insereInicio(celulaL **head, celulaL *novaCelula){
    novaCelula->next = *head;
    if (*head != NULL){
        (*head)->prev = novaCelula;
    }
    *head = novaCelula;
    novaCelula->prev = NULL;
    return novaCelula;
}

celulaL *encontraCelula(celulaL *head, int n){
    celulaL *list = head;
    while (list != NULL){
        if (list->value == n){
            return list;
        }
        list = list->next;
    }
    return NULL;
}

void insereDepois(celulaL *celulaAnterior, celulaL *novaCelula){
    novaCelula->next = celulaAnterior->next;
    if (novaCelula->next != NULL){
        novaCelula->next->prev = novaCelula;
    }
    novaCelula->prev = celulaAnterior;
    celulaAnterior->next = novaCelula;
}

void removeCelula(celulaL **head, celulaL *celulaARemover){
    if (*head == celulaARemover){
        *head = celulaARemover->next;
        if (*head != NULL){
            (*head)->prev = NULL;
        }
    } else {
        celulaARemover->prev->next = celulaARemover->next;
        if (celulaARemover->next != NULL){
            celulaARemover->next->prev = celulaARemover->prev;
        }  
    }
    free(celulaARemover);
    // celulaARemover->next = NULL;
    // celulaARemover->prev = NULL;
    return;
}