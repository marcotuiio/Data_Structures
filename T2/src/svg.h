#include "libs.h"
#include "tree.h"

#ifndef SVG_H
#define SVG_H

/*
* Criação e elaborção de um arquivo no formato svg, desenhando formas como
* retângulos, círculos, linhas e textos no mesmo.
*/

// As funções tem nome autoexplicativo. Apenas desenham no svg a forma designada.

void writeSvg(char *bsdSvg);
// Deve receber as estruturas que armazenam as formas lidas no geo, o aqruivo svg adequado
// e a informação se existe ou não um arquivo de consulta qry.

void drawCircle(FILE *svg);
// Recebe o arquivo svg e o Info círculo
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawRectangle(FILE *svg);
// Recebe o arquivo svg e o Info retângulo
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawLine(FILE *svg);
// Recebe o arquivo svg e o Info linha
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawText(FILE *svg);
// Recebe o arquivo svg, o Info texto e a informção se é um texto pós qry ou não
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

FILE *createSvg(char *bsdSvg);
// Consiste na criação da saída padrão do projeto, um arquivo .svg.
// Deve receber um diretório de saída e cria o arquivo .svg com nome adequado

void killSvg(FILE *svg);
// Encerra o arquivo svg adequadamente.

#endif