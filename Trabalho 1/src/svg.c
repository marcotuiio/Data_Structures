#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "list.h"

FILE *createSvg(char *svg_path){
    printf("--- INICIO CREATE SVG ---\n");
    FILE *svg = fopen(svg_path, "rw");

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
    //arrumar aqui, passar o outputDir
    FILE * svg = fopen("a.svg", "w");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    if (rect){
        printf("--- INICIO if rect---\n");
        Cell auxC1 = getFirst(rect);
        while (auxC1 != NULL){
            Item auxI1 = getInfo(auxC1);
            drawRectangle(svg, auxI1);
            auxC1 = getNext(rect, auxC1);
        }
    }

    if (circ){
        printf("--- INICIO if circ ---\n");
        Cell auxC2 = getFirst(circ);
        while (auxC2 != NULL){
            Item auxI2 = getInfo(auxC2);
            drawCircle(svg, auxI2);
            auxC2 = getNext(circ, auxC2);
        }
    }

    if (txt){
        printf("--- INICIO if txt ---\n");
        Cell auxC3 = getFirst(txt);
        while (auxC3 != NULL){
            Item auxI = getInfo(auxC3);
            drawText(svg, auxI);
            auxC3 = getNext(txt, auxC3);
        }
    }

    if (linha){
        printf("--- INICIO if linha ---\n");
        Cell auxC4 = getFirst(linha);
        while (auxC4 != NULL){
            Item auxI4 = getInfo(auxC4);
            drawLine(svg, auxI4);
            auxC4 = getNext(linha, auxC4);
        }
    }
    
    killSvg(svg);
    free(rect);
    free(circ);
    free(linha);
    free(txt);
}

void drawCircle(FILE * svg, Item circ){
    printf("--- INICIO DRAW CIRC ---\n");
    int id;
    double x, y, radius;
    char fill[15], stroke[15];

    id = getCircID(circ);
    x = getCircX(circ);
    y = getCircY(circ);
    radius = getCircRADIUS(circ);
    strcpy(fill, getCircFILL(circ));
    strcpy(stroke, getcircEDGE(circ));

    printf("\nid %d\n", id);
    printf("x %lf\n", x);
    printf("y %lf\n", y);
    printf("r %lf\n", radius);
    printf("fill %s\n", fill);

    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", id, x, y, radius, stroke, fill);
}

void drawRectangle(FILE * svg, Item rect){
    printf("--- INICIO DRAW RECT ---\n");
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

void drawLine(FILE * svg, Item linha){
    printf("--- INICIO DRAW LINE ---\n");
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

void drawText(FILE * svg, Item txt){
    printf("--- INICIO DRAW TEXT ---\n");
    int id;
    double x, y, anchor;
    char text[100], fill[15], stroke[15];

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
    anchor = getTxtANCHOR(txt);
    strcpy(text, getTxtTEXT(txt));
    strcpy(fill, getTxtFILL(txt));
    strcpy(stroke, getTxtEDGE(txt));

    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" >\"%s\"</>\n", id, x, y, anchor, stroke, fill, text);
}

