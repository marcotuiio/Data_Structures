#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#ifndef GEO_H
#define GEO_H

/*
 * Leitura de arquivos com extensão .geo e tratamento dos dados para montar figuras
 * como retângulos, círculos, linhas e textos.
*/

void buildGeometricForms(FILE *arq, char *svgoutput, FILE *qry, int existe);
// Deve receber um arquivo .geo e um diretorio para criar o arquivo de saída
// Pode receber um arquivo .qry, caso ele exista.
// Após essa função, todas as informações do geo ja foram lidas e suas respectivas
// figuras já foram corretamente montadas e armazenadas.

FILE *createTxt(char *output);
// Caso exista um arquivo de consulta .qry, deve receber um diretório de 
// saída e cria o arquivo .txt de histórico com nome adequado

FILE *createSvg(char *svg_path);
// Consiste na criação da saída padrão do projeto, um arquivo .svg.
// Deve receber um diretório de saída e cria o arquivo .svg com nome adequado

void killSvg(FILE *svg);
// Encerra o arquivo svg adequadamente.

#endif
