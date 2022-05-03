#include "libs.h"

#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * Tratamentos dos paramêtros de entrada , via argc e argv
 * Leitura dos dados, e atribuição dos determinados diretórios
 * Concatenação dos devidos diretorios e nomes de arquivos
 */

typedef void *Parameters;

Parameters *createParameters();
// Realiza malloc dos parâmetros esperados para executar o projeto

Parameters setParameters(int argc, char **argv, Parameters p);
// Deve receber os parâmetros de argc e argv para atribuir e definir
// para as devidas variáveis.

char *getOutputDir(Parameters p);
// Recebe os parâmetros, já organizados e interpretados, e retorna
// o referente ao diretório de saída.

char *makePathGeoFile(Parameters p);
// Recebe os parâmetros, já organizados e interpretados, e realiza
// o tratamento do nome do geo, para concatenar com o diretório de
// entrada e assim possibilitar o acesso correto ao arquivo

char *makePathQryFile(Parameters p, char* qryoriginal);
// Recebe os parâmetros, já organizados e interpretados, e realiza
// o tratamento do nome do qry, para concatenar com o diretório de
// entrada e assim possibilitar o acesso correto ao arquivo

FILE *loadFile(char *path);
// Recebe o diretório, que ja passou por todo o tratamento e
// abre os arquivos de consulta

char* getQryPath(Parameters p);
// Recebe parâmetros e retorna o path para qry

char *buildFilePath(char *directory, char *fileName);
// FUNÇÂO AUXILIAR PARA MAKEPATHFILE:
// Recebe o diretório e o nome do arquivo, faz as verificações
// se são um caminho válido e retorna o caminho pronto.

int qryExiste(Parameters p);
// Recebe os parâmetros, já organizados e interpretados, e realiza a
// verificação se existe ou não um arquivo de consuta qry recebido
// para execução do projeto (uma vez que receber o qry não é essencial)

void freeParam(Parameters p);

#endif