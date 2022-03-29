#ifndef TEXT_H
#define TEXT_H

#include "list.h"

typedef void* Text1;

Text1 criaTxt();

Item buildText(FILE *arq, Text1 txt, char infos[], char *eptr);

int getTxtID(Text1 t);

float getTxtX(Text1 t);

float getTxtY(Text1 t);

float getTxtANCHOR(Text1 t);

char getTxtFILL(Text1 t);

char getTxtEDGE(Text1 t);

char getTxtTEXT(Text1 t);

#endif