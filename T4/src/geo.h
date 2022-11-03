#include "libs.h"
#include "paths.h"

#ifndef GEO_H
#define GEO_H

void readGeo(char *bedGeo, Rb t);
// Deve receber um diretório (arq.geo concatenado com o bed), para criação do .geo
// Após essa função, todas as informações do geo ja foram lidas e suas respectivas
// figuras já foram corretamente montadas e armazenadas.

FILE *openGeo(char *bedGeo);
// Deve receber o diretório do arquivo .geo a ser criado
// Retorna o arquivo .geo criado para leitura

int countCQ(char *bedGeo);
// Deve receber o diretório do arquivo .geo a ser criado
// Retorna a quantidade de cq's no arquivo .geo

#endif