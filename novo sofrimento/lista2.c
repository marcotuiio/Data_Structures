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

    novaLista = malloc(sizeof(ImpList));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;

    return novaLista;     
}

void printList(Lista l){
    ImpList *aux = (ImpList*) l;
    celulaL *temporary = aux->inicio;

    while (temporary != NULL){
        printf("%p - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

void insereInicio(Lista l, Item n){
    ImpList *lista = (ImpList*) l;

    //Cria celula
    celulaL *novaCelula = malloc(sizeof(celulaL*));

    novaCelula->value = n;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    if (lista->inicio != NULL){
        novaCelula->prev = NULL;  //nova -> inico -> next
        novaCelula->next->prev = novaCelula;
        lista->inicio = novaCelula;
    }else{  //(Lista vazia)
        lista->fim = novaCelula;
        lista->inicio = novaCelula;  //(inicio)nova(fim) 
        novaCelula->prev = NULL; 
        novaCelula->next = NULL;
    }
    
}

void insereDepois(Lista l, Item n, Item x){
    celulaL *lista = (celulaL*) l;
    ImpList *aux = (ImpList*) l;
    celulaL *celulaAnterior;

    //Buscando a celula com valor n desejado
    while (lista != NULL){
        if (lista->value == n){
            celulaAnterior = lista;
            break;
        }
        lista = lista->next;
    }

    //Criando celula com valor x desejado
    celulaL *novaCelula = (celulaL*) malloc(sizeof(celulaL));

    novaCelula->value = x;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    novaCelula->next = celulaAnterior->next;

    if (novaCelula->next != NULL){ //ant -> new <- next
        novaCelula->next->prev = novaCelula;
    }else if (celulaAnterior == aux->fim){
        aux->fim = novaCelula;  //ant -> new -> fim
    }
    novaCelula->prev = celulaAnterior;
    celulaAnterior->next = novaCelula;
}

void removeCelula(Lista l, Item n){
    celulaL *lista = (celulaL*) l;
    ImpList *aux = (ImpList*) l;
    celulaL *celulaARemover;

    //Buscando a celula com valor desejado
    while (lista != NULL){
        if (lista->value == malloc(sizeof(n))){
            celulaARemover = lista;
            break;
        }
        lista = lista->next;
    }
     
    if (aux->inicio == celulaARemover){
        aux->inicio = celulaARemover->next;
        celulaARemover->next->prev = NULL;
        
    }else if (aux->fim == celulaARemover){
        aux->fim = celulaARemover->prev;
        celulaARemover->prev->next = NULL;

    }else{
        celulaARemover->prev->next = celulaARemover->next;
        if (celulaARemover->next != NULL){
            celulaARemover->next->prev = celulaARemover->prev;
        }  //ant -> remove -> next
    }      

    free(celulaARemover);

}
