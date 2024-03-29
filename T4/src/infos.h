#include "libs.h"

#ifndef INFOS_H
#define INFOS_H

void *createDetails(char *sw, char *cfill, char *cstrk);
// Creates a new details pattern

void* getDetails(InfoRb info);
// Returns the details of a given info

InfoRb createInfoRb(char* cep, double x, double y, double w, double h, void* details);
// Creates a new InfoRb with the given name and coordinates

InfoEdge createInfoEdge(double vm, double cmp, char* ldir, char* lesq, char* nomeEdge);
// Creates a new InfoEdge with the given values

InfoNode createInfoVertex(double x, double y, char* nome);
// Creates a new InfoNode with the given coordinates

char* getSW(InfoRb info);
// Returns the border width of the given details

void setSW(void *detail, char* sw);
// Sets the border width of the given InfoRb

char* getCFill(InfoRb info);
// Returns the fill color of the given details

void setCFill(void *detail, char* cfill);
// Sets the fill color of the given InfoRb

char* getCStrk(InfoRb info);
// Returns the stroke color of the given details

void setCStrk(void *detail, char* cstrk);
// Sets the stroke color of the given InfoRb

char* getCep(InfoRb info);
// Returns the cep of the given InfoRb

double getXNode(InfoRb info);
// Returns the x coordinate of the given InfoRb

double getYNode(InfoRb info);
// Returns the y coordinate of the given InfoRb

double getWNode(InfoRb info);
// Returns the width of the given InfoRb

double getHNode(InfoRb info);
// Returns the height of the given InfoRb 

void setVMEdge(InfoEdge info, double vm);
// Sets the velocity of the given InfoEdge

double getVMEdge(InfoEdge info);
// Returns the vm value of the given InfoEdge

double getCMPEdge(InfoEdge info);
// Returns the cmp value of the given InfoEdge

char* getLDirEdge(InfoEdge info);
// Returns the ldir value of the given InfoEdge

char* getLEsqEdge(InfoEdge info);
// Returns the lesq value of the given InfoEdge

char *getNomeEdge(InfoEdge info);
// Returns the name of the given InfoEdge

void setBloqNameEdge(InfoEdge info, char *bloqName);
// Sets the name of the given InfoEdge

char *getBloqNameEdge(InfoEdge info);
// Returns the name of the given InfoEdge

void setSentidoPrimEdge(InfoEdge info, char *sentido);
// Sets the sentido of the given InfoEdge

char *getSentidoPrimEdge(InfoEdge info);
// Returns the sentido of the given InfoEdge

void setSentidoSecEdge(InfoEdge info, char *sentido);
// Sets the sentido of the given InfoEdge

char *getSentidoSecEdge(InfoEdge info);
// Returns the sentido of the given InfoEdge

double getXVertex(InfoNode info);
// Returns the x coordinate of the given InfoNode

double getYVertex(InfoNode info);
// Returns the y coordinate of the given InfoNode

char *getNomeVertex(InfoNode info);
// Returns the name of the given InfoNode

bool insideQuadra(InfoRb info, double x, double y, double w, double h);
// Returns true if the given rectangle is inside the given InfoRb

bool insideEdge(double x, double y, double w, double h, double x1, double y1, double x2, double y2);
// Returns true if the given edge is inside the given rectangle

#endif