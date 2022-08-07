#include "shapes.h"

struct fig {
    char type[3];               // geral
    int id;                     // geral
    double x, y;                // geral
    double w, h;                // retangulo
    double r;                   // circulo
    double x2, y2;              // linha
    char anchor[3], text[100];  // texto
    char stroke[15], fill[15];  // geral
};
typedef struct fig Shapes;

Info newShape() {
    Shapes *new_form = calloc(1, sizeof(Shapes));
    return new_form;
}

void setCircle(FILE *geo, Tree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "c");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%lf", &shape->r);
    fscanf(geo, "%s", shape->stroke);
    fscanf(geo, "%s", shape->fill);

    shape->w = shape->h = shape->x2 = shape->y2 = 0;
    strcpy(shape->anchor, "0");
    strcpy(shape->text, "0");

    insertTree(t, shape, shape->x);
}

void setRectangle(FILE *geo, Tree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "r");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%lf", &shape->w);
    fscanf(geo, "%lf", &shape->h);
    fscanf(geo, "%s", shape->stroke);
    fscanf(geo, "%s", shape->fill);

    shape->r = shape->x2 = shape->y2 = 0;
    strcpy(shape->anchor, "0");
    strcpy(shape->text, "0");

    insertTree(t, shape, shape->x);
}

void setLine(FILE *geo, Tree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "l");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%lf", &shape->x2);
    fscanf(geo, "%lf", &shape->y2);
    fscanf(geo, "%s", shape->stroke);

    shape->w = shape->h = shape->r = 0;
    strcpy(shape->anchor, "0");
    strcpy(shape->text, "0");
    strcpy(shape->fill, "none");

    insertTree(t, shape, shape->x);
}

void setText(FILE *geo, Tree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "t");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%s", shape->stroke);
    fscanf(geo, "%s", shape->fill);
    fscanf(geo, "%s", shape->anchor);
    fscanf(geo, "%[^\n]", shape->text);

    shape->w = shape->h = shape->r = shape->x2 = shape->y2 = 0;

    insertTree(t, shape, shape->x);
}

int getType(Info f) {
    Shapes *shape = f;
    int type;
    if (!strcmp(shape->type, "c")) {
        type = 1;
    } else if (!strcmp(shape->type, "r")) {
        type = 2;
    } else if (!strcmp(shape->type, "l")) {
        type = 3;
    } else if (!strcmp(shape->type, "t")) {
        type = 4;
    }
    return type;
}

int getId(Info f) {
    Shapes *shape = f;
    return shape->id;
}

double getX(Info f) {
    Shapes *shape = f;
    return shape->x;
}

double getY(Info f) {
    Shapes *shape = f;
    return shape->y;
}

double getW(Info f) {
    Shapes *shape = f;
    return shape->w;
}

double getH(Info f) {
    Shapes *shape = f;
    return shape->h;
}

double getR(Info f) {
    Shapes *shape = f;
    return shape->r;
}

double getX2(Info f) {
    Shapes *shape = f;
    return shape->x2;
}

double getY2(Info f) {
    Shapes *shape = f;
    return shape->y2;
}

char *getStroke(Info f) {
    Shapes *shape = f;
    return shape->stroke;
}

char *getFill(Info f) {
    Shapes *shape = f;
    return shape->fill;
}

char *getAnchor(Info f) {
    Shapes *shape = f;
    return shape->anchor;
}

char *getText(Info f) {
    Shapes *shape = f;
    return shape->text;
}
