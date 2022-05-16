#include "libs.h"

#ifndef LINE_H
#define LINE_H

/*
* Linha é uma forma geometrica básica, com propriedades
* como x inicial, y inicial, x final, y final e sua cor. Pode 
* ser desenhado no formato de svg, possuindo assim um x e y no plano
*/

Info criaLinha();
//cria uma nova linha para svg

void buildLine(FILE *geo, Info l);
//realiza leitura e extração dos dados da linha no .geo

int getLineID(Info l);
//retorna o id de determinada linha

double getLineX(Info l);
//retorna a coordenada x inicial de determinada linha no svg

double getLineY(Info l);
//retorna a coordenada y inicial de determinada linha no svg

double getLineFINALX(Info l);
//retorna a coordenada x final de determinada linha no svg

double getLineFINALY(Info l);
//retorna a coordenada y final de determinada linha no svg

char *getLineCOLOR(Info l);
//retorna a cor de determinada linha no svg

void setlineCOLOR(Info l, char *new_color);
//altera a cor da linha

void setlineX(Info l, double dx);
//translada em X a coordenada x1

void setlineY(Info l, double dy, int n);
//translada em DY vezes N a coordenada y1

void setlineFinalX(Info l, double dx);
//translada em X a coordenada x2

void setlineFinalY(Info l, double dy, int n);
//translada em DY vezes N a coordenada y2

double getLineLenght(Info l);
// dada um determinada Linha l, calcula seu comprimento e o retorna
// no formato de double

#endif