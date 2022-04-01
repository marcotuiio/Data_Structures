#ifndef CIRCLE_H
#define CIRCLE_H

#include "list.h"

typedef void* Circle1;

Circle1 criaCirc();
//cria um novo círculo para svg

Item buildCircle(FILE *arq, Circle1 circ, char infos[], char *eptr);
//realiza leitura e extração dos dados do círculo no .geo

int getCircID(Circle1 c);
//retorna o id de determinado círculo

double getCircX(Circle1 c);
//retorna a coordenada x de determinado círculo no svg

double getCircY(Circle1 c);
//retorna a coordenada y de determinado círculo no svg

double getCircRADIUS(Circle1 c);
//retorna o raio de determinado círculo

char *getCircFILL(Circle1 c);
//retorna a cor de preenchimento de determinado círculo no svg

char *getcircEDGE(Circle1 c);
//retorna a cor de borda de determinado círculo no svg

#endif