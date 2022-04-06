#ifndef FILES_H
#define FILES_H

#include <stdio.h>

/*
 * Executa o devido tratamento para utilizar os diretórios e criar o arquivos necessários
*/

FILE *loadFile(char *path);

char *buildFilePath(char *directory, char *fileName);

#endif