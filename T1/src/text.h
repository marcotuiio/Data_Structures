#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include "list.h"

typedef void* Text1;

/*
 * Texto é uma forma simples, com propriedades como sua âncora, 
 * cor de borda e de preenchimento, além da menssagem de texto em si. 
 * Pode ser escrito no formato de svg, possuindo assim um x e y no plano
 * O texto txto é o último parâmetro docomando. Pode incluir espaços  
 * em branco e se estende até o final da linha.
*/

Text1 criaTxt();
//cria um novo texto para svg

Item buildText(FILE *arq, Text1 txt, char *infos[], char *eptr);
//realiza leitura e extração dos dados do texto no .geo

int getTxtID(Text1 t);
//retorna o id de determinado texto 

double getTxtX(Text1 t);
//retorna a coordenada x de determinado texto no svg

double getTxtY(Text1 t);
//retorna a coordenada y de determinado texto no svg

char *getTxtFILL(Text1 t);
//retorna a cor de preenchimento de determinado texto no svg

char *getTxtEDGE(Text1 t);
//retorna a cor de preenchimento de determinado texto no svg

char *getTxtANCHOR(Text1 t);
//retorna a posição da âncora de determinado texto no svg (inicio, meio ou fim)

char *getTxtTEXT(Text1 t);
//retorna o texto escrito propriamente dito de determinado texto no svg

#endif