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
#include "qry.h"

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
    char *diraux = (char*)malloc(strlen(svgoutput) + 20);
    strcpy(diraux, svgoutput);

    if (existe == 1) {
        char *svgpuro = (char*)malloc(strlen(svgoutput));
        strcpy(svgpuro, svgoutput);
        svgpuro = strtok(svgpuro, "_");
        strcat(svgpuro, ".svg");

        FILE *svg1 = createSvg(svgpuro);
        writeSvg(listRETANGULO, listCIRCULO, listTEXTO, listLINHA, svg1, 0);
        killSvg(svg1);

        FILE *arq_txt = createTxt(diraux);
        FILE *svgQry = createSvg(svgoutput);

        readComands(qry, listRETANGULO, listCIRCULO, listLINHA, listTEXTO, svgQry, arq_txt);
        killSvg(svgQry);
        free(svgpuro);

    } else {
        FILE *svg2 = createSvg(svgoutput);
        writeSvg(listRETANGULO, listCIRCULO, listTEXTO, listLINHA, svg2, 0);
        killSvg(svg2);
    }

    removeAll(listRETANGULO);
    removeAll(listCIRCULO);
    removeAll(listLINHA);
    removeAll(listTEXTO);

    free(listRETANGULO);
    free(listCIRCULO);
    free(listLINHA);
    free(listTEXTO);

    free(diraux);

}

FILE *createTxt(char *output) {
    char toRemove[] = ".";
    char toAdd[] = ".txt";
    char *txtdir = malloc(strlen(output) + 1);
    char *aux = strtok(output, toRemove);
    strcpy(txtdir, aux);
    strcat(txtdir, toAdd);

    FILE *txt = fopen(txtdir, "w");

    printf("\nCriado txt com sucesso: %s\n", txtdir);
    free(txtdir);

    return txt;
}

FILE *createSvg(char *svg_path) {
    printf("--- INICIO CREATE SVG ---\n");

    FILE *svg = fopen(svg_path, "w");

    printf("\nCriado com Sucesso: %s\n", svg_path);
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    return svg;
}

void killSvg(FILE *svg) {
    printf("\n--- INICIO ENCERRAR SVG ---\n");
    if (!svg) {
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}