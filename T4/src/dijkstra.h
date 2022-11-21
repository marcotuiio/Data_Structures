#include "digraph.h"
#include "list.h"
#include "infos.h"
#include "libs.h"
#include "priority_queue.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

/*
    O algoritmo de Dijkstra solucionará o problema de encontrar o menor caminho
    em um grafo ponderado, a partir de um vértice inicial, até todos os outros
    vértices do grafo. O algoritmo de Dijkstra é um algoritmo guloso, que
    utiliza uma fila de prioridades para encontrar o menor caminho.
*/

int compareDijkstraSpeed(Chave ch1, Chave ch2);
// Retorna 1 se ch1 > ch2, 0 se ch1 = ch2 e -1 se ch1 < ch2

int compareDijkstraDistance(Chave ch1, Chave ch2);
// Retorna 1 se ch1 > ch2, 0 se ch1 = ch2 e -1 se ch1 < ch2

void fullDijkstra(Digraph g, double w, Node src, Node dest, ComparaChavesPQ comparator, int type);
// Executa o algoritmo de Dijkstra para encontrar o caminho mais curto entre src e dest

#endif