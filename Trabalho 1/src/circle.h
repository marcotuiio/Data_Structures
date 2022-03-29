#ifndef CIRCLE_H
#define CIRCLE_H

#include "list.h"

typedef void* Circle1;

Circle1 criaCirc();

Item buildCircle(FILE *arq, Circle1 circ, char infos[], char *eptr);

int getCircID(Circle1 r);

float getCircX(Circle1 r);

float getCircY(Circle1 r);

float getCircRADIUS(Circle1 r);

char getCircFILL(Circle1 r);

char getcircEDGE(Circle1 r);

#endif