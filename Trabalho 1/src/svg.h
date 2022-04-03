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

void drawCircle(FILE * svg, Circle1 circ);

void drawRectangle(FILE * svg, Rectangle1 rect);

void drawLine(FILE * svg, Line1 linha);

void drawText(FILE * svg, Text1 txt);

#endif