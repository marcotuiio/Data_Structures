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

void replicateRect(Tree t, Info base_r, Info new_r, double dx, double dy, int id);
// dado um retângulo base, um novo retângulo e um deslocamento, define o novo retângulo 
// e o insere a árvore

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

void setProtecRect(Info r, double reduc);
// atualiza o nivel de proteção da figuração, dada 
// uma redução de um ataque

double getProtecRect(Info r);
// retorna a proteção atual do determinado navio

double getRectArea(Info r);
// dado um determinado retângulo, retorna a área do mesmo

void freeRect(Info r);

#endif