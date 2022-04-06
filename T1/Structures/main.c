#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista2.h"
#include "fila_circ.h"

void main() {

    printf("\n--- LISTA DUPLAMENTE ENCADEADA ---\n\n");
    Lista lista = criaLista();
    //printf("--- PASSOU DA CRIACAO DA LISTA ---\n");
    
    for (int i=0; i<9; i++){
        insereInicio(lista, i);
    }
    //printf("--- PASSOU DO INSERE INICIO ---\n");
    
    printList(lista);

    int a=3, b=8, c=999;
    insereDepois(lista, b, c); //inserir depois de b, item c
    //printf("--- PASSOU DO INSERE DEPOIS ---\n");

    printList(lista);

    removeCelula(lista, 0);
    //printf("--- PASSOU DO REMOVE CELULA ---\n");

    insereFim(lista, 69);

    printList(lista);

    encontraCelula(lista, 8);
    getFirst(lista);
    getLast(lista);

    printf("\n--- FILA CIRCULAR---\n");
    Fila_Circular fila = criaFila(3);

    for (int j=30; j< 100; j=j+17){
        enfila_circ(fila, j);
    }
    
     printFila_circ(fila);

}