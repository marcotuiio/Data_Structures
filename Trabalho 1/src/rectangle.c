#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rectangle.h"
#include "list.h"

struct rect{
    char type;
    int id;
    double x;
    double y;
    double width;
    double height;
    char *corb;
    char *corp;
};
typedef struct rect Retangulo;

Rectangle1 criaRec(){
    Retangulo *new_rec = calloc(1, sizeof(Retangulo*));
    return new_rec;
}

Item buildRectangle(FILE *arq, Rectangle1 rec, char infos[], char *eptr){
    printf("\nInicio Build Rectangle\n");
    Retangulo *rectangle = (Retangulo*) rec;

     rectangle->type = infos[0];

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->id = atoi(infos);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->x = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->y = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->width = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->height = strtod(infos, &eptr);

    //printf("deu arro aqui?\n");
    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->corb = infos;

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->corp = infos;

    strcpy(infos, "");

    return rectangle;
}

int getRectID(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->id;
}

double getRectX(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->x;
}

double getRectY(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->y;
}

double getRectWIDTH(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->width;
}

double getRectHEIGHT(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r; // lista{ retangulo1(infos) retangulo2(infos) }

    return rect->height;
}

char* getRectFILL(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->corp;
}

char* getRectEDGE(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->corb;
}