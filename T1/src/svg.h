#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include "text.h"
#include "list.h"
#include "system.h"

/*
 * Criação e elaborção de um arquivo no formato svg, desenhando formas como 
 * retângulos, círculos, linhas e textos no mesmo.
 */

// As funções tem nome autoexplicativo. Apenas desenham no svg a forma designada.

FILE *createSvg(char *svg_path);

void killSvg(FILE * svg);

FILE *createTxt(char *output);

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha, char *diroutput, FILE *qry, int existe);

void drawCircle(FILE * svg, Item circ);

void drawRectangle(FILE * svg, Item rect);

void drawLine(FILE * svg, Item linha);

void drawText(FILE * svg, Item txt);

#endif