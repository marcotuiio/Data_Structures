#ifndef TEXT_H
#define TEXT_H

#include "list.h"

typedef void* Text1;

Text1 criaTxt();
//cria um novo texto para svg

Item buildText(FILE *arq, Text1 txt, char infos[], char *eptr);
//realiza leitura e extração dos dados do texto no .geo

int getTxtID(Text1 t);
//retorna o id de determinado texto 

float getTxtX(Text1 t);
//retorna a coordenada x de determinado texto no svg

float getTxtY(Text1 t);
//retorna a coordenada y de determinado texto no svg

float getTxtANCHOR(Text1 t);
//retorna a coordenada da âncora de determinado texto no svg

char getTxtFILL(Text1 t);
//retorna a cor de preenchimento de determinado texto no svg

char getTxtEDGE(Text1 t);
//retorna a cor de preenchimento de determinado texto no svg

char getTxtTEXT(Text1 t);
//retorna o texto escrito propriamente dito de determinado texto no svg

#endif