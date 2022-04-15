#ifndef QRY_H
#define QRY_H

#include <stdio.h>

#include "fila_circ.h"
#include "list.h"

/*
 * Tratamento dos comandos do .qry. Leitura dos dados, identificação de
 * comando e execução da determinada função
 */

void readComands(FILE *qry_dir, Lista r, Lista c, Lista l, Lista t, FILE *svg, char *diroutput);

FILE *createTxt(char *output);

void inp(FILE *arq, char *infos[], Fila_Circular q, Lista r, Lista c, Lista l, Lista t);
// Insere no polígono corrente as coordenadas
// da âncora da figura identificada por i. No
// caso de linhas, insere a extremidade de menor
// x (se empate, de menor y)

Item criaPonto(double x, double y);
// Função auxiliar para o comando inp, cria um ponto
// com as coordenadas desejadas

void rmp(char *infos[], Fila_Circular q);
// Remove a coordenada mais antiga inserida no
// poligono corrente.

void pol(FILE *arq, char *infos[], char *eptr);
// Produz um conjunto de linhas (e os insere no
//“banco de dados”). As linhas produzidas
// correspondem à borda do polígono e as linhas
// de seu preenchimento. Os identificadores das
// linhas produzidas são sequenciais, a partir de
// i. O parâmetro d é a distância entre as linhas
// do preenchimento; e é a espessura da linhas;
// corb a cor das linhas do polígono; corp, a cor
// das linhas do preenchimento.

void clp(Fila_Circular q);
// Remove todas as coordenadas do polígono
// corrente

void sel(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT, Lista r, Lista c, Lista l, Lista t);
// Seleciona as figuras inteiramente dentro da
// região especificada pelos parâmetros.
//(Desconsidera seleções anteriores)
// SVG: desenhar região. Desenhar um anel
// vermelho em volta da âncora das figuras
// selecionadas.

void selplus(FILE *arq, char *infos[], char *eptr);
// Semelhante à operação sel, porém, acrescenta
//(união) as figuras selecionadas àquelas
// anteriormente selecionadas. ATENÇÃO: as
// figuras selecionadas por este comando devem
// suceder (na lista) àquelas selecionadas por
// comandos anteriores.

void dels(Lista sR, Lista sC, Lista sL, Lista sT);
// Remove do “banco de dados” todas as figuras
// selecionadas.

void dps(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT);
// Cria novas formas, semelhantes às
// selecionadas, porém, transladadas de dx e dy,
// cujos identificadores começam em i e são
// incrementados sequencialmente .

void ups(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT);
// Altera as cores e a posição de n figuras antes
//(se n<0) ou depois (se n>0) da última figura
// selecionada pelo último sel ou sel+. Atribui
// corb à borda das figuras e corp ao
// preenchimento. Translada a figura em dx
// unidades na horizontal e incrementalmente dy
// na vertical.

#endif
