#include "libs.h"

#ifndef QRY_H
#define QRY_H

/*
* Tratamento dos comandos do .qry. Leitura dos dados, identificação de
* comando e execução da determinada função
*/

void readQry(char *bedQry, char *bsdTxt);
// Leitura dos comando e delegação de tarefas para as
// determinados comandos

FILE *openQry(char *bedQry);
// Deve receber o diretório do arquivo .qry a ser criado
// Retorna o arquivo .qry criado para leitura

FILE *OpenTxt(char *bsdTxt);
// Deve receber o diretório do arquivo .txt a ser criado
// Retorna o arquivo .txt criado para registro do histórico solicitado

void na(FILE *qry, FILE *txt);
// Atribui o nível de agressividade v (real) às
// regiões de ataque

void tp(FILE *qry, FILE *txt);
// Torpedo no ponto (x,y). Remover todas as
// formas para as quais o ponto (x,y) é interno.

void tr(FILE *qry, FILE *txt);
// Torpedo replicante no ponto (x,y). Cria um
// clone para cada uma das formas atingidas e
// os posiciona transladados de (dx,dy) de seu
// original. O nível de proteção é o mesmo do
// original e as cores de borda e preenchimento
// são intercambiadas (se aplicável). O
// identificador dos clones devem começar no
// valor id.

void be(FILE *qry, FILE *txt);
// Bomba de irradiação atingiu região
// especificada nos parâmetros.
// Formas inteiramente contidas na região
// devem ter seu nível de proteção diminuído
// proporcionalmente (como explicado acima).
// Formas cujo nível de proteção atingir 0
// devem ser removidas.

void sel(Tree root, Info fig, double x, double y, double w, double h);
bool isInsideCirc(Info circ, x, y, w, h);
bool isInsideRect(Info rect, x, y, w, h);
bool isInsideLine(Info line, x, y, w, h);
bool isInsideText(Info text, x, y, w, h);

#endif