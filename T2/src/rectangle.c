#include "rectangle.h"
#include "tree.h"

struct rect {
    char type[3];
    int id;
    double x;
    double y;
    double width;
    double height;
    char corb[15];
    char corp[15];
    double protec;
};
typedef struct rect Retangulo;

Info criaRec() {
    Retangulo *new_rec = calloc(1, sizeof(Retangulo));
    return new_rec;
}

void buildRectangle(FILE *geo, Info r, Tree root) {
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
    rectangle->protec = 60.00;

    insertTree(root, getRoot(root), rectangle->x, rectangle->y, rectangle, 2);  // rect ctrl = 2;
    
    // printf("\nid %d\n", rectangle->id);
    // printf("x %lf\n", rectangle->x);
    // printf("y %lf\n", rectangle->y);
    // printf("w %lf\n", rectangle->width);
    // printf("h %lf\n", rectangle->height);
    // printf("corb %s\n", rectangle->corb);
    // printf("corp %s\n", rectangle->corp);
}

void replicateRect(Tree t, Info base_r, Info new_r, double dx, double dy, int id, FILE *txt) {
    Retangulo *rectangle = base_r;
    Retangulo *new_rectangle = new_r;

    new_rectangle->id = id;
    new_rectangle->x = rectangle->x + dx;
    new_rectangle->y = rectangle->y + dy;
    new_rectangle->width = rectangle->width;
    new_rectangle->height = rectangle->height;
    strcpy(new_rectangle->corb, rectangle->corp);
    strcpy(new_rectangle->corp, rectangle->corb);
    new_rectangle->protec = 60.00;

    insertTree(t, getRoot(t), new_rectangle->x, new_rectangle->y, new_rectangle, 2);
    
    fprintf(txt, "Retangulo Base id = %d, x = %lf, y = %lf, w = %lf, h = %lf, corb = %s, corp = %s\n", rectangle->id, rectangle->x, rectangle->y, rectangle->width, rectangle->height, rectangle->corb, rectangle->corp);
    fprintf(txt, "Retangulo Replicado id = %d, x = %lf, y = %lf, w = %lf, h = %lf, corb = %s, corp = %s\n", new_rectangle->id, new_rectangle->x, new_rectangle->y, new_rectangle->width, new_rectangle->height, new_rectangle->corb, new_rectangle->corp);
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

void setProtecRect(Info r, double reduc) {
    Retangulo *rect = r;

    rect->protec = rect->protec - reduc;
}

double getProtecRect(Info r) {
    Retangulo *rect = r;

    return rect->protec;
}

double getRectArea(Info r) {
    Retangulo *rect = r;
    double a, width, height;
    width = rect->x + rect->width;
    height = rect->y + rect->height;

    a = width * height;
    return a;
}

void freeRect(Info r) {
    Retangulo *rect = r;

    free(rect);
}