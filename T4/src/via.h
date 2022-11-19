#include "libs.h"

#ifndef VIA_H
#define VIA_H

Digraph readVia(char *bedVia);
// Deve receber um diretório (arq.via concatenado com o bed), para criação do .via

void defineSentido(Digraph g, Node from, Node to, char *sentido);
// Deve receber um grafo, um nó de origem e um nó de destino, para definir o sentido da via

FILE *openVia(char *bedVia);
// Deve receber o diretório do arquivo .via a ser criado

#endif