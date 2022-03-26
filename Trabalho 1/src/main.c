#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system.h"
#include "files.h"
#include "list.h"

void main(int argc, char **argv) {
    char var[100];
    printf("main1\n");
    Parameters param = createParameters(argc, argv);

    printf("main2\n");
    char *pathGeo = makePathGeoFile(param);

    printf("main3\n");
    char *geoFile = loadFile(pathGeo);

    printf("main4\n");
    if (geoFile == NULL){
        printf("Geo File NULO\n");
        return;
    }

    printf("----> %s\n", geoFile);
    Lista teste = criaLista();
    FILE * geo_source = fopen(geoFile, "rb"); //geoFile contem o path do arquivo geo
    while (fscanf(geoFile, "%s", var) != -1){
        printf("%s\n", var);
        insereFim(teste, var);
    }
    getFirst(teste);
}