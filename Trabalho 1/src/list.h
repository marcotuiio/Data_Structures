#ifndef LIST_H
#define LIST_H

/*
 *Lista são estruturas de dados alocadas dinamicamente na qual 
 *escoho a posição onde removerei ou adicionarei um elemento
*/

typedef void* Lista;
typedef void* Item;

Lista criaLista(); //createList
//Cria e retorna uma lista vazia;

void printList(Lista l);
//Imprime os elementos a medida que eles são removidos

void insereFim(Lista l, Item n); //insert
//insere um elemento sempre no final da lista 

void insereInicio(Lista l, Item n); 
//insere um elemento no começo da lista 

void insereDepois(Lista l, Item n, Item x); //insertAfter
//insere um elemento depois de um determinado elemento anterior
//(utiliza função get, procurando o elemento)
//n = elemento da lista anterior ao novo 
//x = novo elemento da lista

void removeCelula(Lista l, Item n); //remove
//remove um elemento de valor n e libera a memória
//(utiliza função get, procurando o elemento)

Lista getFirst(Lista l);
//exibe o primeiro elemento da lista

void getLast(Lista l);
//exibe o ultimo elemento da lista

void getLenght(Lista l);
//exibe a quantidade de elementos na lista

Lista encontraCelula(Lista l, Item n);
//dada a lista, percorre a mesma buscando o item n desejado 

Lista getNext(Lista l, Item at);
//dada a lista e um elemento de referência, retorna o valor seguinte ao mesmo

#endif