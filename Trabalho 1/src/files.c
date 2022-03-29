#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"

FILE *loadFile(char path[]){
    printf("\nInicio load file\n");
    printf("%s\n", path);
    FILE *arq = fopen(path, "r");
    if(arq == NULL) {
        printf("Problemas na criação do arquivo!\n");
        return NULL;
    }
    return arq;
}

char *buildFilePath(char *directory, char *fileName){
    printf("\nInicio Build file path\n");
    printf("Dir: %s - File Name: %s\n", directory, fileName);
    char separator[] = "/";
    char *result = malloc(strlen(directory)+strlen(fileName)+1);

    strcpy(result, directory);
    strcat(result, separator);
    strcat(result, fileName);

    return result;
}