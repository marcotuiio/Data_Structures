#include "libs.h"

#ifndef CIRCLE_H
#define CIRCLE_H

/*
* Círculo é uma figura geométrica básica, com propriedades
* como raio, cor de borda e de preenchimento. Pode ser desenhado
* no formato de svg, possuindo assim um x e y no plano
*/

Info criaCirc();
//cria um novo círculo para svg

void buildCircle(FILE *geo, Info c, Lista my_list);
//realiza leitura e extração dos dados do círculo no .geo

int getCircID(Info c);
//retorna o id de determinado círculo

double getCircX(Info c);
//retorna a coordenada x de determinado círculo no svg

double getCircY(Info c);
//retorna a coordenada y de determinado círculo no svg

double getCircRADIUS(Info c);
//retorna o raio de determinado círculo

char *getCircFILL(Info c);
//retorna a cor de preenchimento de determinado círculo no svg

char *getcircEDGE(Info c);
//retorna a cor de borda de determinado círculo no svg

void setcircFILL(Info c, char *new_corp);
//altera a cor de preenchimento

void setcircEDGE(Info c, char *new_corb);
//altera a cor da borda

void setcircX(Info c, double dx);
//transalada a coordenada x

void setcircY(Info c, double dy, int n);
//translada em DY vezes N a coordenada y

#endif