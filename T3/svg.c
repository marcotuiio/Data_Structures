#include "svg.h"

#include "system.h"
#include "shapes.h"

void writeSvg(char *bsdSvg, Tree my_tree) {
    FILE *svg = createSvg(bsdSvg);
    Node my_root = getRoot(my_tree);
    // printf("\n size %d\n", getSize(my_tree));

    preOrderSVG(my_root, svg);

    killSvg(svg);
}

void preOrderSVG(Node root, FILE *svg) {
    Info my_info;

    if (!root) {
        return;
    }

    if (!getRemovedStatus(root)) {
        my_info = getInfo(root);

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
    } else {
        // printf("\n--- REMOVED %p ---\n", root);
    }

    preOrderSVG(getLeft(root), svg);
    preOrderSVG(getCenter(root), svg);
    preOrderSVG(getRight(root), svg);
}

void drawCircle(FILE *svg, Info circ) {
    // printf("--- INICIO DRAW CIRC ---\n");
    int id;
    double x, y, radius;
    char fill[15], stroke[15];

    id = getId(circ);
    x = getX(circ);
    y = getY(circ);
    radius = getR(circ);
    strcpy(fill, getFill(circ));
    strcpy(stroke, getStroke(circ));

    fprintf(svg, CIRCLE, id, x, y, radius, stroke, fill);
}

void drawRectangle(FILE *svg, Info rect) {
    // printf("--- INICIO DRAW RECT ---\n");
    int id;
    double x, y, height, width;
    char fill[15], stroke[15];

    id = getId(rect);
    x = getX(rect);
    y = getY(rect);
    height = getH(rect);
    width = getW(rect);
    strcpy(fill, getFill(rect));
    strcpy(stroke, getStroke(rect));

    fprintf(svg, RECTANGLE, id, x, y, width, height, stroke, fill);
}

void drawLine(FILE *svg, Info linha) {
    // printf("--- INICIO DRAW LINE ---\n");
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

    fprintf(svg, TEXT, id, x, y, anchor, stroke, fill, text);
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