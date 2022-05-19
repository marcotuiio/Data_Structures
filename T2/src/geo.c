#include "geo.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "text.h"
#include "tree.h"

void readGeo(char *bedGeo, Tree my_tree) {  // FAZER GEO RETORNAR UMA ARVORE ???/
    FILE *geo = openGeo(bedGeo);
    char tipo[5];

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (strcmp(tipo, "c") == 0) {
            Info circle = criaCirc();
            buildCircle(geo, circle, my_tree);

        } else if (strcmp(tipo, "r") == 0) {
            Info rect = criaRec();
            buildRectangle(geo, rect, my_tree);

        } else if (strcmp(tipo, "l") == 0) {
            Info line = criaLinha();
            buildLine(geo, line, my_tree);

        } else if (strcmp(tipo, "t") == 0) {
            Info text = criaTxt();
            buildText(geo, text, my_tree);
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