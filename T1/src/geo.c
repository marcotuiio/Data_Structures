#include "geo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"
#include "line.h"
#include "list.h"
#include "rectangle.h"
#include "svg.h"
#include "text.h"

void buildGeometricForms(FILE *arq, char *svgoutput, FILE *qry, int existe) {
    printf("\nInicio Build GeoForms\n");
    Lista listRETANGULO = criaLista();
    Lista listCIRCULO = criaLista();
    Lista listTEXTO = criaLista();
    Lista listLINHA = criaLista();

    while (!feof(arq)) {
        char infos[10][200];
        char *eptr = NULL;

        fscanf(arq, "%s", *infos);

        if (strcmp(infos[0], "c") == 0) {
            Circle1 circle = criaCirc();
            Item item = buildCircle(arq, circle, *infos, eptr);
            insereFim(listCIRCULO, item);

        } else if (strcmp(infos[0], "r") == 0) {
            Rectangle1 rectangle = criaRec();
            Item item = buildRectangle(arq, rectangle, *infos, eptr);
            insereFim(listRETANGULO, item);

        } else if (strcmp(infos[0], "t") == 0) {
            Text1 text = criaTxt();
            Item item = buildText(arq, text, *infos, eptr);
            insereFim(listTEXTO, item);

        } else if (strcmp(infos[0], "l") == 0) {
            Line1 line = criaLinha();
            Item item = buildLine(arq, line, *infos, eptr);
            insereFim(listLINHA, item);
        }
    }

    fclose(arq);

    if (existe == 1) {
        char *svgpuro = (char*)malloc(strlen(svgoutput));
        strcpy(svgpuro, svgoutput);
        svgpuro = strtok(svgpuro, "_");
        strcat(svgpuro, ".svg");
        writeSvg(listRETANGULO, listCIRCULO, listTEXTO, listLINHA, svgpuro, qry, 0);
        writeSvg(listRETANGULO, listCIRCULO, listTEXTO, listLINHA, svgoutput, qry, 1);
        free(svgpuro);

    } else {
        writeSvg(listRETANGULO, listCIRCULO, listTEXTO, listLINHA, svgoutput, qry, 0);
    }

    removeAll(listRETANGULO);
    removeAll(listCIRCULO);
    removeAll(listLINHA);
    removeAll(listTEXTO);

    free(listRETANGULO);
    free(listCIRCULO);
    free(listLINHA);
    free(listTEXTO);
}
