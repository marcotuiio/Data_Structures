#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include "list.h"

typedef void* Line1;

/*
 * Linha é uma forma geometrica básica, com propriedades
 * como x inicial, y inicial, x final, y final e sua cor. Pode 
 * ser desenhado no formato de svg, possuindo assim um x e y no plano
*/

Line1 criaLinha();
//cria uma nova linha para svg

Item buildLine(FILE *arq, Line1 l, char *infos[], char *eptr);
//realiza leitura e extração dos dados da linha no .geo

int getLineID(Line1 l);
//retorna o id de determinada linha

double getLineX(Line1 l);
//retorna a coordenada x inicial de determinada linha no svg

double getLineY(Line1 l);
//retorna a coordenada y inicial de determinada linha no svg

double getLineFINALX(Line1 l);
//retorna a coordenada x final de determinada linha no svg

double getLineFINALY(Line1 l);
//retorna a coordenada y final de determinada linha no svg

char *getLineCOLOR(Line1 l);
//retorna a cor de determinada linha no svg

void setlineCOLOR(Line1 l, char *new_color);
//altera a cor 

void setlineX(Line1 l, double dx);
//translada em x

void setlineY(Line1 l, double dy);
//translada em y

#endif