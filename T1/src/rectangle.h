#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdio.h>
#include "list.h"

typedef void* Rectangle1;

/*
 * Retângulo é uma figura geometrica básica, com propriedades
 * como altura, largura, cor de borda e de preenchimento. Pode ser desenhado
 * no formato de svg, possuindo assim um x e y no plano.
*/

Rectangle1 criaRec();
//cria um novo retângulo para svg

Item buildRectangle(FILE *arq, Rectangle1 rec, char *infos, char *eptr);
//realiza leitura e extração dos dados do retângulo no .geo

int getRectID(Rectangle1 r);
//retorna o id de determinado retângulo

double getRectX(Rectangle1 r);
//retorna a coordenada x de determinado retângulo no svg

double getRectY(Rectangle1 r);
//retorna a coordenada y de determinado retângulo no svg

double getRectWIDTH(Rectangle1 r);
//retorna a largura de determinado retângulo no svg

double getRectHEIGHT(Rectangle1 r);
//retorna a altura de determinado retângulo no svg

char* getRectFILL(Rectangle1 r);
//retorna a cor de preenchimento de determinado retângulo no svg

char* getRectEDGE(Rectangle1 r);
//retorna a cor de borda de determinado retângulo no svg

void setrectFILL(Rectangle1 r, char *new_corp);
//altera a cor de preenchimento

void setrectEDGE(Rectangle1 r, char *new_corb);
//altera a cor da borda

void setrectX(Rectangle1 r, double dx);
//translada a coordenada x

void setrectY(Rectangle1 r, double dy, int n);
//translada DY vezes N a coordenada y
 
#endif