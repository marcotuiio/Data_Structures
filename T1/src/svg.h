#include "libs.h"

#ifndef SVG_H
#define SVG_H

/*
 * Criação e elaborção de um arquivo no formato svg, desenhando formas como
 * retângulos, círculos, linhas e textos no mesmo.
 */

// As funções tem nome autoexplicativo. Apenas desenham no svg a forma designada.

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha, FILE *svg, int existe);
// Deve receber as estruturas que armazenam as formas lidas no geo, o aqruivo svg adequado
// e a informação se existe ou não um arquivo de consulta qry.

void drawCircle(FILE *svg, Item circ);
// Recebe o arquivo svg e o Item círculo
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawRectangle(FILE *svg, Item rect);
// Recebe o arquivo svg e o Item retângulo
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawLine(FILE *svg, Item linha);
// Recebe o arquivo svg e o Item linha
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

void drawText(FILE *svg, Item txt, int e);
// Recebe o arquivo svg, o Item texto e a informção se é um texto pós qry ou não
// Extrai os dados tais quais encontrados no geo e imprimi os mesmo no formato SVG

#endif