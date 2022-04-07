#include "rectangle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct rect {
    char type[1];
    int id;
    double x;
    double y;
    double width;
    double height;
    char corb[15];
    char corp[15];
};
typedef struct rect Retangulo;

Rectangle1 criaRec() {
    Retangulo *new_rec = calloc(1, sizeof(Retangulo));
    return new_rec;
}

Item buildRectangle(FILE *arq, Rectangle1 rec, char *infos[], char *eptr) {
    //printf("\nInicio Build Rectangle\n");
    Retangulo *rectangle = (Retangulo *)rec;

    strcpy(rectangle->type, infos);

    fscanf(arq, "%s", infos);
    rectangle->id = atoi(infos);

    fscanf(arq, "%s", infos);
    rectangle->x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    rectangle->y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    rectangle->width = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    rectangle->height = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(rectangle->corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(rectangle->corp, infos);

    // printf("\nid %d\n", rectangle->id);
    // printf("x %lf\n", rectangle->x);
    // printf("y %lf\n", rectangle->y);
    // printf("w %lf\n", rectangle->width);
    // printf("h %lf\n", rectangle->height);
    // printf("corb %s\n", rectangle->corb);
    // printf("corp %s\n", rectangle->corp);

    return rectangle;
}

int getRectID(Item r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->id;
}

double getRectX(Item r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->x;
}

double getRectY(Item r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->y;
}

double getRectWIDTH(Item r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->width;
}

double getRectHEIGHT(Item r) {
    Retangulo *rect = (Retangulo *)r;  // lista{ retangulo1(infos) retangulo2(infos) }

    return rect->height;
}

char *getRectFILL(Item r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->corp;
}

char *getRectEDGE(Item r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->corb;
}