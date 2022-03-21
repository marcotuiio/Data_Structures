#ifndef PILHA_H
#define PILHA_H

//Descobrir como remover struct da .h
struct node{
    int value;
    struct node *next;
};
typedef struct node celulaP;

typedef celulaP *pilha;

bool empilha(pilha *minhapilha, int n);
//empurra: coloca elementos no topo da pilha

int desempilha(pilha *minhapilha);
//tira: remove elementos que estao no topo e faz free da memoŕia que ocupavam

void printPilha(pilha *minhapilha);   
//print: remove os elementos no topo e imprime qual elemento foi retirado. repete até 
//que a pilha esteja vazia

#endif