#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#ifndef GEO_H
#define GEO_H

Item buildRectangle(FILE *arq, char infos[], char *eptr);

Item buildCircle(FILE *arq, char infos[], char *eptr);

Lista buildGeometricForms(FILE *arq);

#endif