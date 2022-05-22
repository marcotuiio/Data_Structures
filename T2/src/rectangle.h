#include "libs.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

/*
* Retângulo é uma figura geometrica básica, com propriedades
* como altura, largura, cor de borda e de preenchimento. Pode ser desenhado
* no formato de svg, possuindo assim um x e y no plano.
*/

Info criaRec();
// cria um novo retângulo para svg

void buildRectangle(FILE *geo, Info r, Tree root);
// realiza leitura e extração dos dados do retângulo no .geo

int getRectID(Info r);
// retorna o id de determinado retângulo

double getRectX(Info r);
// retorna a coordenada x de determinado retângulo no svg

double getRectY(Info r);
// retorna a coordenada y de determinado retângulo no svg

double getRectWIDTH(Info r);
// retorna a largura de determinado retângulo no svg

double getRectHEIGHT(Info r);
// retorna a altura de determinado retângulo no svg

char *getRectFILL(Info r);
// retorna a cor de preenchimento de determinado retângulo no svg

char *getRectEDGE(Info r);
// retorna a cor de borda de determinado retângulo no svg

void setrectFILL(Info r, char *new_corp);
// altera a cor de preenchimento

void setrectEDGE(Info r, char *new_corb);
// altera a cor da borda

void setrectX(Info r, double dx);
// translada a coordenada x

void setrectY(Info r, double dy, int n);
// translada DY vezes N a coordenada y

void freeRect(Info r);

#endif