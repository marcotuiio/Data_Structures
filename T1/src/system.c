#include "system.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct parameters {
    char *outputDir;
    char *inputDir;
    char *nameGeoFile;
    char *nameQryFile;
};

typedef struct parameters ParamL;

Parameters *setParameters(int argc, char **argv, Parameters p) {
    printf("\nInicio set param\n");
    ParamL *param = (ParamL *)p;

    // printf("argc = %d\n", argc);
    if (argc < 0) {
        return NULL;
    }

    for (int index = 1; index < argc; index++) {
        if (!strcmp(argv[index], "-e")) {
            param->inputDir = argv[index + 1];
            printf("Dir Input: %s\n", param->inputDir);

        } else if (!strcmp(argv[index], "-f")) {
            strcpy(param->nameGeoFile, argv[index + 1]);
            printf("Geo file name: %s\n", param->nameGeoFile);

        } else if (!strcmp(argv[index], "-q")) {
            strcpy(param->nameQryFile, argv[index + 1]);
            printf("Qry file name: %s\n", param->nameQryFile);

        } else if (!strcmp(argv[index], "-o")) {
            strcpy(param->outputDir, argv[index + 1]);
            printf("Dir Output: %s\n", param->outputDir);
        }
    }
    return param;
}

Parameters *createParameters(int argc, char **argv) {
    printf("\nInicio create param\n");
    ParamL *param = calloc(1, sizeof(ParamL *));

    param->outputDir = malloc(sizeof(char *));
    param->inputDir = malloc(200);
    param->nameGeoFile = malloc(sizeof(char *));
    param->nameQryFile = malloc(sizeof(char *));

    param->inputDir = getcwd(NULL, 0);
    param->nameGeoFile = malloc(sizeof(char *));
    strcpy(param->nameQryFile, "nda");

    return setParameters(argc, argv, param);
}

char *makePathGeoFile(Parameters p) {
    printf("\nInicio path geo file\n");
    ParamL *param = (ParamL *)p;

    return buildFilePath(param->inputDir, param->nameGeoFile);
}

char *makePathQryFile(Parameters p) {
    printf("\nInicio path geo file\n");
    ParamL *param = (ParamL *)p;

    // printf("antes %s\n", param->nameQryFile);
    strcat(param->nameQryFile, ".qry");
    // printf("depois %s\n", param->nameQryFile);
    return buildFilePath(param->inputDir, param->nameQryFile);
}

char *getOutputDir(Parameters p) {
    printf("\nInicio getOutputDir\n");
    ParamL *param = (ParamL *)p;

    char under[] = "_";
    char separator[] = "/";
    char tok[] = ".";
    char type[] = ".svg";
    char *geo_token = strtok(param->nameGeoFile, tok);

    if (strcmp(param->nameQryFile, "nda") == 0) {
        strcat(param->outputDir, separator);
        strcat(param->outputDir, geo_token);
        strcat(param->outputDir, type);

        printf("New output dir: %s\n", param->outputDir);
        return param->outputDir;
    }

    char *qry_token = strtok(param->nameQryFile, tok);
    char *new = malloc(strlen(geo_token) + strlen(qry_token) + 2);
    strcpy(new, geo_token);
    strcat(new, under);
    strcat(new, qry_token);

    strcat(param->outputDir, separator);
    strcat(param->outputDir, new);
    strcat(param->outputDir, type);

    // printf("New output dir: %s\n", param->outputDir);
    return param->outputDir;
}

char *buildFilePath(char *directory, char *fileName) {
    printf("\nInicio Build file path\n");
    printf("Dir: %s - File Name: %s\n", directory, fileName);
    char separator[] = "/";
    char *result = malloc(strlen(directory) + strlen(fileName) + 1);

    strcpy(result, directory);
    strcat(result, separator);
    strcat(result, fileName);

    // printf("\nPath geo file: %s\n", result);
    return result;
}

FILE *loadFile(char *path) {
    printf("\nInicio load file\n");
    printf("Path_QRY: %s\n", path);
    FILE *arq = fopen(path, "r");

    if (arq == NULL) {
        printf("Problemas na criação do arquivo!\n");
        return NULL;
    }

    return arq;
}

int qryExiste(Parameters p) {
    ParamL *param = (ParamL *)p;

    if (strcmp(param->nameQryFile, "nda") == 0) {
        return 0;
    }

    return 1;
}