#include "svg.h"

#include "circle.h"
#include "line.h"
#include "list.h"
#include "qry.h"
#include "rectangle.h"
#include "system.h"
#include "text.h"

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha, FILE *svg, int existe) {
    //printf("\n--- INICIO WRITE SVG ---\n");

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
        drawText(svg, auxI3, existe);
    }

    for (Cell auxC4 = getFirst(linha); auxC4 != NULL; auxC4 = getNext(linha, auxC4)) {
        Item auxI4 = getInfo(auxC4);
        drawLine(svg, auxI4);
    }
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

    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", id, x, y, radius, stroke, fill);
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

    fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", id, x, y, width, height, stroke, fill);
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

    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" />\n", id, x1, y1, x2, y2, stroke);
}

void drawText(FILE *svg, Item txt, int e) {
    // printf("--- INICIO DRAW TEXT ---\n");
    int id;
    char aux_anchor[1];
    double x, y;
    char text[100], fill[15], stroke[15], anchor[10];

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
    if (e == 1) {
        strcpy(text, getTxtTEXTAUX(txt));
    } else {
        strcpy(text, getTxtTEXT(txt));
    }
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
    // printf("\nid %d\n", id);
    // printf("x %lf\n", x);
    // printf("y %lf\n", y);
    // printf("a %s\n", anchor);
    // printf("corb %s\n", stroke);
    // printf("corp %s\n", fill);
    // printf("txt %s\n", text);

    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"60%%\" >%s</text>\n", id, x, y, anchor, stroke, fill, text);
}
