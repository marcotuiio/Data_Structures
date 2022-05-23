#include "circle.h"
#include "tree.h"

struct circ {
    char type[3];
    int id;
    double x;
    double y;
    double radius;
    char corp[15];
    char corb[15];
    double protec;
};
typedef struct circ Circulo;

Info criaCirc() {
    Circulo *new_circ = calloc(1, sizeof(Circulo));
    return new_circ;
}

void buildCircle(FILE *geo, Info c, Tree root) {
    // printf("\nInicio Build Circle\n");
    Circulo *circle = c;
    
    strcpy(circle->type, "c");

    fscanf(geo, "%d", &circle->id);
    fscanf(geo, "%lf", &circle->x);
    fscanf(geo, "%lf", &circle->y);
    fscanf(geo, "%lf", &circle->radius);
    fscanf(geo, "%s", circle->corb);
    fscanf(geo, "%s", circle->corp);
    circle->protec = 60.00;

    insertTree(root, getRoot(root), circle->x, circle->y, circle, 1); //circ ctrl = 1;
    
    // printf("\nid %d\n", circle->id);
    // printf("x %lf\n", circle->x);
    // printf("y %lf\n", circle->y);
    // printf("r %lf\n", circle->radius);
    // printf("corb %s\n", circle->corb);
    // printf("corp %s\n", circle->corp);
}

int getCircID(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->id;
}

double getCircX(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->x;
}

double getCircY(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->y;
}

double getCircRADIUS(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->radius;
}

char *getCircFILL(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->corp;
}

char *getcircEDGE(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->corb;
}

void setcircFILL(Info c, char *new_corp) {
    Circulo *circ = (Circulo *)c;

    strcpy(circ->corp, new_corp);
}

void setcircEDGE(Info c, char *new_corb) {
    Circulo *circ = (Circulo *)c;

    strcpy(circ->corb, new_corb);
}

void setcircX(Info c, double dx) {
    Circulo *circ = (Circulo *)c;

    circ->x = getCircX(c) + dx;
}

void setcircY(Info c, double dy) {
    Circulo *circ = (Circulo *)c;

    circ->y = getCircY(c) + dy;
}

void freeCirc(Info c) {
    Circulo *circ = c;

    free(circ);
}