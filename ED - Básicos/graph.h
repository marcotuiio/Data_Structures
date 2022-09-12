#include "libs.h"

#ifndef GRAPH_H
#define GRAPH_H

// Grafo por matriz de adjacências

void* createGraph(int v);
// Cria um grafo com v vértices

void freeGraph(void* g);
// Libera a memória alocada para o grafo

void printGraph(void* g);
// Imprime o grafo no formato dot

bool addEdge(void* g, int from, int to);
// Adiciona uma aresta entre os vértices from e to

bool hasEdge(void* g, int from, int to);
// Verifica se existe uma aresta entre os vértices from e to

#endif