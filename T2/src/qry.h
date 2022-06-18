#include "libs.h"

#ifndef QRY_H
#define QRY_H

/*
* Tratamento dos comandos do .qry. Leitura dos dados, identificação de
* comando e execução da determinada função
*/

void readQry(Tree root, char *bedQry, char* bsdSvgQry, char *bsdTxt);
// Leitura dos comando e delegação de tarefas para as
// determinados comandos

Pontos createPontos();
void updateDestr(Pontos pnts, double pt_destr);
void updateInativ(Pontos pnts, double pt_inativ);
void printPoints(Pontos pnts, FILE *txt);
// Funções com o intuito de manter a table de placar 
// do jogo contando e atualizada

FILE *openQry(char *bedQry);
// Deve receber o diretório do arquivo .qry a ser criado
// Retorna o arquivo .qry criado para leitura

FILE *openTxt(char *bsdTxt);
// Deve receber o diretório do arquivo .txt a ser criado
// Retorna o arquivo .txt criado para registro do histórico solicitado

double na(FILE *qry, FILE *txt);
// Atribui o nível de agressividade v (real) às
// regiões de ataque

void tp(Pontos pnts, Tree root, FILE *qry, FILE *svg, FILE *txt);
// Torpedo no ponto (x,y). Remover todas as
// formas para as quais o ponto (x,y) é interno.

void preOrderTp(Pontos pnts, FILE *txt, Tree t, Node root, double x, double y, char *check);
bool tpCirc(Info circ, double x, double y);
bool tpRect(Info rect, double x, double y);
bool tpLine(Info line, double x, double y);
bool tpTxt(Info text, double x, double y);
// Funções complementares e auxiliares de TP, para percorrer a árvore
// Recebem uma figura e as coordenadas do torpedo, 
// verificam se o torpedo acertou a determinada figura.
// Retorna verdadeiro se sim.

void tr(Tree root, FILE *qry, FILE *svg, FILE *txt);
// Torpedo replicante no ponto (x,y). Cria um
// clone para cada uma das formas atingidas e
// os posiciona transladados de (dx,dy) de seu
// original. O nível de proteção é o mesmo do
// original e as cores de borda e preenchimento
// são intercambiadas (se aplicável). O
// identificador dos clones devem começar no
// valor id.

void preOrderTr(FILE *txt, Tree t, Node root, double x, double y, double dx, double dy, int id, char *check);

void be(Pontos pnts, Tree root, FILE *qry, FILE *txt, FILE *svg, double v);
// Bomba de irradiação atingiu região
// especificada nos parâmetros.
// Formas inteiramente contidas na região
// devem ter seu nível de proteção diminuído
// proporcionalmente (como explicado acima).
// Formas cujo nível de proteção atingir 0
// devem ser removidas.

double calcReduc(double v, double areaEquip, double areaSel);
// dado um valor de agressividade (v) para os ataques, a área da figura
// atingida e a área total do ataque, retorna a redução causada

double calcSelArea(double w, double h);
// recebe as coordenadas de um ataque e retorna a área do mesmo (retangular)

void preOrderBe(Pontos pnts, FILE *svg, FILE *txt, Tree root, Info fig, double x, double y, double w, double h, double v);
bool isInsideCirc(Info circ, double x, double y, double w, double h);
void printReducCirc(Pontos pnts, FILE *svg, FILE *txt, Info circ, Tree root, Node node);
bool isInsideRect(Info rect, double x, double y, double w, double h);
void printReducRect(Pontos pnts, FILE *svg, FILE *txt, Info rect, Tree root, Node node);
bool isInsideLine(Info line, double x, double y, double w, double h);
void printReducLine(Pontos pnts, FILE *svg, FILE *txt, Info line, Tree root, Node node);
bool isInsideText(Info text, double x, double y, double w, double h);
void printReducText(Pontos pnts, FILE *svg, FILE *txt, Info text, Tree root, Node node);
// Funções axiliares e complementares que devem receber uma figura 
// e coordadenas de uma área retangular atingida por um ataque, 
// retornando verdadeiro se a figura está dentro da area em questão
// Também realizam a atualização do histórico no arq txt de saída

#endif