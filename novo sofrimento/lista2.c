#include <stdio.h>
#include <stdlib.h>

#include "lista2.h"

struct nodeL{
    Item value;
    struct nodeL *next;
    struct nodeL *prev;
};
typedef struct nodeL celulaL;

struct ptrL{
    celulaL *inicio;
    celulaL *fim;
};
typedef struct ptrL ImpList;

Lista criaLista(){
    ImpList *novaLista;

    novaLista = (ImpList)* malloc(sizeof(ImpList));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;

    return novaLista;
}

void printList(Lista l){
    celulaL *temporary = l->inicio;

    while (temporary != NULL){
        printf("%p - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

void insereInicio(Lista l, Item n){
    Lista *lista = (Lista*) l;

    //Cria celula
    celulaL *novaCelula = (celulaL *) malloc(sizeof(celulaL));

    novaCelula->value = n;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    l->inicio = novaCelula;

    if (l->inicio != NULL){
        novaCelula->prev = NULL  //nova -> inico -> next
        novaCelula->next = l->inicio;
        l->inicio = novaCelula;
    }else{
        l->fim = novaCelula;
        l->inicio = novaCelula;  //(inicio)nova(fim) 
        novaCelula->prev = NULL; 
        novaCelula->next = NULL;
    }
    
}

void *insereDepois(Lista l, Item n, Item x){
    Lista *lista = (Lista*) l;
    celulaL *celulaAnterior;

    //Buscando a celula com valor desejado
    while (lista->next != NULL){
        if (lista->value == n){
            celulaAnterior = lista;
            break;
        }
        lista = lista->next;
    }

    //Cria celula
    celulaL *novaCelula = (celulaL *) malloc(sizeof(celulaL));

    novaCelula->value = x;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    novaCelula->next = celulaAnterior->next;

    if (novaCelula->next != NULL){ //ant -> new <- next
        novaCelula->next->prev = novaCelula;
    }else if (celulaAnterior == l->fim){
        l->fim = novaCelula;  //ant -> new -> fim
    }
    novaCelula->prev = celulaAnterior;
    celulaAnterior->next = novaCelula;
}

void removeCelula(Lista l, Item n){
    Lista *lista = (Lista*) l;
    celulaL celulaARemover;

    //Buscando a celula com valor desejado
    while (lista->next != NULL){
        if (lista->value == malloc(sizeof(n))){
            celulaARemover = lista;
            break;
        }
        lista = lista->next;
    }
     
    if (l->inicio == celulaARemover){
        l->inicio = celulaARemover->next;
        celulaARemover->next->prev = NULL;
        
    }else if (l->fim == celulaARemover){
        l->fim = celulaARemover->prev;
        celulaARemover->prev->next = NULL;

    }else{
        celulaARemover->prev->next = celulaARemover->next;
        if (celulaARemover->next != NULL){
            celulaARemover->next->prev = celulaARemover->prev;
        }  //ant -> remove -> next
    }      

    free(celulaARemover);

}