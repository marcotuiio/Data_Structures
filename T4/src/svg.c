#include "svg.h"

#include "avl_tree.h"
#include "infos.h"
#include "system.h"

void writeSvg(FILE *svg, Avl t, Digraph g) {
    traversePreOrder(t, writeAvl, svg);
    // percursoProfundidade(t, writeAux, svg);

    killSvg(svg);
}

void writeAvl(InfoAvl i, void *aux) {
    FILE *svg = aux;
    double x = getXNode(i);
    double y = getYNode(i);
    double w = getWNode(i);
    double h = getHNode(i);
    char cep[30], sw[10], cfill[15], cstrk[15];
    strcpy(cep, getCep(i));
    strcpy(sw, getSw(i));
    strcpy(cfill, getCFill(i));
    strcpy(cstrk, getCStrk(i));

    fprintf(svg, RECTANGLE, cep, x, y, w, h, cfill, cstrk, sw);
}

// void drawCircle(FILE *svg, void *circ) {
//     int id;
//     double x, y, r;
//     char fill[15], stroke[15];

//     id = getId(circ);
//     x = getX(circ);
//     y = getY(circ);
//     r = getR(circ);
//     strcpy(fill, getFill(circ));
//     strcpy(stroke, getStroke(circ));

//     fprintf(svg, CIRCLE, id, x, y, r, stroke, fill);
// }

// void drawLine(FILE *svg, void *linha) {
//     int id;
//     double x1, y1, x2, y2;
//     char stroke[15];

//     id = getId(linha);
//     x1 = getX(linha);
//     y1 = getY(linha);
//     x2 = getX2(linha);
//     y2 = getY2(linha);
//     strcpy(stroke, getStroke(linha));

//     fprintf(svg, LINE, id, x1, y1, x2, y2, stroke);
// }

// void drawText(FILE *svg, void *txt) {
//     int id;
//     char aux_anchor[3];
//     double x, y;
//     char text[100], fill[15], stroke[15], anchor[10];

//     id = getId(txt);
//     x = getX(txt);
//     y = getY(txt);
//     strcpy(fill, getFill(txt));
//     strcpy(stroke, getStroke(txt));

//     strcpy(aux_anchor, getAnchor(txt));
//     if (!strcmp(aux_anchor, "i")) {
//         strcpy(anchor, "start");
//     } else if (!strcmp(aux_anchor, "m")) {
//         strcpy(anchor, "middle");
//     } else if (!strcmp(aux_anchor, "f")) {
//         strcpy(anchor, "end");
//     }

//     strcpy(text, getText(txt));

//     fprintf(svg, TEXT, id, x, y, anchor, stroke, fill, text);
// }

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