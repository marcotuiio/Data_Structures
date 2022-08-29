#include "geo.h"

void readGeo(char *bedGeo, SRBTree t) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (!strcmp(tipo, "c")) {
            Info circle = newShape();
            setCircle(geo, t, circle);

        } else if (!strcmp(tipo, "r")) {
            Info rect = newShape();
            setRectangle(geo, t, rect);

        } else if (!strcmp(tipo, "l")) {
            Info line = newShape();
            setLine(geo, t, line);

        } else if (!strcmp(tipo, "t")) {
            Info text = newShape();
            setText(geo, t, text);
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