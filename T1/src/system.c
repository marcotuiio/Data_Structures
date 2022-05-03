#include "system.h"

struct parameters {
    char *outputDir;
    char *inputDir;
    char *nameGeoFile;
    char *nameQryFile;
};

typedef struct parameters ParamL;

Parameters setParameters(int argc, char **argv, Parameters p) {
    // printf("\n--- INICIO SET PARAM ---\n");
    ParamL *param = (ParamL *)p;

    // printf("argc = %d\n", argc);
    if (argc < 0) {
        return NULL;
    }

    for (int index = 1; index < argc; index++) {
        if (!strcmp(argv[index], "-e")) {
            // bed = calloc(strlen(argv[i]) + 1, sizeof(char)); usar no t2
            strcpy(param->inputDir, argv[index + 1]);
            // printf("Dir Input: %s\n", param->inputDir);

        } else if (!strcmp(argv[index], "-f")) {
            // geofile = calloc(strlen(argv[i]) + 1, sizeof(char)); usar no t2
            strcpy(param->nameGeoFile, argv[index + 1]);
            // printf("Geo file name: %s\n", param->nameGeoFile);

        } else if (!strcmp(argv[index], "-q")) {
            // qryfile = calloc(strlen(argv[i]) + 1, sizeof(char)); usar no t2
            strcpy(param->nameQryFile, argv[index + 1]);
            // printf("Qry file name: %s\n", param->nameQryFile);

        } else if (!strcmp(argv[index], "-o")) {
            // bsd = calloc(strlen(argv[i]) + 1, sizeof(char)); usar no t2
            strcpy(param->outputDir, argv[index + 1]);
            // printf("Dir Output: %s\n", param->outputDir);
        }
    }
    return param;
}

Parameters *createParameters(int argc, char **argv) {
    printf("\n--- INICIO CREATE PARAM ---\n");
    ParamL *param = calloc(1, sizeof(ParamL));

    param->outputDir = (char *)calloc(300, sizeof(char));
    param->inputDir = (char *)calloc(300, sizeof(char));
    param->nameGeoFile = (char *)calloc(100, sizeof(char));
    param->nameQryFile = (char *)calloc(100, sizeof(char));

    strcpy(param->nameQryFile, "nda");

    return setParameters(argc, argv, param);
}

char *makePathGeoFile(Parameters p) {
    // printf("\n--- PATH GEO FILE ---\n");
    ParamL *param = (ParamL *)p;
    int len_dir = strlen(param->inputDir);
    int len_geo = strlen(param->nameGeoFile);

    if (param->inputDir[len_dir - 1] == '/') {
        param->inputDir[len_dir - 1] = '\0';
    }
    // Removendo / no final do nome geo
    if (param->nameGeoFile[len_geo - 1] == '/') {
        param->nameGeoFile[len_geo - 1] = '\0';
    }
    // Removendo / no inicio do nome geo
    if (param->nameGeoFile[0] == '/') {
        param->nameGeoFile = param->nameGeoFile + 1;
    }

    return buildFilePath(param->inputDir, param->nameGeoFile);
}

char *makePathQryFile(Parameters p, char* qryoriginal) {
    // printf("\n--- PATH QRY FILE ---\n");
    ParamL *param = (ParamL *)p;
    int len_dir = strlen(param->inputDir);
    int len_qry = strlen(qryoriginal);

    if (param->inputDir[len_dir - 1] == '/') {
        param->inputDir[len_dir - 1] = '\0';
    }
    // Removendo / no inicio do nome qry
    if (qryoriginal[len_qry - 1] == '/') {
        qryoriginal[len_qry - 1] = '\0';
    }
    // Removendo / no inicio do nome qry
    if (qryoriginal[0] == '/') {
        qryoriginal = qryoriginal + 1;
    }
    // puts(qryoriginal);

    return buildFilePath(param->inputDir, qryoriginal);
}

char *getOutputDir(Parameters p) {
    // printf("\n--- GET BSD ---\n");
    ParamL *param = (ParamL *)p;
    int len_dir = strlen(param->outputDir);

    if (param->outputDir[len_dir - 1] == '/') {
        param->outputDir[len_dir - 1] = '\0';
    }

    char under[] = "_";
    char separator[] = "/";
    char tok[] = ".";
    char type_svg[] = ".svg";
    char *geo_token = strtok(param->nameGeoFile, tok);

    if (strcmp(param->nameQryFile, "nda") == 0) {
        strcat(param->outputDir, separator);
        strcat(param->outputDir, geo_token);
        strcat(param->outputDir, type_svg);

        // printf("New output dir: %s\n", param->outputDir);
        return param->outputDir;
    }

    if (param->nameQryFile[0] == '/') {
        param->nameQryFile++;
    }

    char *qry_token = strtok(param->nameQryFile, tok);
    char *new = (char *)malloc(strlen(geo_token) + strlen(qry_token) + 2);

    char *index = strrchr(param->nameQryFile, '/');
    index++;
    strcpy(param->nameQryFile, index);
    // printf("nome qry %s\n", param->nameQryFile);

    strcpy(new, geo_token);
    strcat(new, under);
    strcat(new, qry_token);

    strcat(param->outputDir, separator);
    strcat(param->outputDir, new);
    strcat(param->outputDir, type_svg);

    free(new);
    return param->outputDir;
}

char *getQryPath(Parameters p) {
    ParamL *param = (ParamL *)p;

    return param->nameQryFile;
}

char *buildFilePath(char *directory, char *fileName) {
    // printf("\n--- BUILD FILE PATH ---\n");
    // printf("Dir: %s - File Name: %s\n", directory, fileName);
    char separator[] = "/";
    char *result = malloc(strlen(directory) + strlen(fileName) + 5);
    // printf("Last digit %c\n", directory[aux-1]);

    strcpy(result, directory);
    strcat(result, separator);
    strcat(result, fileName);

    return result;
}

FILE *loadFile(char *path) {
    // printf("\n--- LOAD FILE ---\n");
    // printf("Path Arq: %s\n", path);
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

void freeParam(Parameters p) {
    ParamL *param = (ParamL *)p;

    free(param->inputDir);
    free(param->outputDir);
    free(param->nameGeoFile);
    free(param->nameQryFile);
    free(param);
}

