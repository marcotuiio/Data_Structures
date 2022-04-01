#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include "text.h"
#include "list.h"
#include "system.h"

FILE *createSvg(char *svg_path);

void killSvg(FILE * svg);

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha);

void drawCircle(FILE * svg, Item circ);

void drawRectangle(FILE * svg, Item rect);

void drawLine(FILE * svg, Item linha);

void drawText(FILE * svg, Item txt);

#endif