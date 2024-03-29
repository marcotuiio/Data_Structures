#include "/home/marcotuiio/Data_Structures/1UTIL/libs.h"

#ifndef LIST_H
#define LIST_H

/*
 * Uma lista  ́e uma coleção ordenada de itens em que seus elementos podem
 * ser acessados através de sua posição (tipo Posic). Uma lista sem nenhum
 * elemento (comprimento 0)  ́e denominada lista vazia.
 */

typedef void* Lista;
typedef void* Cell;
typedef void* Item;

Lista criaLista();  // createList
// Cria e retorna uma lista vazia;

void printList(Lista l);
// * Percorre a lista e exibe o valor de cada célula armazenada

void insereFim(Lista l, int n);  // insert
// * Insere o item n no final da lista L. O comprimento da
// lista  ́e acrescido de 1 elemento.

void insereInicio(Lista l, int n);
// * Insere o item n no inicio da lista L. O comprimento da
// lista  ́e acrescido de 1 elemento.

void insereDepois(Lista l, int n, int x);  // insertAfter
// * n deve indicar um elemento existente em L.
// * insere o item x na posição imediatamente posterior ao
// item indicado por n. O comprimento da lista  ́e acrescido de 1 elemento.

void removeCelula(Lista from, int to);  // remove
// * n deve indicar um elemento existente em L.
// * remove o elemento da lista indicado por n. O
// comprimento da lista  ́e diminu ́ıdo de 1 elemento. O indicador n deixa de
// indicar um elemento válido de L.

void setVisited(Lista l, bool b);

bool getVisited(Lista l);

Cell getFirst(Lista l);
// * retorna o indicador do primeiro elemento de L. Se
// length(L)=0, retorna NULL.

Cell getLast(Lista l);
// * retorna o indicador do último elemento de L. Se
// length(L)=0, retorna NULL.

Cell getNext(Lista l, Cell at);
// * at deve indicar um elemento existente em L.
// * retorna o indicador do elemento de L seguinte ao elemento
// indicado por at. Se at for o  ́ultimo elemento da lista, retorna NULL.

Cell getPrevious(Lista l, Cell at);
// * at deve indicar um elemento existente em L.
// * retorna o indicador do elemento de L anterior ao elemento
// indicado por at. Se at for o primeiro elemento da lista, retorna NULL.

int getInfo(Cell x);
// * retorna o valor armazenado na célula de X. Se
// length(L)=0, retorna NULL.

void getLenght(Lista l);
// * exibe a quantidade de elementos em L

int encontraCelula(Lista from, int to);  // get
// * n deve indicar um elemento existente em L.
// * retorna o valor do item da lista indicado por n.

void freeList(Lista l);
// * recebe uma lista e remove todos seus elementos.

#endif