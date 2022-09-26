#include "libs.h"
#include "srb_tree.h"

#ifndef SHAPES_H
#define SHAPES_H

Info newShape();
// Cria uma nova forma vazia e retorna um ponteiro para ela

void setCircle(FILE *geo, SRBTree t, Info f);
// Recebe um arquivo de entrada e uma forma e preenche um circulo com os dados do arquivo

void setRectangle(FILE *geo, SRBTree t, Info f);
// Recebe um arquivo de entrada e uma forma e preenche um retangulo com os dados do arquivo

void setLine(FILE *geo, SRBTree t, Info f);
void findLineXY(double *y1, double *y2, Info f);
// Recebe um arquivo de entrada e uma forma e preenche uma linha com os dados do arquivo

void setText(FILE *geo, SRBTree t, Info f);
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

double getLineLength(Info line);
// Recebe uma linha e retorna a sua comprimento

void setEnergy(Info rect, double energy);
// Recebe um retangulo (nau) e atribui a sua energia

double getEnergy(Info rect);
// Recebe um retangulo (nau) e retorna a sua energia

void addGold(Info rect, double gold);
// Recebe um retangulo (nau) e atribui a sua quantidade de ouro

double getGold(Info rect);
// Recebe um retangulo (nau) e retorna a sua quantidade de ouro

void setX(Info f, double dx);
// Recebe uma forma e translada sua posicao em dx

void setY(Info f, double dy);
// Recebe uma forma e translada sua posicao em dy

void setX2(Info f, double dx);
// Recebe uma linha e translada sua posicao em dx

void setY2(Info f, double dx);
// Recebe uma linha e translada sua posicao em dy

bool energyDeslocamento(Info i, double d);
// Recebe uma nau e o deslocamento proposto, calcula se possui energia
// realiza a atualização e retorna verdadeiro, caso não seja possivel, falso

bool energyArremesso(Info i, double d, double A, double *need);
// Recebe uma nau e a area de rede do lançamento, calcula se possui energia
// realiza a atualização e retorna verdadeiro, caso não seja possivel, falso

bool energyShot(Info i, double d);
// Recebe uma nau e o d do tiro proposto, calcula se possui energia
// realiza a atualização e retorna verdadeiro, caso não seja possivel, falso

bool hitRectangle(Info i, double xt, double yt);
// Recebe uma forma e um ponto e retorna se o ponto esta dentro da forma

bool insideNet(Info i, double xr, double yr, double w, double h);
// Recebe uma forma e um retangulo e retorna se a forma esta dentro do retangulo

bool fishInside(Info i, double x, double y, double w, double h);
// Recebe um circulo e um retangulo e retorna se a forma esta dentro do retangulo

#endif