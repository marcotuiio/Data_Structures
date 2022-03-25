#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista2.h"
//#include "fila_circ.h"

void main() {

    printf("\n--- LISTA DUPLAMENTE ENCADEADA ---\n");
    Lista lista = criaLista();
    //printf("--- PASSOU DA CRIACAO DA LISTA ---\n");
    
    for (int i=0; i<9; i++){
        insereInicio(lista, i);
    }
    //printf("--- PASSOU DO INSERE INICIO ---\n");

    int a=3, b=8, c=999;
    insereDepois(lista, b, c); 
    //printf("--- PASSOU DO INSERE DEPOIS ---\n");

    printList(lista);

    removeCelula(lista, 0);
    printf("--- PASSOU DO REMOVE CELULA ---\n");

    printList(lista);

    // printf("\n--- FILA CIRCULAR---\n");
    // fila_circ cq1;

    // init_circ(&cq1, 3);

    // enfila_circ(&cq1, 34);
    // enfila_circ(&cq1, 75); 
    // enfila_circ(&cq1, 11);
    // enfila_circ(&cq1, 292); 
    // enfila_circ(&cq1, 19);
    // enfila_circ(&cq1, 999);

    // printFila_circ(&cq1);

}
