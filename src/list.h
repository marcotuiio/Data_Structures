#ifndef lista_h
#define lista_h
#include "libs.h"
#include "digraph.h" 

List criaLista();                       // cria uma lista vazia  
Edge insertAresta(List vertice, InfoEdge info, Node from, Node to);
void RemoveElemento(List L, Edge C);    // remove a célula passada de parâmetro 
Edge getInicio(List L);                 // retorna a primeira célula da lista
Edge getNext(Edge C);                   // retorna a próxima celula da célula passada de parâmetro
Edge getPrevious(Edge C);               // retorna a célula anterior à célula passada de parâmetro
Edge getLast(List L);                   // retorna a última célula da lista
InfoEdge getItem(Edge C);               // retorna o item contido na célula passada de parâmetro
void liberaLista(List lista);           // percorre toda a lista e libera todas as células e, ao fim, a lista
void setNomeVert(List vertice, char* nome);
char* getNomeVert(List vertice);
void setInfoVert(List vertice, InfoNode info);
InfoNode getInfoVert(List vertice);
Node getArestaTo(Edge E);
Node getArestaFrom(Edge E);
Edge searchEdge(List L, Node from, Node to);
void setArestaDesativada(Edge E);

#endif