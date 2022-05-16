#include "libs.h"

#ifndef LIST_H
#define LIST_H

/*
 * Uma lista  ́e uma coleção ordenada de itens em que seus elementos podem
 * ser acessados através de sua posição (tipo Posic). Uma lista sem nenhum
 * elemento (comprimento 0)  ́e denominada lista vazia.
 */

Lista createList();  // createList
// Cria e retorna uma lista vazia;

void printList(Lista l);
// * Percorre a lista e exibe o valor de cada célula armazenada

void insereFim(Lista l, Info n, double x, double y);  // insert
// * Insere o Info n no final da lista L. O comprimento da
// lista  ́e acrescido de 1 elemento.

void insereInicio(Lista l, Info n);
// * Insere o Info n no inicio da lista L. O comprimento da
// lista  ́e acrescido de 1 elemento.

void insereDepois(Lista l, Info n, Info x);  // insertAfter
// * n deve indicar um elemento existente em L.
// * insere o Info x na posição imediatamente posterior ao
// Info indicado por n. O comprimento da lista  ́e acrescido de 1 elemento.

void removeCelula(Lista l, Info n, int id, char* tipo);  // remove
// * n deve indicar um elemento existente em L.
// * remove o elemento da lista indicado por n. O
// comprimento da lista  ́e diminu ́ıdo de 1 elemento. O indicador n deixa de
// indicar um elemento válido de L.

Cell getFirst(Lista l);
// * retorna o indicador do primeiro elemento de L. Se
// length(L)=0, retorna NULL.

Cell getLast(Lista l);
// * retorna o indicador do último elemento de L. Se
// length(L)=0, retorna NULL.

Cell getNext(Cell at);
// * at deve indicar um elemento existente em L.
// * retorna o indicador do elemento de L seguinte ao elemento
// indicado por at. Se at for o  ́ultimo elemento da lista, retorna NULL.

Cell getPrevious(Cell at);
// * at deve indicar um elemento existente em L.
// * retorna o indicador do elemento de L anterior ao elemento
// indicado por at. Se at for o primeiro elemento da lista, retorna NULL.

Info getInfo(Cell x);
// * retorna o valor armazenado na célula de X. Se
// length(L)=0, retorna NULL.

int getLenght(Lista l);
// * exibe a quantidade de elementos em L

Info encontraCelula(Lista l, Info n);  // get
// * n deve indicar um elemento existente em L.
// * retorna o valor do Info da lista indicado por n.

// double* toArray(Lista l);
// double getXL(Cell node);
// double getYL(Cell node);

void freeList(Lista l);
// * recebe uma lista e remove todos seus elementos.

#endif