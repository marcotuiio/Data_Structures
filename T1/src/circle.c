#include "circle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct circ {
    char type[1];
    int id;
    double x;
    double y;
    double radius;
    char corp[15];
    char corb[15];
};
typedef struct circ Circulo;

Circle1 criaCirc() {
    Circulo *new_circ = calloc(1, sizeof(Circulo));
    return new_circ;
}

Item buildCircle(FILE *arq, Circle1 circ, char *infos, char *eptr) {
    // printf("\nInicio Build Circle\n");
    Circulo *circle = (Circulo *)circ;

    strcpy(circle->type, infos);

    fscanf(arq, "%s", infos);
    circle->id = atoi(infos);

    fscanf(arq, "%s", infos);
    circle->x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    circle->y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    circle->radius = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(circle->corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(circle->corp, infos);

    // printf("\nid %d\n", circle->id);
    // printf("x %lf\n", circle->x);
    // printf("y %lf\n", circle->y);
    // printf("r %lf\n", circle->radius);
    // printf("corb %s\n", circle->corb);
    // printf("corp %s\n", circle->corp);

    return circle;
}

int getCircID(Circle1 c) {
    Circulo *circ = (Circulo *)c;

    return circ->id;
}

double getCircX(Circle1 c) {
    Circulo *circ = (Circulo *)c;

    return circ->x;
}

double getCircY(Circle1 c) {
    Circulo *circ = (Circulo *)c;

    return circ->y;
}

double getCircRADIUS(Circle1 c) {
    Circulo *circ = (Circulo *)c;

    return circ->radius;
}

char *getCircFILL(Circle1 c) {
    Circulo *circ = (Circulo *)c;

    return circ->corp;
}

char *getcircEDGE(Circle1 c) {
    Circulo *circ = (Circulo *)c;

    return circ->corb;
}

void setcircFILL(Circle1 c, char *new_corp) {
    Circulo *circ = (Circulo *)c;

    strcpy(circ->corp, new_corp);
}

void setcircEDGE(Circle1 c, char *new_corb) {
    Circulo *circ = (Circulo *)c;

    strcpy(circ->corb, new_corb);
}

void setcircX(Circle1 c, double dx) {
    Circulo *circ = (Circulo *)c;

    circ->x = getCircX(c) + dx;
}

void setcircY(Circle1 c, double dy, int n) {
    Circulo *circ = (Circulo *)c;

    circ->y = getCircY(c) + n * dy;
}