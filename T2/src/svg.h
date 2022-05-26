#include "libs.h"
#include "tree.h"

#ifndef SVG_H
#define SVG_H

/*
* Criação e elaborção de um arquivo no formato svg, desenhando formas como
* retângulos, círculos, linhas e textos no mesmo.
*/

// As funções tem nome autoexplicativo. Apenas desenham no svg a forma designada.

void writeSvg(char *bsdSvg, Tree my_tree);
// Deve receber as estruturas que armazenam as formas lidas no geo, o aqruivo svg adequado
// e a informação se existe ou não um arquivo de consulta qry.

void postOrderSVG(Node root, FILE *svg);
// Deve receber a raiz da árvore e o aqr svg 
// Percorre todos os elementos e vai delegando funções corretas
// para extrair dados dos nós e, consequentemente, escrever no svg

void drawCircle(FILE *svg, Info circ);
// Recebe o arquivo svg e o Info círculo
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawRectangle(FILE *svg, Info rect);
// Recebe o arquivo svg e o Info retângulo
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawLine(FILE *svg, Info linha);
// Recebe o arquivo svg e o Info linha
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawText(FILE *svg, Info txt);
// Recebe o arquivo svg, o Info texto e a informção se é um texto pós qry ou não
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

FILE *createSvg(char *bsdSvg);
// Consiste na criação da saída padrão do projeto, um arquivo .svg.
// Deve receber um diretório de saída e cria o arquivo .svg com nome adequado

void killSvg(FILE *svg);
// Encerra o arquivo svg adequadamente.

#endif