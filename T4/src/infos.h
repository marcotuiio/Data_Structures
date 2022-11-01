#include "libs.h"

#ifndef INFOS_H
#define INFOS_H

void* createDetails();
// Creates a new details pattern

InfoAvl createInfoAvl(char *cep, double x, double y, double w, double h, void* details);
// Creates a new InfoAvl with the given name and coordinates

InfoEdge createInfoEdge(double vm, double cmp, char *ldir, char *lesq, char *nomeEdge);
// Creates a new InfoEdge with the given values

char* getSw(void* detail);
// Returns the border width of the given details

void setSW(void* detail, char *sw);
// Sets the border width of the given InfoAvl

char* getCFill(void* detail);
// Returns the fill color of the given details

void setCFill(void* detail, char *cfill);
// Sets the fill color of the given InfoAvl

char* getCStrk(void* detail);
// Returns the stroke color of the given details

void setCStrk(void* detail, char *cstrk);
// Sets the stroke color of the given InfoAvl

double getXNode(InfoAvl info);
// Returns the x coordinate of the given InfoAvl

double getYNode(InfoAvl info);
// Returns the y coordinate of the given InfoAvl

double getVMEdge(InfoEdge info);
// Returns the vm value of the given InfoEdge

double getCMPEdge(InfoEdge info);
// Returns the cmp value of the given InfoEdge

char *getLDirEdge(InfoEdge info);
// Returns the ldir value of the given InfoEdge

char *getLEsqEdge(InfoEdge info);
// Returns the lesq value of the given InfoEdge

#endif