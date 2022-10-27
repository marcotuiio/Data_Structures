#include "geo.h"

void readGeo(char *bedGeo, Digraph d) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "c")) {
            void *circle = newShape();
            setCircle(geo, d, circle);

        } else if (!strcmp(tipo, "r")) {
            void *rect = newShape();
            setRectangle(geo, d, rect);

        } else if (!strcmp(tipo, "l")) {
            void *line = newShape();
            setLine(geo, d, line);

        } else if (!strcmp(tipo, "t")) {
            void *text = newShape();
            setText(geo, d, text);
        }
        strcpy(tipo, " ");
    }
    fclose(geo);
}

FILE *openGeo(char *bedGeo) {
    FILE *geo = fopen(bedGeo, "r");
    if (geo == NULL) {
        printf("ERRO NA CRIAÇÃO DO GEO\n");
        exit(1);
    }
    return geo;
}