#include "libs.h"
#include "avl_tree.h"

#ifndef SHAPES_H
#define SHAPES_H

Info newShape();
// Cria uma nova forma vazia e retorna um ponteiro para ela

void setCircle(FILE *geo, Tree t, Info f);
// Recebe um arquivo de entrada e uma forma e preenche um circulo com os dados do arquivo

void setRectangle(FILE *geo, Tree t, Info f);
// Recebe um arquivo de entrada e uma forma e preenche um retangulo com os dados do arquivo

void setLine(FILE *geo, Tree t, Info f);
// Recebe um arquivo de entrada e uma forma e preenche uma linha com os dados do arquivo

void setText(FILE *geo, Tree t, Info f);
// Recebe um arquivo de entrada e uma forma e preenche um texto com os dados do arquivo

int getType(Info f);
// Recebe uma forma e retorna o tipo da forma

int getId(Info f);
// Recebe uma forma e retorna o seu id

double getX(Info f);
// Recebe uma forma e retorna o seu x

double getY(Info f);
// Recebe uma forma e retorna o seu y

double getW(Info f);
// Recebe uma forma e retorna o seu w

double getH(Info f);
// Recebe uma forma e retorna o seu h

double getR(Info f);
// Recebe uma forma e retorna o seu r

double getX2(Info f);
// Recebe uma forma e retorna o seu x2

double getY2(Info f);
// Recebe uma forma e retorna o seu y2

char *getStroke(Info f);
// Recebe uma forma e retorna sua cor de borda

char *getFill(Info f);
// Recebe uma forma e retorna sua cor de preenchimento

char *getAnchor(Info f);
// Recebe uma forma e retorna seu ponto de ancoragem

char *getText(Info f);
// Recebe uma forma e retorna seu texto

#endif