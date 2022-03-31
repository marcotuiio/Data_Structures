#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "list.h"

FILE *createSvg(char *svg_path){

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

    if(!svg){
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}

void writeSvg(Lista rect, Lista circ, Lista txt, Lista linha){
    //FILE * svg = createSvg("/home/marcotuiio/Documents/ED/Trabalho 1/src/");
    FILE *svg = fopen("a.svg", "w");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    if (rect){
        for(Rectangle1 aux = getFirst(rect); aux; aux = getNext(rect, aux)){
            drawRectangle(svg, aux);
        }
    }

    if (circ){
        for(Circle1 aux = getFirst(circ); aux; aux = getNext(circ, aux)){
            drawCircle(svg, aux);
        }
    }

    if (txt){
        for(Text1 aux = getFirst(txt); aux; aux = getNext(txt, aux)){
            drawText(svg, aux);
        }
    }

    if (linha){
        for(Line1 aux = getFirst(linha); aux; aux = getNext(linha, aux)){
            drawLine(svg, aux);
        }
    }
    
    killSvg(svg);
}

void drawCircle(FILE * svg, Circle1 circ){
    int id;
    float x, y, radius;
    char *fill, *stroke;

    id = getCircID(circ);
    x = getCircX(circ);
    y = getCircY(circ);
    radius = getCircRADIUS(circ);
    fill = getCircFILL(circ);
    stroke = getcircEDGE(circ);

    fprintf(svg, "\t<circle id=\"%d\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\"/>\n", id, x, y, radius, stroke, fill);
}

void drawRectangle(FILE * svg, Rectangle1 rect){
    int id;
    float x, y, height, width;
    char *fill, *stroke;

    id = getRectID(rect);
    x = getRectX(rect);
    y = getRectY(rect);
    height = getRectHEIGHT(rect);
    width = getRectWIDTH(rect);
    fill = getRectFILL(rect);
    stroke = getcircEDGE(rect);

    fprintf(svg, "\t<rect id=\"%d\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" />\n", id, x, y, width, height, stroke, fill);
}

void drawLine(FILE * svg, Line1 linha){
    int id;
    float x1, y1, x2, y2;
    char *stroke;

    id = getLineID(linha);
    x1 = getLineX(linha);
    y1 = getLineY(linha);
    x2 = getLineFINALX(linha);
    y2 = getLineFINALY(linha);
    stroke = getLineCOLOR(linha);

    fprintf(svg, "\t<line id=\"%d\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" fill-opacity=\"50%%\" />\n", id, x1, y1, x2, y2, stroke);
}

void drawText(FILE * svg, Text1 txt){
    int id;
    float x, y, anchor;
    char *text, *fill, *stroke;

    id = getTxtID(txt);
    x = getTxtX(txt);
    y = getTxtY(txt);
    text = getTxtTEXT(txt);
    fill = getTxtFILL(txt);
    stroke = getTxtEDGE(txt);

    fprintf(svg, "\t<text id=\"%d\" x=\"%f\" y=\"%f\" text-anchor=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" >\"%s\"</>\n", id, x, y, anchor, stroke, fill, text);
}

//killSvg(svg);

