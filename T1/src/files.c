#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *buildFilePath(char *directory, char *fileName) {
    printf("\nInicio Build file path\n");
    printf("Dir: %s - File Name: %s\n", directory, fileName);
    char separator[] = "/";
    char *result = malloc(strlen(directory) + strlen(fileName) + 1);

    strcpy(result, directory);
    strcat(result, separator);
    strcat(result, fileName);

    //printf("\nPath geo file: %s\n", result);

    return result;
}

FILE *loadFile(char path[]) {
    printf("\nInicio load file\n");
    printf("path: %s\n", path);
    FILE * arq = fopen("/home/marcotuiio/ED1/EDor/T1/input/g.geo", "r");
    if (arq == NULL) {
        printf("Problemas na criação do arquivo!\n");
        return NULL;
    }
    return arq;
}