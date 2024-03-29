#include "libs.h"

#ifndef CIRCLE_H
#define CIRCLE_H

typedef void* Circle1;

/*
 * Círculo é uma figura geométrica básica, com propriedades
 * como raio, cor de borda e de preenchimento. Pode ser desenhado
 * no formato de svg, possuindo assim um x e y no plano
*/

Circle1 criaCirc();
//cria um novo círculo para svg

Item buildCircle(FILE *arq, Circle1 circ, char *infos, char *eptr);
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

char *getCircEDGE(Circle1 c);
//retorna a cor de borda de determinado círculo no svg

void setcircFILL(Circle1 c, char *new_corp);
//altera a cor de preenchimento

void setcircEDGE(Circle1 c, char *new_corb);
//altera a cor da borda

void setcircX(Circle1 c, double dx);
//transalada a coordenada x

void setcircY(Circle1 c, double dy, int n);
//translada em DY vezes N a coordenada y

#endif