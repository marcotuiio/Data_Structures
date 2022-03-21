#ifndef LISTA2_H
#define LISTA2_H

//Lista são estruturas de dados alocadas dinamicamente na qual 
//escoho a posição onde removerei ou adicionarei um elemento

//Descobrir como remover struct da .h
struct nodeL {
    int value;
    struct nodeL *next;
    struct nodeL *prev;
};
typedef struct nodeL celulaL;

void printList(celulaL *head);
//Imprime os elementos a medida que eles são removidos

celulaL *criaCelula(int n);
//cria uma nova célula

celulaL *insereInicio(celulaL **head, celulaL *novaCelula);
//insere um elemento no começo da lista 

celulaL *encontraCelula(celulaL *head, int n);
//encontra o elemento n na lista

void insereDepois(celulaL *celulaAnterior, celulaL *novaCelula);
//insere um elemento depois de um determinado elemento anterior

void removeCelula(celulaL **head, celulaL *celulaARemover);
//remove um elemento e libera a memória

#endif