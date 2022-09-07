#include "libs.h"
#include "shapes.h"
#include "srb_tree.h"
#include "svg.h"

#ifndef QRY_H
#define QRY_H

void readQry(SRBTree t, char *bedQry, char *bsdSvg, char *bsdTxt);
// Função que lê o arquivo de consulta e define a execução das funções especificas

FILE *openQry(char *bedQry);
// Função que abre o arquivo de consulta.

FILE *openTxt(char *bsdTxt);
// Função que abre o arquivo de texto.

void find_id(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Função que busca o elemento pelo id e retorna a informação.

void e(FILE *qry, FILE *txt, SRBTree t);
void e_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Energiza todas as naus com o nível v.

void mv(FILE *qry, FILE *txt, SRBTree t);
void mv_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Desloca a forma de identificador i de dx no eixo x e dy
// no eixo y.

void lr(FILE *qry, FILE *txt, SRBTree t);
void lr_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Lança rede de dimensão (w,h) a uma distância d do
// lado especificado da nau de identificador i, se a nau
// tiver energia suficiente. Os elementos capturados são
// contabilizados e removidos

void d(FILE *qry, FILE *txt, SRBTree t);
void d_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Dispara canhão da nau i do lado especificado, se a
// nau tiver energia suficiente. A carga atinge a distância
// d. Se a carga atingir uma nau, esta nau é destruida
// (como especificado na descrição)

void mc(FILE *qry, FILE *txt, SRBTree t);
void mc_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Translada os peixes que estiverem dentro da região
// (x,y,w,h) de dx e dy.

void printResultados(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
// Função que imprime os resultados finais da pescaria no arquivo de texto.

#endif