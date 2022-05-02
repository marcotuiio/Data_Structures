#include "libs.h"

#ifndef LINE_H
#define LINE_H

typedef void* Line1;

/*
 * Linha é uma forma geometrica básica, com propriedades
 * como x inicial, y inicial, x final, y final e sua cor. Pode 
 * ser desenhado no formato de svg, possuindo assim um x e y no plano
*/

Line1 criaLinha();
//cria uma nova linha para svg

Item buildLine(FILE *arq, Line1 l, char *infos, char *eptr);
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
//altera a cor da linha

void setlineX(Line1 l, double dx);
//translada em X a coordenada x1

void setlineY(Line1 l, double dy, int n);
//translada em DY vezes N a coordenada y1

void setlineFinalX(Line1 l, double dx);
//translada em X a coordenada x2

void setlineFinalY(Line1 l, double dy, int n);
//translada em DY vezes N a coordenada y2

#endif