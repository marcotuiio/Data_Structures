#include "rectangle.h"
#include "list.h"

struct rect {
    char type[3];
    int id;
    double x;
    double y;
    double width;
    double height;
    char corb[15];
    char corp[15];
};
typedef struct rect Retangulo;

Info criaRec() {
    Retangulo *new_rec = calloc(1, sizeof(Retangulo));
    return new_rec;
}

void buildRectangle(FILE *geo, Info r, Lista my_list) {
    // printf("\nInicio Build Rectangle\n");
    Retangulo *rectangle = r;

    strcpy(rectangle->type, "r");

    fscanf(geo, "%d", &rectangle->id);
    fscanf(geo, "%lf", &rectangle->x);
    fscanf(geo, "%lf", &rectangle->y);
    fscanf(geo, "%lf", &rectangle->width);
    fscanf(geo, "%lf", &rectangle->height);
    fscanf(geo, "%s", rectangle->corb);
    fscanf(geo, "%s", rectangle->corp);

    insereFim(my_list, rectangle, rectangle->x, rectangle->y);
    // printf("\nid %d\n", rectangle->id);
    // printf("x %lf\n", rectangle->x);
    // printf("y %lf\n", rectangle->y);
    // printf("w %lf\n", rectangle->width);
    // printf("h %lf\n", rectangle->height);
    // printf("corb %s\n", rectangle->corb);
    // printf("corp %s\n", rectangle->corp);
}

int getRectID(Info r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->id;
}

double getRectX(Info r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->x;
}

double getRectY(Info r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->y;
}

double getRectWIDTH(Info r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->width;
}

double getRectHEIGHT(Info r) {
    Retangulo *rect = (Retangulo *)r;  

    return rect->height;
}

char *getRectFILL(Info r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->corp;
}

char *getRectEDGE(Info r) {
    Retangulo *rect = (Retangulo *)r;

    return rect->corb;
}

void setrectFILL(Info r, char *new_corp) {
    Retangulo *rect = (Retangulo *)r;

    strcpy(rect->corp, new_corp);
}

void setrectEDGE(Info r, char *new_corb) {
    Retangulo *rect = (Retangulo *)r;

    strcpy(rect->corb, new_corb);
}

void setrectX(Info r, double dx) {
    Retangulo *rect = (Retangulo *)r;

    rect->x = getRectX(r) + dx;
}

void setrectY(Info r, double dy, int n) {
    Retangulo *rect = (Retangulo *)r;

    rect->y = getRectY(r) + n * dy;
}