#include "geo.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "text.h"
#include "tree.h"

void readGeo(char *bedGeo, Tree my_tree) {
    FILE *geo = openGeo(bedGeo);
    char tipo[5];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (strcmp(tipo, "c") == 0) {
            Info circle = criaCirc();
            buildCircle(geo, circle);
            Tree circleNode = createTree();
            setInfo(circleNode, circle);

        } else if (strcmp(tipo, "r") == 0) {
            Info rect = criaRec();
            buildRectangle(geo, rect);
            Tree rectNode = createTree();
            setInfo(rectNode, rect);

        } else if (strcmp(tipo, "l") == 0) {
            Info line = criaLinha();
            buildLine(geo, line);
            Tree lineNode = createTree();
            setInfo(lineNode, line);

        } else if (strcmp(tipo, "t") == 0) {
            Info text = criaTxt();
            buildText(geo, text);
            Tree textNode = createTree();
            setInfo(textNode, text);
        }
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