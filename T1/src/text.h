#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include "list.h"

typedef void* Text1;

/*
 * Texto é uma forma simples, com propriedades como sua âncora, 
 * cor de borda e de preenchimento, além da menssagem de texto em si. 
 * Pode ser escrito no formato de svg, possuindo assim um x e y no plano
 * O texto é o último parâmetro do comando. Pode incluir espaços  
 * em branco e se estende até o final da linha.
*/

Text1 criaTxt();
//cria um novo texto para svg

Item buildText(FILE *arq, Text1 txt, char *infos, char *eptr);
//realiza leitura e extração dos dados do texto no .geo

int getTxtID(Item t);
//retorna o id de determinado texto 

double getTxtX(Item t);
//retorna a coordenada x de determinado texto no svg

double getTxtY(Item t);
//retorna a coordenada y de determinado texto no svg

char *getTxtFILL(Item t);
//retorna a cor de preenchimento de determinado texto no svg

char *getTxtEDGE(Item t);
//retorna a cor de preenchimento de determinado texto no svg

char *getTxtANCHOR(Item t);
//retorna a posição da âncora de determinado texto no svg (inicio, meio ou fim)

char *getTxtTEXT(Item t);
//retorna o texto escrito propriamente dito de determinado texto no svg

char *getTxtTEXTAUX(Item t);
//retorna o texto escrito propriamente dito de determinado texto no svg

void settxtFILL(Item t, char *new_corp);
//altera a cor de preenchimento

void settxtEDGE(Item t, char *new_corb);
//altara a cor da borda

void settxtX(Item t, double dx);
//translada a coordenada x

void settxtY(Item t, double dy, int n);
//translada em DY vezes N a coordenada y

#endif
