#ifndef geo_h
#define geo_h
#include "SRBtree.h"

void readingGeo(FILE* geoFile, SRbTree tree);
/*
Faz a leitura do arquivo .geo passado de parâmetro, 
cria todas as figuras contidas no .geo e
as insere na árvore.
*/

Digraph buildingVias(char* arqVia);

#endif