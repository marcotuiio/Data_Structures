#include "svg.h"

#include "rb_tree.h"
#include "digraph.h"
#include "infos.h"
#include "system.h"

void writeSvg(FILE *svg, Rb t, Digraph g) {
    percursoProfundidade(t, writeRb, svg);

    killSvg(svg);
}

void writeRb(InfoRb i, void *aux) {
    FILE *svg = aux;
    if (i) {
        double x = getXNode(i);
        double y = getYNode(i);
        double w = getWNode(i);
        double h = getHNode(i);
        char cep[30], sw[10], cfill[20], cstrk[20];
        strcpy(cep, getCep(i));
        strcpy(sw, getSW(i));
        strcpy(cfill, getCFill(i));
        strcpy(cstrk, getCStrk(i));

        fprintf(svg, RECTANGLE, cep, x, y, w, h, cfill, cstrk, sw);
    }
}

void animatedPath(Digraph g, FILE *svg, Node *path, char *id) {
    fprintf(svg, "<path d=m ");

    for (int i = 0; i < getGraphSize(g); i++) {
        fprintf(svg, "\"%lf\" \"%lf\", ", getXVertex(getNodeInfo(g, path[i])), getYVertex(getNodeInfo(g, path[i])));
    }
    fprintf(svg, "id=\"%s\" />", id);

    fprintf(svg, "<circle cx="" cy="" r=\"%lf\" fill=\"%s\">", 5.0, "red");
    fprintf(svg, "\t<animateMotion dur=\"%s\" repeatCount=\"%s\">", "6s", "indefinite");
    fprintf(svg, "\t\t<mpath xlink:href=\"#%s\"/>", id);
    fprintf(svg, "\t</animateMotion>");
    fprintf(svg, "</circle>");
}

FILE *createSvg(char *bsdSvg) {
    FILE *svg = fopen(bsdSvg, "w");
    if (!svg) {
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