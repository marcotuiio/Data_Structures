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
        Item aux = getFirst(rect);
        
        drawRectangle(svg, aux);
        
    }

    if (circ){
        printf("--- INICIO if circ ---\n");
        Item aux = getFirst(circ);

        drawCircle(svg, aux);
    }

    if (txt){
        printf("--- INICIO if txt ---\n");
        Item aux = getFirst(txt);
        
        drawText(svg, aux);
    }

    if (linha){
        printf("--- INICIO if linha ---\n");
        Item aux = getFirst(linha);

        drawLine(svg, aux);
    }
    
    killSvg(svg);
}

void drawCircle(FILE * svg, Circle1 circ){
    printf("--- INICIO DRAW CIRC ---\n");
    int id;
    double x, y, radius;
    char fill[15], stroke[15];

    id = getCircID(circ);
    x = getCircX(circ);
    y = getCircY(circ);
    radius = getCircRADIUS(circ);
    strcpy(fill, getRectFILL(circ));
    strcpy(stroke, getRectEDGE(circ));

    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", id, x, y, radius, stroke, fill);
}

void drawRectangle(FILE * svg, Rectangle1 rect){
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

void drawLine(FILE * svg, Line1 linha){
    printf("--- INICIO DRAW LINE ---\n");
    int id;
    double x1, y1, x2, y2;
    char stroke[15];

    id = getLineID(linha);
    x1 = getLineX(linha);
    y1 = getLineY(linha);
    x2 = getLineFINALX(linha);
    y2 = getLineFINALY(linha);
    strcpy(stroke, getRectEDGE(linha));

    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"50%%\" />\n", id, x1, y1, x2, y2, stroke);
}

void drawText(FILE * svg, Text1 txt){
    printf("--- INICIO DRAW TEXT ---\n");
    int id;
    double x, y, anchor;
    char text[50], fill[15], stroke[15];

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
    strcpy(text, getRectFILL(txt));
    strcpy(fill, getRectFILL(txt));
    strcpy(stroke, getRectEDGE(txt));

    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" >\"%s\"</>\n", id, x, y, anchor, stroke, fill, text);
}

