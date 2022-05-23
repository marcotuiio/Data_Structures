#include "libs.h"

#ifndef TEXT_H
#define TEXT_H

/*
* Texto é uma forma simples, com propriedades como sua âncora,
* cor de borda e de preenchimento, além da menssagem de texto em si.
* Pode ser escrito no formato de svg, possuindo assim um x e y no plano
* O texto é o último parâmetro do comando. Pode incluir espaços
* em branco e se estende até o final da linha.
*/

Info criaTxt();
// cria um novo texto para svg

void buildText(FILE *geo, Info t, Tree root);
// realiza leitura e extração dos dados do texto no .geo

int getTxtID(Info t);
// retorna o id de determinado texto

double getTxtX(Info t);
// retorna a coordenada x de determinado texto no svg

double getTxtY(Info t);
// retorna a coordenada y de determinado texto no svg

char *getTxtFILL(Info t);
// retorna a cor de preenchimento de determinado texto no svg

char *getTxtEDGE(Info t);
// retorna a cor de preenchimento de determinado texto no svg

char *getTxtANCHOR(Info t);
// retorna a posição da âncora de determinado texto no svg (inicio, meio ou fim)

char *getTxtTEXT(Info t);
// retorna o texto escrito propriamente dito de determinado texto no svg

char *getTxtTEXTAUX(Info t);
// retorna o texto escrito propriamente dito de determinado texto no svg

void settxtFILL(Info t, char *new_corp);
// altera a cor de preenchimento

void settxtEDGE(Info t, char *new_corb);
// altara a cor da borda

void settxtX(Info t, double dx);
// translada a coordenada x

void settxtY(Info t, double dy);
// translada em DY a coordenada y

void freeTxt(Info t);

#endif
