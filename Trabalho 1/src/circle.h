#ifndef CIRCLE_H
#define CIRCLE_H

#include "list.h"

typedef void* Circle1;

Circle1 criaCirc();

Item buildCircle(FILE *arq, Circle1 circ, char infos[], char *eptr);

int getCircID(Circle1 c);

float getCircX(Circle1 c);

float getCircY(Circle1 c);

float getCircRADIUS(Circle1 c);

char getCircFILL(Circle1 c);

char getcircEDGE(Circle1 c);

#endif