#include "geo.h"

void readGeo(char *bedGeo, Tree my_tree) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "c")) {
            Info circle = newShape();
            setCircle(geo, my_tree, circle);

        } else if (!strcmp(tipo, "r")) {
            Info rect = newShape();
            setRectangle(geo, my_tree, rect);

        } else if (!strcmp(tipo, "l")) {
            Info line = newShape();
            setLine(geo, my_tree, line);

        } else if (!strcmp(tipo, "t")) {
            Info text = newShape();
            setText(geo, my_tree, text);
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