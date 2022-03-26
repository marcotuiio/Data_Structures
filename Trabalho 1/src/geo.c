#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "geo.h"

struct circle {
    char type;
    int id;
    double x;
    double y;
    double radius;
    char *corp;
    char *corb;
};
typedef struct circle GCircle;

struct text {
    char type;
    int id;
    float x;
    float y;
    char anchor;
    char *corp;
    char *corb;
    char *text;
};
typedef struct text GText;

struct line {
    char type;
    int id;
    float initX;
    float initY;
    float finalX;
    float finalY;
    char *color;
};
typedef struct line GLine;

struct rectangle {
    char type;
    int id;
    float x;
    float y;
    float width;
    float height;
    char *corb;
    char *corp;
};
typedef struct rectangle GRectangle;

Item buildRectangle(FILE *arq, char infos[], char *eptr){
    printf("\nInicio Build Rectangle\n");
    GRectangle *rectangle = calloc(1, sizeof(GRectangle*));

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

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->corb = infos;

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    rectangle->corp = infos;

    strcpy(infos, "");

    return rectangle;
}

Item buildCircle(FILE *arq, char infos[], char *eptr){
    printf("\nInicio Build Circle\n");
    GCircle *circle = calloc(1, sizeof(GCircle*));

    circle->type = infos[0];

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    circle->id = atoi(infos);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    circle->x = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    circle->y = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    circle->radius = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    circle->corb = infos;

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    circle->corp = infos;

    strcpy(infos, "");

    return circle;
}

Lista buildGeometricForms(FILE *arq) {
    printf("\nInicio Build GeoForms\n");
    Lista list = criaLista();

    while(!feof(arq)) {
        char infos[10];
        char *eptr;
        fscanf(arq, "%s", infos);

         if (infos[0] == 'c' && infos[1] == NULL) {
            Item item = buildCircle(arq, infos, eptr);
            insereInicio(list, item);

         }else if(infos[0] == 'r' && infos[1] == NULL) {
            Item item = buildRectangle(arq, infos, eptr);
            insereInicio(list, item);
         }
    }

}