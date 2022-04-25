#include <stdlib.h>
#include <stdio.h>

#include "list.h"

#ifndef GEO_H
#define GEO_H

void buildGeometricForms(FILE *arq, char *svgoutput, FILE *qry, int existe);

FILE *createTxt(char *output);

FILE *createSvg(char *svg_path);

void killSvg(FILE *svg);

#endif
