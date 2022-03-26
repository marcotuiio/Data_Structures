#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "system.h"
#include "files.h"

struct parameters {
    char *outputDir;
    char *inputDir;
    char *nameGeoFile;
    char *nameQryFile;
};

typedef struct parameters ParamL;

Parameters *setParameters(int argc, char** argv, Parameters p) {
    printf("\nInicio set param\n");
    ParamL *param = (ParamL*) p;

    printf("argc = %d\n", argc);
    if(argc < 0) {
        return NULL;
    }

    for(int index=1; index<argc; index++) {
        
        if(!strcmp(argv[index], "-e")) {
            strcpy(param->inputDir, argv[index+1]);
            printf("Dir Argument: %s\n",param->inputDir);

        } else if(!strcmp(argv[index], "-f")) {
            strcpy(param->nameGeoFile, argv[index+1]);

        } else if(!strcmp(argv[index], "-q")) {
            strcpy(param->nameQryFile, argv[index+1]);

        } else if(!strcmp(argv[index], "-o")) {
            strcpy(param->outputDir, argv[index+1]);

        }
    }
    return param;
}

Parameters *createParameters(int argc, char** argv) {
    printf("\nInicio create param\n");
    ParamL *param = calloc(1, sizeof(ParamL));

    param->outputDir = malloc(sizeof(char*));
    param->inputDir = malloc(200);
    param->nameGeoFile = malloc(sizeof(char*));
    param->nameQryFile = malloc(sizeof(char*));

    strcpy(param->inputDir, getcwd(NULL, 0));
    strcpy(param->nameGeoFile, "geo.geo");

    return setParameters(argc, argv, param);
}

char *makePathGeoFile(Parameters p) {
    printf("\nInicio path geo file\n");
    ParamL *param = (ParamL*) p;

    return buildFilePath(param->inputDir, param->nameGeoFile);
}