#include "libs.h"

#ifndef SVG_H
#define SVG_H

/*
 * Criação e elaborção de um arquivo no formato svg, desenhando formas como
 * retângulos, círculos, linhas e textos no mesmo.
 */

// As funções tem nome autoexplicativo. Apenas desenham no svg a forma designada.

void writeSvg(FILE *svg, Rb t, Digraph g);
// Deve receber as estruturas que armazenam as formas lidas no geo, o aqruivo svg adequado
// e a informação se existe ou não um arquivo de consulta qry.

void writeRb(InfoRb i, void *aux);
// Deve receber a raiz da árvore e o aqr svg
// Percorre todos os elementos e vai delegando funções corretas
// para extrair dados dos nós e, consequentemente, escrever no svg

void animatedPath(Digraph g, FILE *svg, Node *path, char *id);
// Deve receber o grafo, o arquivo svg, o vetor de nós que formam o caminho e o id do caminho
// Anima um circulo percorrendo o caminho no svg

FILE *createSvg(char *bsdSvg);
// Consiste na criação da saída padrão do projeto, um arquivo .svg.
// Deve receber um diretório de saída e cria o arquivo .svg com nome adequado

void killSvg(FILE *svg);
// Encerra o arquivo svg adequadamente.

#endif