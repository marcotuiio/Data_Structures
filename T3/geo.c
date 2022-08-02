#include "geo.h"

#include "shapes.h"

void readGeo(char *bedGeo, Tree my_tree) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);
        // printf("tipo %s\n", tipo);

        if (!strcmp(tipo, "c")) {
            Info circle = newShape();
            setCircle(geo, circle);

        } else if (!strcmp(tipo, "r")) {
            Info rect = newShape();
            setRectangle(geo, rect);

        } else if (!strcmp(tipo, "l")) {
            Info line = newShape();
            setLine(geo, line);

        } else if (!strcmp(tipo, "t")) {
            Info text = newShape();
            setText(geo, text);
        }
        strcpy(tipo, " ");
    }
    fclose(geo);
}

FILE *openGeo(char *bedGeo) {
    // printf("\nbedGeo %s\n", bedGeo);
    FILE *geo = fopen(bedGeo, "r");
    if (geo == NULL) {
        printf("ERRO NA CRIAÇÃO DO GEO\n");
        exit(1);
    }
    return geo;
}