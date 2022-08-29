#include "svg.h"

#include "shapes.h"
#include "system.h"

void writeSvg(char *bsdSvg, SRBTree t) {
    FILE *svg = createSvg(bsdSvg);

    percursoProfundidade(t, writeAux, svg);

    killSvg(svg);
}

void writeAux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    FILE *svg = aux;
    switch (getType(i)) {
        case 1:
            drawCircle(svg, i);
            break;

        case 2:
            drawRectangle(svg, i);
            break;

        case 3:
            drawLine(svg, i);
            break;

        case 4:
            drawText(svg, i);
            break;

        default:
            break;
    }
}

void drawCircle(FILE *svg, Info circ) {
    int id;
    double x, y, r;
    char fill[15], stroke[15];

    id = getId(circ);
    x = getX(circ);
    y = getY(circ);
    r = getR(circ);
    strcpy(fill, getFill(circ));
    strcpy(stroke, getStroke(circ));

    fprintf(svg, CIRCLE, id, x, y, r, stroke, fill);
}

void drawRectangle(FILE *svg, Info rect) {
    int id;
    double x, y, h, w;
    char fill[15], stroke[15];

    id = getId(rect);
    x = getX(rect);
    y = getY(rect);
    h = getH(rect);
    w = getW(rect);
    strcpy(fill, getFill(rect));
    strcpy(stroke, getStroke(rect));

    fprintf(svg, RECTANGLE, id, x, y, w, h, stroke, fill);
}

void drawLine(FILE *svg, Info linha) {
    int id;
    double x1, y1, x2, y2;
    char stroke[15];

    id = getId(linha);
    x1 = getX(linha);
    y1 = getY(linha);
    x2 = getX2(linha);
    y2 = getY2(linha);
    strcpy(stroke, getStroke(linha));

    fprintf(svg, LINE, id, x1, y1, x2, y2, stroke);
}

void drawText(FILE *svg, Info txt) {
    int id;
    char aux_anchor[3];
    double x, y;
    char text[100], fill[15], stroke[15], anchor[10];

    id = getId(txt);
    x = getX(txt);
    y = getY(txt);
    strcpy(fill, getFill(txt));
    strcpy(stroke, getStroke(txt));

    strcpy(aux_anchor, getAnchor(txt));
    if (!strcmp(aux_anchor, "i")) {
        strcpy(anchor, "start");
    } else if (!strcmp(aux_anchor, "m")) {
        strcpy(anchor, "middle");
    } else if (!strcmp(aux_anchor, "f")) {
        strcpy(anchor, "end");
    }

    strcpy(text, getText(txt));

    fprintf(svg, TEXT, id, x, y, anchor, stroke, fill, text);
}

FILE *createSvg(char *bsdSvg) {
    FILE *svg = fopen(bsdSvg, "w");
    if (svg == NULL) {
        printf("ERRO AO CRIAR SVG\n");
        exit(1);
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    return svg;
}

void killSvg(FILE *svg) {
    if (!svg) {
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}