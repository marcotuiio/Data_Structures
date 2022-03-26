#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "fila.h"
#include "lista2.h"
//#include "pilha.h"
//#include "fila_circular.h"

void main() {
    // printf("INT_MIN = %d\n\n", QUEUE_EMPTY);
    // printf("--- FILA ---\n");
    // fila q1, q2, q3;

    // init(&q1);
    // init(&q2);
    // init(&q3);

    // enfila(&q1, 34);
    // enfila(&q2, 75); 
    // enfila(&q2, 11);
    // enfila(&q2, 292); 
    // enfila(&q3, 19);
    // enfila(&q1, 999);
    
    // printFila(&q2);
    // printFila(&q1);

    printf("\n--- LISTA DUPLAMENTE ENCADEADA ---\n");
    Lista lista = criaLista();

    for (int i=0; i<25; i++){
        insereInicio(lista, &i);
    }

    int a=3, b=8, c=1;
    insereDepois(lista, &a, &b);

    printList(lista);

    removeCelula(lista, &c);
    //removeCelula(&head, head);

    printList(lista);

    // printf("\n--- PILHA ---\n");
    // pilha s1 = NULL;
    // pilha s2 = NULL;
    // pilha s3 = NULL;

    // empilha(&s1, 34); 
    // empilha(&s2, 75);
    // empilha(&s2, 11);
    // empilha(&s2, 292);
    // empilha(&s3, 19);
    // empilha(&s1, 999);
    
    // printPilha(&s2);
    // printPilha(&s1);

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