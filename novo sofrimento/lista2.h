#ifndef LISTA2_H
#define LISTA2_H

//Lista são estruturas de dados alocadas dinamicamente na qual 
//escoho a posição onde removerei ou adicionarei um elemento

typedef void *Lista;
typedef void *Item;

Lista criaLista();
//Criação de uma lista;

void printList(Lista l);
//Imprime os elementos a medida que eles são removidos

void insereInicio(Lista l, Item n);
//insere um elemento no começo da lista 

void insereDepois(Lista l, Item n, Item x);
//insere um elemento depois de um determinado elemento anterior
//n = elemento da lista anterior ao novo
//x = novo elemento da lista

void removeCelula(Lista l, Item n);
//remove um elemento e libera a memória

#endif