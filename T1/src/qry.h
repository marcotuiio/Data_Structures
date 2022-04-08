#ifndef QRY_H
#define QRY_H

#include <stdio.h>

/*
 * Tratamento dos comandos do .qry. Leitura dos dados, identificação de 
 * comando e execução da determinada função
*/

void readComands (FILE * qry_dir);

void inp(FILE *arq, char *infos[]);

void rmp(char *infos[]);

void pol(FILE *arq, char *infos[], char *eptr);

void clp();

void sel(FILE *arq, char *infos[], char *eptr);

void selplus(FILE *arq, char *infos[], char *eptr);

void dels();

void dps(FILE *arq, char *infos[], char *eptr);

void ups(FILE *arq, char *infos[], char *eptr);

#endif
