#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "list.h"

typedef void* Rectangle1;

Rectangle1 criaRec();

Item buildRectangle(FILE *arq, Rectangle1 rec, char infos[], char *eptr);

int getRectID(Rectangle1 r);

float getRectX(Rectangle1 r);

float getRectY(Rectangle1 r);

float getRectWIDTH(Rectangle1 r);

float getRectHEIGHT(Rectangle1 r);

char getRectFILL(Rectangle1 r);

char getRectEDGE(Rectangle1 r);

#endif