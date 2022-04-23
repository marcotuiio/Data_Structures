#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>

/*
 * Tratamentos dos paramêtros de entrada , via argc e argv
 * Leitura dos dados, e atribuição dos determinados diretórios
 * Concatenação dos devidos diretorios e nomes de arquivos
*/

typedef void* Parameters;

Parameters *createParameters();

Parameters setParameters(int argc, char** argv, Parameters p);

char *getOutputDir(Parameters p);

char *makePathGeoFile(Parameters p);

char *makePathQryFile(Parameters p);

FILE *loadFile(char *path);

char *buildFilePath(char *directory, char *fileName);

int qryExiste (Parameters p);

// void freeParam(Parameters p);

#endif