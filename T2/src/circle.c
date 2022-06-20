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

    insertTree(root, getRoot(root), circle->x, circle->y, circle, 1);  // circ ctrl = 1;

    // printf("\nid %d\n", circle->id);
    // printf("x %lf\n", circle->x);
    // printf("y %lf\n", circle->y);
    // printf("r %lf\n", circle->radius);
    // printf("corb %s\n", circle->corb);
    // printf("corp %s\n", circle->corp);
}

void replicateCirc(Tree t, Info base_c, Info new_c, double dx, double dy, int id) {
    Circulo *circ = base_c;
    Circulo *new_circ = new_c;

    new_circ->id = id;
    new_circ->x = circ->x + dx;
    new_circ->y = circ->y + dy;
    new_circ->radius = circ->radius;
    strcpy(new_circ->corb, circ->corp);
    strcpy(new_circ->corp, circ->corb);
    new_circ->protec = circ->protec;

    insertTree(t, getRoot(t), new_circ->x, new_circ->y, new_circ, 1);
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

char *getCircEDGE(Info c) {
    Circulo *circ = (Circulo *)c;

    return circ->corb;
}

void setProtecCirc(Info c, double reduc) {
    Circulo *circ = c;

    circ->protec = circ->protec - reduc;
}

double getCircPROTEC(Info c) {
    Circulo *circ = c;

    return circ->protec;
}

double getCircArea(Info c) {
    Circulo *circ = c;
    double a, r;
    r = circ->radius;

    a = pi * r * r;
    return a;
}

void freeCirc(Info c) {
    Circulo *circ = c;

    free(circ);
}