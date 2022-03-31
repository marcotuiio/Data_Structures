#include <stdio.h>
#include <stdlib.h>

#include "rectangle.h"
#include "list.h"

struct rect{
    char type;
    int id;
    float x;
    float y;
    float width;
    float height;
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
    fscanf(arq, "%d", infos);
    rectangle->id = atoi(infos);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    rectangle->x = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    rectangle->y = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    rectangle->width = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    rectangle->height = strtod(infos, &eptr);

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

    printf("id = %d\n", rect->id);
    return rect->id;
}

float getRectX(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->x;
}

float getRectY(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->y;
}

float getRectWIDTH(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->width;
}

float getRectHEIGHT(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->height;
}

char getRectFILL(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->corp;
}

char getRectEDGE(Rectangle1 r){
    Retangulo *rect = (Retangulo*) r;

    return rect->corb;
}