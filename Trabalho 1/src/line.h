#ifndef LINE_H
#define LINE_H

#include "list.h"

typedef void* Line1;

Line1 criaLinha();

Item buildLine(FILE *arq, Line1 l, char infos[], char *eptr);

int getLineID(Line1 l);

float getLineX(Line1 l);

float getLineY(Line1 l);

float getLineFINALX(Line1 l);

float getLineFINALY(Line1 l);

char getLineCOLOR(Line1 l);

#endif