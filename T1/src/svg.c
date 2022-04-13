#include "svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "qry.h"

FILE *createSvg(char *svg_path) {
    printf("--- INICIO CREATE SVG ---\n");

    FILE *svg = fopen(svg_path, "w");

    printf("\nCriado com Sucesso: %s\n\n", svg_path);
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    return svg;
}

void killSvg(FILE *svg) {
    printf("\n--- INICIO KILL SVG ---\n");
    if (!svg) {
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha, char *diroutput, FILE *qry, int existe) {
    printf("\n--- INICIO WRITE SVG ---\n");

    FILE *svg = createSvg(diroutput);
    char *diraux = malloc(strlen(diroutput));
    strcpy(diraux, diroutput);

    for (Cell auxC1 = getFirst(rect); auxC1 != NULL; auxC1 = getNext(rect, auxC1)) {
        Item auxI1 = getInfo(auxC1);
        drawRectangle(svg, auxI1);
    }

    for (Cell auxC2 = getFirst(circ); auxC2 != NULL; auxC2 = getNext(circ, auxC2)) {
        Item auxI2 = getInfo(auxC2);
        drawCircle(svg, auxI2);
    }

    for (Cell auxC3 = getFirst(txt); auxC3 != NULL; auxC3 = getNext(txt, auxC3)) {
        Item auxI3 = getInfo(auxC3);
        drawText(svg, auxI3);
    }

    for (Cell auxC4 = getFirst(linha); auxC4 != NULL; auxC4 = getNext(linha, auxC4)) {
        Item auxI4 = getInfo(auxC4);
        drawLine(svg, auxI4);
    }

    if (existe == 1) {
        readComands(qry, rect, circ, linha, txt, svg, diraux);
    }

    killSvg(svg);

}

void drawCircle(FILE *svg, Item circ) {
    // printf("--- INICIO DRAW CIRC ---\n");
    int id;
    double x, y, radius;
    char fill[15], stroke[15];

    id = getCircID(circ);
    x = getCircX(circ);
    y = getCircY(circ);
    radius = getCircRADIUS(circ);
    strcpy(fill, getCircFILL(circ));
    strcpy(stroke, getcircEDGE(circ));

    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", id, x, y, radius, stroke, fill);
}

void drawRectangle(FILE *svg, Item rect) {
    // printf("--- INICIO DRAW RECT ---\n");
    int id;
    double x, y, height, width;
    char fill[15], stroke[15];

    id = getRectID(rect);
    x = getRectX(rect);
    y = getRectY(rect);
    height = getRectHEIGHT(rect);
    width = getRectWIDTH(rect);
    strcpy(fill, getRectFILL(rect));
    strcpy(stroke, getRectEDGE(rect));

    fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" />\n", id, x, y, width, height, stroke, fill);
}

void drawLine(FILE *svg, Item linha) {
    // printf("--- INICIO DRAW LINE ---\n");
    int id;
    double x1, y1, x2, y2;
    char stroke[15];

    id = getLineID(linha);
    x1 = getLineX(linha);
    y1 = getLineY(linha);
    x2 = getLineFINALX(linha);
    y2 = getLineFINALY(linha);
    strcpy(stroke, getLineCOLOR(linha));

    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"50%%\" />\n", id, x1, y1, x2, y2, stroke);
}

void drawText(FILE *svg, Item txt) {
    // printf("--- INICIO DRAW TEXT ---\n");
    int id;
    char aux_anchor[1];
    double x, y;
    char text[100], fill[15], stroke[15], anchor[10];

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
    strcpy(text, getTxtTEXT(txt));
    strcpy(fill, getTxtFILL(txt));
    strcpy(stroke, getTxtEDGE(txt));

    strcpy(aux_anchor, getTxtANCHOR(txt));
    if (strcmp(aux_anchor, "i") == 0) {
        strcpy(anchor, "start");
    } else if (strcmp(aux_anchor, "m") == 0) {
        strcpy(anchor, "middle");
    } else if (strcmp(aux_anchor, "f") == 0) {
        strcpy(anchor, "end");
    }

    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" >\"%s\"</text>\n", id, x, y, anchor, stroke, fill, text);
}
