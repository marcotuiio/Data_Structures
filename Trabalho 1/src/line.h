#ifndef LINE_H
#define LINE_H

#include "list.h"

typedef void* Line1;

Line1 criaLinha();
//cria uma nova linha para svg

Item buildLine(FILE *arq, Line1 l, char infos[], char *eptr);
//realiza leitura e extração dos dados da linha no .geo

int getLineID(Line1 l);
//retorna o id de determinada linha

float getLineX(Line1 l);
//retorna a coordenada x inicial de determinada linha no svg

float getLineY(Line1 l);
//retorna a coordenada y inicial de determinada linha no svg

float getLineFINALX(Line1 l);
//retorna a coordenada x final de determinada linha no svg

float getLineFINALY(Line1 l);
//retorna a coordenada y final de determinada linha no svg

char getLineCOLOR(Line1 l);
//retorna a cor de determinada linha no svg

#endif