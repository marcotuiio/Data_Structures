#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"
#include "list.h"

struct circ{
    char type;
    int id;
    double x;
    double y;
    double radius;
    char corp[15];
    char corb[15];
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
    fscanf(arq, "%s", infos );
    strcpy(circle->corb, infos);
    //circle->corb = infos;

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    strcpy(circle->corp, infos);
    //circle->corp = infos;

    strcpy(infos, "");

    printf("\nid %d\n", circle->id);
    printf("x %lf\n", circle->x);
    printf("y %lf\n", circle->y);
    printf("r %lf\n", circle->radius);
    printf("corb %s\n", circle->corb);
    printf("corp %s\n", circle->corp);

    return circle;
}

int getCircID(Circle1 c){
    Circulo *circ = (Circulo*) c;

    return circ->id;
}

double getCircX(Circle1 c){
    Circulo *circ = (Circulo*) c;

    return circ->x;
}

double getCircY(Circle1 c){
    Circulo *circ = (Circulo*) c;

    return circ->y;
}

double getCircRADIUS(Circle1 c){
    Circulo *circ = (Circulo*) c;

    return circ->radius;
}

char *getCircFILL(Circle1 c){
    Circulo *circ = (Circulo*) c;

    return circ->corp;
}

char *getcircEDGE(Circle1 c){
    Circulo *circ = (Circulo*) c;

    return circ->corb;
}