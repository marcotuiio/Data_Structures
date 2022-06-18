#include "libs.h"

#ifndef LINE_H
#define LINE_H

/*
 * Linha é uma forma geometrica básica, com propriedades
 * como x inicial, y inicial, x final, y final e sua cor. Pode
 * ser desenhado no formato de svg, possuindo assim um x e y no plano
 */

Info criaLinha();
// cria uma nova linha para svg

void buildLine(FILE *geo, Info l, Tree root);
// realiza leitura e extração dos dados da linha no .geo

void replicateLine(Tree t, Info base_l, Info new_l, double dx, double dy, int id);
// dada uma linha, uma nova linha e um deslocamento, define as coordenadas da nova linha e
// insere na árvore

int getLineID(Info l);
// retorna o id de determinada linha

double getLineX(Info l);
// retorna a coordenada x inicial de determinada linha no svg

double getLineY(Info l);
// retorna a coordenada y inicial de determinada linha no svg

double getLineFINALX(Info l);
// retorna a coordenada x final de determinada linha no svg

double getLineFINALY(Info l);
// retorna a coordenada y final de determinada linha no svg

char *getLineCOLOR(Info l);
// retorna a cor de determinada linha no svg

void setProtecLine(Info l, double reduc);
// atualiza o nivel de proteção da figuração, dada
// uma redução de um ataque

double getProtecLine(Info l);
// retorna a proteção atual do determinado navio

double getLineArea(Info l);
// dada uma determinada linha, retorna a área da mesma

void freeLine(Info l);

double getLineLenght(double x1, double y1, double x2, double y2);
double sqroot(double num);
// dada um determinada Linha l, calcula seu comprimento e o retorna
// no formato de double

#endif