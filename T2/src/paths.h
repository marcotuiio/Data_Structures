#include "libs.h"

#ifndef PATHS_H
#define PATHS_H

/*
 * Recebe os dados e atribui para suas determinados variáveis 
 * definindo os diretorios e nomes, alem das confirmações de leitura
*/

Paths createAllPaths();
// Aloca memória para todas as possiveis variaveis de entrada

char* prepareDir(char* dir);
// Tratamento dos diretorios, para garantir que sejam válidos

void prepareDoc(char* asread, char* onlyname);
// Tratamentos dos nomes, para evitar falhas de concatenação

void setBed(Paths path, char* bed);
// Atribui o diretório de entrada em sua devida variável

char* getBed(Paths path);
// Retorna apenas o diretório de entrada

void setBsd(Paths path, char* bsd);
// Atribui o diretório de saída em sua devida variável

char* getBsd(Paths path);
// Retorna apenas o diretório de saída

void setBedGeo(Paths path, char* bedgeo);
// Atribui o diretório de entrada concatenado com o arquivo geo
// em sua devida variável

char* getBedGeo(Paths path);
// Retorna apenas diretório de entrada concatenado com o arquivo geo 

void setGeoArq(Paths path, char* geoarq);
// Atribui o arquivo geo em sua devida variável (nome com .geo)

char* getGeoArq(Paths path);
// Retorna apenas o arquivo geo

void setGeoName(Paths path, char* geoname);
// Atribui o nome arquivo geo em sua devida variável (apenas nome sem .geo)

char* getGeoName(Paths path);
// Retorna apenas o nome do arquivo geo

void setBedQry(Paths path, char* bedqry);
// Atribui o diretório de entrada concatenado com o arquivo qry 

char* getBedQry(Paths path);
// Retorna apenas o diretório de entrada concatenado com o arquivo qry 

void setQryArq(Paths path, char* qryarq);
// Atribui o arquivo qry em sua devida variável 
// (possiveis pastas / nome com .qry)

char* getQryArq(Paths path);
// Retorna apenas arquivo qry com as possiveis pastas 

void setQryName(Paths path, char* qryname);
// Atribui o nome do arquivo qry em sua devida variável
// (apenas nome sem .qry nem pastas anteriores)

char* getQryName(Paths path);
// Retorna apenas o nome do arquivo qry em sua devida variável

void setBsdGeoSvg(Paths path, char* bsdgeosvg);
// Atribui o nome do arquivo geo concatenado com o diretório de
// saída e a terminação .svg em sua devida variável

char* getBsdGeoSvg(Paths path);
// Retorna apenas o diretório de saída com geo e .svg

void setBsdGeoQrySvg(Paths path, char* bsdgeoqrysvg);
// Atribui o nome do arquivo geo concatenado com o nome 
// do arquivo qry, o diretório de saída e a terminação
// .svg em sua devida variável

char* getBsdGeoQrySvg(Paths path);
// Retorna apenas o diretório de saída com geo, qry e .svg

void setBsdGeoQryTxt(Paths path, char* bsdgeoqrytxt);
// Atribui o nome do arquivo geo concatenado com o nome 
// do arquivo qry, o diretório de saída e a terminação
// .txt em sua devida variável

char* getBsdGeoQryTxt(Paths path);
// Retorna apenas o diretório de saída com geo, qry e .txt

void freePaths(Paths path);
// Realiza liberação de memória de todos os parâmetros de entrada
// utilizados durante o projeto

#endif
