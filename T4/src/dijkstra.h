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

int compareKeys(Chave ch1, Chave ch2);
// Compara duas chaves de acordo com o alguma espeficicação previamente definida

void fullDijkstra(Digraph g, Node src, Node dest, int type, FILE* svg, FILE* txt, char *cmr, char *cmc);
// Executa o algoritmo de Dijkstra para encontrar o caminho mais curto entre src e dest

#endif