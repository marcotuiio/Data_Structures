#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fila.h"
#include "lista2.h"
#include "pilha.h"

void main() {
    //printf("INT_MIN = %d\n\n", QUEUE_EMPTY);
    printf("--- FILA ---\n");
    fila q1, q2, q3;

    init(&q1);
    init(&q2);
    init(&q3);

    enfila(&q1, 34);
    enfila(&q2, 75);
    enfila(&q2, 11);
    enfila(&q2, 292);
    enfila(&q3, 19);
    enfila(&q1, 999);
    
    printFila(&q2);
    printFila(&q1);

    printf("\n--- LISTA DUPLAMENTE ENCADEADA ---\n");
    celulaL *head = NULL;
    celulaL *list;

    for (int i=0; i<25; i++){
        list = criaCelula(i);
        insereInicio(&head, list);
    }

    //list = encontraCelula(head, 9);
    printf("\nEncontrei: %d\n", list->value);

    insereDepois(encontraCelula(head, 9), criaCelula(77));

    printList(head);

    removeCelula(&head, encontraCelula(head, 1));
    //removeCelula(&head, head);

    printList(head);

    printf("\n--- PILHA ---\n");
    pilha s1 = NULL;
    pilha s2 = NULL;
    pilha s3 = NULL;

    empilha(&s1, 34);
    empilha(&s2, 75);
    empilha(&s2, 11);
    empilha(&s2, 292);
    empilha(&s3, 19);
    empilha(&s1, 999);
    
    printPilha(&s2);
    printPilha(&s1);

}