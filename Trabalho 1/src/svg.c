#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "list.h"

FILE *createSvg(char *svg_path){
    printf("--- INICIO CREATE SVG ---\n");
    FILE *svg = fopen(svg_path, "w");

    if(!svg){
        printf("Erro na criacao do SVG!!\n");
        free(svg_path);
        exit(1);
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    return svg;
}

void killSvg(FILE * svg){
    printf("--- INICIO KILL SVG ---\n");
    if(!svg){
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha){
    printf("\n--- INICIO WRITE SVG ---\n");
    //FILE * svg = createSvg("/home/marcotuiio/Documents/ED/Trabalho 1/src/");
    FILE *svg = fopen("a.svg", "w");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    if (rect){
        printf("--- INICIO if rect---\n");
        Item aux = getFirst(rect);
        while (aux != NULL){
            drawRectangle(svg, aux);
            aux = getNext(rect, aux);
        }
    }

    if (circ){
        printf("--- INICIO if circ ---\n");
        Item aux = getFirst(circ);
        while (aux != NULL){
            drawCircle(svg, aux);
            aux = getNext(circ, aux);
        }
    }

    if (txt){
        printf("--- INICIO if txt ---\n");
        Item aux = getFirst(txt);
        while (aux != NULL){
            drawText(svg, aux);
            aux = getNext(txt, aux);
        }
    }

    if (linha){
        printf("--- INICIO if linha ---\n");
        Item aux = getFirst(linha);
        while (aux != NULL){
            drawLine(svg, aux);
            aux = getNext(linha, aux);
        }
    }
    
    killSvg(svg);
}

void drawCircle(FILE * svg, Item circ){
    printf("--- INICIO DRAW CIRC ---\n");
    int id;
    double x, y, radius;
    char *fill, *stroke;

    id = getCircID(circ);
    x = getCircX(circ);
    y = getCircY(circ);
    radius = getCircRADIUS(circ);
    fill = getCircFILL(circ);
    stroke = getcircEDGE(circ);

    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", id, x, y, radius, stroke, fill);
}

void drawRectangle(FILE * svg, Item rect){
    printf("--- INICIO DRAW RECT ---\n");
    int id;
    double x, y, height, width;
    char *fill, *stroke;

    id = getRectID(rect);
    printf("\n%d\n", id);
    x = getRectX(rect);
    printf("%lf\n", x);
    y = getRectY(rect);
    printf("%lf\n", y);
    height = getRectHEIGHT(rect);
    printf("%lf\n", height);
    width = getRectWIDTH(rect);
    printf("%lf\n", width);
    fill = getRectFILL(rect);
    printf("%s\n", fill);
    stroke = getcircEDGE(rect);
    printf("%s\n", stroke);

    fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" />\n", id, x, y, width, height, stroke, fill);
}

void drawLine(FILE * svg, Item linha){
    printf("--- INICIO DRAW LINE ---\n");
    int id;
    double x1, y1, x2, y2;
    char *stroke;

    id = getLineID(linha);
    x1 = getLineX(linha);
    y1 = getLineY(linha);
    x2 = getLineFINALX(linha);
    y2 = getLineFINALY(linha);
    stroke = getLineCOLOR(linha);

    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"50%%\" />\n", id, x1, y1, x2, y2, stroke);
}

void drawText(FILE * svg, Item txt){
    printf("--- INICIO DRAW TEXT ---\n");
    int id;
    double x, y, anchor;
    char *text, *fill, *stroke;

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
    text = getTxtTEXT(txt);
    fill = getTxtFILL(txt);
    stroke = getTxtEDGE(txt);

    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" >\"%s\"</>\n", id, x, y, anchor, stroke, fill, text);
}

