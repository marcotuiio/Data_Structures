#include "libs.h"

#ifndef LIST_H
#define LIST_H

/*
 * Uma lista  ́e uma coleção ordenada de itens em que seus elementos podem
 * ser acessados através de sua posição (tipo Posic). Uma lista sem nenhum
 * elemento (comprimento 0)  ́e denominada lista vazia.
 */

Lista criaListaAux();
void insereAux(Lista l, Node n);
void removeCell(Lista l, Node n);
void *getFirstAux(Lista l);
void *getNextAux(void *cell);
Node getValueAux(void *cell);
void freeListaAux(Lista l);
// Funções auxiliares para lidar com lista auxiliares envolvendo os grafo 

Lista criaLista();  // createList
// Cria e retorna uma lista vazia;

void setId(Lista l, char *id);
// seta o nome do nó

char *getId(Lista l);
// Retorna o nome do node

void setTD(Lista l, int td);
// adiciona o tempo de descoberta

int getTD(Lista l);
// retorna o tempo de descoberta

void setTF(Lista l, int tf);
// adiciona o tempo de finalização

int getTF(Lista l);
// retorna o tempo de finalização

void setD(Lista l, int d);
// adiciona a distância

int getD(Lista l);
// retorna a distância

void setWeightDij(Lista l, double weightDij);
// adiciona o peso do algoritmo de Dijkstra

double getWeightDij(Lista l);
// retorna o peso do algoritmo de Dijkstra

void printList(Lista l);
// * Percorre a lista e exibe o valor de cada célula armazenada

Edge encontraAresta(Lista l, Node from, Node to);
// * n deve indicar um elemento existente em L.
// * retorna o valor do item da lista indicado por n.

Edge insereFim(Lista l, InfoEdge n, Node from, Node to);  // insert
// * Insere o item n no final da lista L. O comprimento da
// lista  ́e acrescido de 1 elemento.

Edge insereInicio(Lista l, void* n);
// * Insere o item n no inicio da lista L. O comprimento da
// lista  ́e acrescido de 1 elemento.

Edge insereDepois(Lista l, void* n, void* x);  // insertAfter
// * n deve indicar um elemento existente em L.
// * insere o item x na posição imediatamente posterior ao
// item indicado por n. O comprimento da lista  ́e acrescido de 1 elemento.

void removeAresta(Lista l, void* n);  // remove
// * n deve indicar um elemento existente em L.
// * remove o elemento da lista indicado por n. O
// comprimento da lista  ́e diminu ́ıdo de 1 elemento. O indicador n deixa de
// indicar um elemento válido de L.

void setVisited(Lista l, char b);
// * seta o valor de visited para b

char getVisited(Lista l);
// * retorna o valor de visited

void setEnabled(Edge e, bool b);
// * Ativa ou desativa a aresta

bool getEnabled(Edge e);
// * Retorna o valor do enabled da aresta

Node getFromAresta(Edge e);
// * Retorna o nó de origem da aresta

Node getToAresta(Edge e);
// * Retorna o nó de destino da aresta

Edge getFirst(Lista l);
// * retorna o indicador do primeiro elemento de L. Se
// length(L)=0, retorna NULL.

Edge getLast(Lista l);
// * retorna o indicador do último elemento de L. Se
// length(L)=0, retorna NULL.

Edge getNext(Edge at);
// * at deve indicar um elemento existente em L.
// * retorna o indicador do elemento de L seguinte ao elemento
// indicado por at. Se at for o  ́ultimo elemento da lista, retorna NULL.

Edge getPrevious(Edge at);
// * at deve indicar um elemento existente em L.
// * retorna o indicador do elemento de L anterior ao elemento
// indicado por at. Se at for o primeiro elemento da lista, retorna NULL.

void setInfoFromVertex(Lista l, InfoNode info);
// * Atribui ao no' "node" a informacao "info"

InfoNode getInfoFromVertex(Lista l);
// * Retorna informacao associada ao no' node.

void setInfoFromEdge(Edge e, InfoEdge info);
// * Atribui a aresta "e" a informacao "info"

InfoEdge getInfoFromEdge(Edge e);
// * Retorna informacao associada a aresta "e"

void freeEdgeInfo(Edge e);

void getLenght(Lista l);
// * exibe a quantidade de elementos em L

void freeAdjList(Lista l);
// * libera a lista de nós adjacentes sem remover a informação associada

void freeList(Lista l);
// * recebe uma lista e remove todos seus elementos.

#endif