#include "libs.h"

#ifndef SHAPES_H
#define SHAPES_H

Info newShape();

void setCircle(FILE *geo, Info f);

void setRectangle(FILE *geo, Info f);

void setLine(FILE *geo, Info f);

void setText(FILE *geo, Info f);

int getId(Info f);

double getX(Info f);

double getY(Info f);

double getW(Info f);

double getH(Info f);

double getR(Info f);

double getX2(Info f);

double getY2(Info f);

char *getStroke(Info f);

char *getFill(Info f);

char *getAnchor(Info f);

char *getText(Info f);

#endif