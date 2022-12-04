#ifndef via_h
#define via_h
#include "libs.h"

InfoEdge criaArestaVia(char* rua, char* ldir, char* lesq, double cmp, double vm);
InfoNode criaVerticeVia(char* id, double x, double y);
double getXvia(InfoNode V);
double getYvia(InfoNode V);
void setSentido(InfoEdge A, char* sentido);

#endif