#ifndef QRY_H
#define QRY_H

#include <stdio.h>

#include "fila_circ.h"
#include "list.h"

/*
 * Tratamento dos comandos do .qry. Leitura dos dados, identificação de
 * comando e execução da determinada função
 */

void readComands(FILE *qry_dir, Lista r, Lista c, Lista l, Lista t, FILE *svg, FILE *txt);

void inp(FILE *txt, FILE *svg, FILE *arq, char *infos, Fila_Circular q, Lista r, Lista c, Lista l, Lista t);
// Insere no polígono corrente as coordenadas
// da âncora da figura identificada por i. No
// caso de linhas, insere a extremidade de menor
// x (se empate, de menor y)

Item criaPonto(double x, double y);
// Função auxiliar para o comando inp, cria um ponto
// com as coordenadas desejadas

void rmp(FILE *txt, FILE *svg, char *infos, Fila_Circular q);
// Remove a coordenada mais antiga inserida no
// poligono corrente.

void pol(FILE *txt, FILE *svg, FILE *arq, char *infos, char *eptr, Fila_Circular q);
// Produz um conjunto de linhas (e os insere no
//“banco de dados”). As linhas produzidas
// correspondem à borda do polígono e as linhas
// de seu preenchimento. Os identificadores das
// linhas produzidas são sequenciais, a partir de
// i. O parâmetro d é a distância entre as linhas
// do preenchimento; e é a espessura da linhas;
// corb a cor das linhas do polígono; corp, a cor
// das linhas do preenchimento.

double getpX(Item n);
// função auxiliar para pol
// retorna o x dos pontos para montar as linhas das bordas

double getpY(Item n);
// função auxiliar para pol
// retorna o y dos pontos para montar as linhas das bordas

void clp(FILE *txt, Fila_Circular q);
// Remove todas as coordenadas do polígono
// corrente

void sel(FILE *txt, FILE *svg, FILE *arq, char *infos, char *eptr, Lista g, Lista a, Lista sR, Lista sC, Lista sL, Lista sT, Lista r, Lista c, Lista l, Lista t);
// Seleciona as figuras inteiramente dentro da
// região especificada pelos parâmetros.
//(Desconsidera seleções anteriores)
// SVG: desenhar região. Desenhar um anel
// vermelho em volta da âncora das figuras
// selecionadas.

Item controleTipo(char *t);
// função auxiliar para o comando ups saber quais
// figuras foram as ultimas a entrar no banco de dados

char *getTipo(Item t);
// função auxiliar para ups,
// retorna o tipo das figuras selecionadas

Item criaRecaux(double x, double y, double w, double h);
// função auxiliar para os comandos SEL e SEL+, para controle da area de seleção

double getrX(Item r);
// função auxiliar para os comandos SEL e SEL+
// retorna o X do retângulo de seleção

double getrY(Item r);
// função auxiliar para os comandos SEL e SEL+,
// retorna o Y do retângulo de seleção

double getrW(Item r);
// função auxiliar para os comandos SEL e SEL+,
// retorna o W do retângulo de seleção

double getrH(Item r);
// função auxiliar para os comandos SEL e SEL+,
// retorna o H do retângulo de seleção

void selplus(FILE *txt, FILE *svg, FILE *arq, char *infos, char *eptr, Lista g, Lista a, Lista sR, Lista sC, Lista sL, Lista sT, Lista r, Lista c, Lista l, Lista t);
// Semelhante à operação sel, porém, acrescenta
//(união) as figuras selecionadas àquelas
// anteriormente selecionadas. ATENÇÃO: as
// figuras selecionadas por este comando devem
// suceder (na lista) àquelas selecionadas por
// comandos anteriores.

void dels(FILE *txt, Lista sR, Lista sC, Lista sL, Lista sT);
// Remove do “banco de dados” todas as figuras
// selecionadas.

void dps(FILE *txt, FILE *svg, FILE *arq, char *infos, char *eptr, Lista sR, Lista sC, Lista sL, Lista sT);
// Cria novas formas, semelhantes às
// selecionadas, porém, transladadas de dx e dy,
// cujos identificadores começam em i e são
// incrementados sequencialmente .

void ups(FILE *txt, FILE *svg, FILE *arq, char *infos, char *eptr, Lista g, Lista sR, Lista sC, Lista sL, Lista sT);
// Altera as cores e a posição de n figuras antes
//(se n<0) ou depois (se n>0) da última figura
// selecionada pelo último sel ou sel+. Atribui
// corb à borda das figuras e corp ao
// preenchimento. Translada a figura em dx
// unidades na horizontal e incrementalmente dy
// na vertical.

#endif