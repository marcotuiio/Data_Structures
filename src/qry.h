#ifndef qry_h
#define qry_h
#include "libs.h"
#include "SRBtree.h"

void readingQry(FILE *qryFile, SRbTree arvore, FILE *svg, FILE *arqTxt);
/*
    Faz a leitura do arquivo .qry passado de parâmetro
    e chama todas as funções passadas no arquivo.
*/

// ==================================== AUXILIARES =========================================
void buscaCep(void* i, void* aux);
void buscaRegiaoRetangular(void* i, void* aux);
void pnt(char* cep, char* cfill, char* cstrk, SRbTree tree, FILE* txt);
void oFunc(char* cep, char* face, double num, SRbTree tree, FILE* svg);
void catac(double x, double y, double w, double h, FILE* arqTxt, FILE* arqSvg, SRbTree tree);
void blq(char* nome, char* sentido, double x, double y, double w, double h);
void rbl(char* nome);
void rf(char* cep, char* face, double fator);
void bFunc(double x, double y, double fator);
void pFunc(char* cep, char* face, double num, char* cmc, char* cmr);

#endif