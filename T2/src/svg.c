#include "svg.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "system.h"
#include "text.h"

void writeSvg(char *bsdSvg, Tree my_tree) {
    // printf("\n--- INICIO WRITE SVG ---\n");
    FILE *svg = createSvg(bsdSvg);
    Node my_root = getRoot(my_tree);
    // printf("\n size %d\n", getSize(my_tree));

    postOrderSVG(my_root, svg);

    killSvg(svg);
}

void postOrderSVG(Node root, FILE *svg) {
    Info my_info;

    if (root == NULL) {
        return;
    }

    postOrderSVG(getLeft(root), svg);
    postOrderSVG(getCenter(root), svg);
    postOrderSVG(getRight(root), svg);
    my_info = getInfo(root);

    if (!getRemovedStatus(root)) {

        switch (getCtrl(root)) {
            case 1:
                drawCircle(svg, my_info);
                break;
            case 2:
                drawRectangle(svg, my_info);
                break;
            case 3:
                drawLine(svg, my_info);
                break;
            case 4:
                drawText(svg, my_info);
                break;

            default:
                break;
        }
    }
}

void drawCircle(FILE *svg, Info circ) {
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

void drawRectangle(FILE *svg, Info rect) {
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

void drawLine(FILE *svg, Info linha) {
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

void drawText(FILE *svg, Info txt) {
    // printf("--- INICIO DRAW TEXT ---\n");
    int id;
    char aux_anchor[3];
    double x, y;
    char text[100], fill[15], stroke[15], anchor[10];

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
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

    strcpy(text, getTxtTEXT(txt));

    // printf("\nid %d\n", id);
    // printf("x %lf\n", x);
    // printf("y %lf\n", y);
    // printf("a %s\n", anchor);
    // printf("corb %s\n", stroke);
    // printf("corp %s\n", fill);
    // printf("txt %s\n", text);

    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"60%%\" >%s</text>\n", id, x, y, anchor, stroke, fill, text);
}

FILE *createSvg(char *bsdSvg) {
    // printf("--- INICIO CREATE SVG ---\n");
    FILE *svg = fopen(bsdSvg, "w");
    if (svg == NULL) {
        printf("ERRO AO CRIAR SVG\n");
        exit(1);
    }

    // printf("\nCriado com Sucesso: %s\n", svg_path);
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    return svg;
}

void killSvg(FILE *svg) {
    // printf("\n--- INICIO ENCERRAR SVG ---\n");
    if (!svg) {
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}