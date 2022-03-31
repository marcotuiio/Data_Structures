#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "list.h"

typedef void* Rectangle1;

Rectangle1 criaRec();
//cria um novo retângulo para svg

Item buildRectangle(FILE *arq, Rectangle1 rec, char infos[], char *eptr);
//realiza leitura e extração dos dados do retângulo no .geo

int getRectID(Rectangle1 r);
//retorna o id de determinado retângulo

float getRectX(Rectangle1 r);
//retorna a coordenada x de determinado retângulo no svg

float getRectY(Rectangle1 r);
//retorna a coordenada y de determinado retângulo no svg

float getRectWIDTH(Rectangle1 r);
//retorna a largura de determinado retângulo no svg

float getRectHEIGHT(Rectangle1 r);
//retorna a altura de determinado retângulo no svg

char getRectFILL(Rectangle1 r);
//retorna a cor de preenchimento de determinado retângulo no svg

char getRectEDGE(Rectangle1 r);
//retorna a cor de borda de determinado retângulo no svg

#endif