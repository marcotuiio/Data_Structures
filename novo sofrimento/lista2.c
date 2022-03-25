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
    //printf("--- INICIO CRIA LISTA ---\n");
    ImpList *novaLista = calloc(1, sizeof(ImpList*));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;

    return novaLista;     
}

void printList(Lista l){
    ImpList *aux = (ImpList*) l;  //celulaL *temporary = (celulaL*) l
    celulaL *temporary = aux->inicio;  

    while (temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

void insereInicio(Lista l, Item n){
    //printf("--- INICIO INSERE INICIO ---\n");
    ImpList *lista = (ImpList*) l;

    //Cria celula
    celulaL *novaCelula = calloc(1, sizeof(celulaL*));

    novaCelula->value = n;  //n pode ser int, char etc, recebido com void pointer
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    if (lista->inicio != NULL){
        novaCelula->next = lista->inicio;  //nova -> primeira
        novaCelula->next->prev = novaCelula;
        lista->inicio = novaCelula;
    }else{  //(Lista vazia)
        lista->fim = novaCelula;
        lista->inicio = novaCelula;  //(inicio)nova(fim) 
    }
    
}

void insereDepois(Lista l, Item n, Item x){
    //printf("--- INICIO INSERE DEPOIS ---\n");
    ImpList *aux = (ImpList*) l;
    celulaL *lista = aux->inicio;
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

    novaCelula->value = (int) x;
    novaCelula->next = NULL;
    novaCelula->prev = NULL;

    novaCelula->next = celulaAnterior->next;  //ant -> nova -> aux

    if (novaCelula->next != NULL){ //ant -> new <- next
        novaCelula->next->prev = novaCelula;
    }else if (celulaAnterior == aux->fim){
        aux->fim = novaCelula;  //ant <-> new -> fim
    }
    novaCelula->prev = celulaAnterior;
    celulaAnterior->next = novaCelula;
}

void removeCelula(Lista l, Item n){
    //printf("--- INICIO REMOVE CELULA ---\n");
    ImpList *aux = (ImpList*) l;
    celulaL *lista = aux->inicio;
    celulaL *celulaARemover = NULL;

    //Buscando a celula com valor desejado
    while (lista != NULL){
        if (lista->value == n){
            celulaARemover = lista;
            break;
        }
        lista = lista->next;
    }

    if (celulaARemover == NULL){
        printf("ELEMENTO INEXISTENTE NA LISTA\n");
        return;
    }
     
    if (aux->inicio == celulaARemover){   //celula a remover -> slkkefd
        aux->inicio = celulaARemover->next;
        celulaARemover->next->prev = NULL;
        
    }else if (aux->fim == celulaARemover){  //vfbvff -> celula a remover 
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
