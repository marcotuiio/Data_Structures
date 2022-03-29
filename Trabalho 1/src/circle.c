#include <stdio.h>
#include <stdlib.h>

#include "circle.h"
#include "list.h"

struct circ{
    char type;
    int id;
    double x;
    double y;
    double radius;
    char *corp;
    char *corb;
};
typedef struct circ Circulo;

Circle1 criaCirc(){
    Circulo *new_circ = calloc(1, sizeof(Circulo*));
    return new_circ;
}

Item buildCircle(FILE *arq, Circle1 circ, char infos[], char *eptr){
    printf("\nInicio Build Circle\n");
    Circulo *circle = (Circulo*) circ;

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

int getCircID(Circle1 r){
    Circulo *circ = (Circulo*) r;

    return circ->id;
}

float getCircX(Circle1 r){
    Circulo *circ = (Circulo*) r;

    return circ->x;
}

float getCircY(Circle1 r){
    Circulo *circ = (Circulo*) r;

    return circ->y;
}

float getCircRADIUS(Circle1 r){
    Circulo *circ = (Circulo*) r;

    return circ->radius;
}

char getCircFILL(Circle1 r){
    Circulo *circ = (Circulo*) r;

    return circ->corp;
}

char getcircEDGE(Circle1 r){
    Circulo *circ = (Circulo*) r;

    return circ->corb;
}