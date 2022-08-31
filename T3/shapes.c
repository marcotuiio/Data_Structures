#include "shapes.h"

struct fig {
    char type[3];               // geral
    int id;                     // geral
    double x, y;                // geral
    double w, h, energy;        // retangulo
    double r;                   // circulo
    double x2, y2;              // linha
    char anchor[3], text[100];  // texto
    char stroke[15], fill[15];  // geral
};
typedef struct fig Shapes;

Info newShape() {
    Shapes *new_shape = calloc(1, sizeof(Shapes));
    return new_shape;
}

void setCircle(FILE *geo, SRBTree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "c");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%lf", &shape->r);
    fscanf(geo, "%s", shape->stroke);
    fscanf(geo, "%s", shape->fill);

    shape->energy = -1;
    shape->w = shape->h = shape->x2 = shape->y2 = 0;
    strcpy(shape->anchor, "0");
    strcpy(shape->text, "0");

    insertSRB(t, shape->x, shape->y, 0, 0, 0, 0, shape);
}

void setRectangle(FILE *geo, SRBTree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "r");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%lf", &shape->w);
    fscanf(geo, "%lf", &shape->h);
    fscanf(geo, "%s", shape->stroke);
    fscanf(geo, "%s", shape->fill);
    shape->energy = 0;

    shape->r = shape->x2 = shape->y2 = 0;
    strcpy(shape->anchor, "0");
    strcpy(shape->text, "0");

    insertSRB(t, shape->x, shape->y, 0, 0, 0, 0, shape);
}

void setLine(FILE *geo, SRBTree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "l");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%lf", &shape->x2);
    fscanf(geo, "%lf", &shape->y2);
    fscanf(geo, "%s", shape->stroke);

    shape->energy = -1;
    shape->w = shape->h = shape->r = 0;
    strcpy(shape->anchor, "0");
    strcpy(shape->text, "0");
    strcpy(shape->fill, "none");

    insertSRB(t, shape->x, shape->y, 0, 0, 0, 0, shape);
}

void setText(FILE *geo, SRBTree t, Info f) {
    Shapes *shape = f;

    strcpy(shape->type, "t");

    fscanf(geo, "%d", &shape->id);
    fscanf(geo, "%lf", &shape->x);
    fscanf(geo, "%lf", &shape->y);
    fscanf(geo, "%s", shape->stroke);
    fscanf(geo, "%s", shape->fill);
    fscanf(geo, "%s", shape->anchor);
    fscanf(geo, "%[^\n]", shape->text);

    shape->energy = -1;
    shape->w = shape->h = shape->r = shape->x2 = shape->y2 = 0;

    insertSRB(t, shape->x, shape->y, 0, 0, 0, 0, shape);
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

double getLineLength(Info line) {
    double x1 = getX(line);
    double y1 = getY(line);
    double x2 = getX2(line);
    double y2 = getY2(line);
    double length;

    if (x1 == x2 && y1 != y2) {
        length = y2 - y1;
        return length;
    }
    if (x1 != x2 && y1 == y2) {
        length = x2 - x1;
        return length;
    }

    double auxX = pow((x2 - x1), 2);
    double auxY = pow((y2 - y1), 2);
    double auxL = auxX + auxY;

    length = sqrt(auxL);
    return length;
}

void setEnergy(Info rect, double energy) {
    Shapes *shape = rect;
    shape->energy = energy;
}

double getEnergy(Info rect) {
    Shapes *shape = rect;
    return shape->energy;
}

void setX(Info f, double dx) {
    Shapes *shape = f;
    shape->x = shape->x + dx;
}

void setY(Info f, double dy) {
    Shapes *shape = f;
    shape->y = shape->y + dy;
}

bool hitRectangle(Info i, double xt, double yt) {
    double rx = getX(i);
    double ry = getY(i);
    double w = getW(i);
    double h = getH(i);

    if (xt >= rx && xt <= (rx + w)) {  // Está dentro do retangulo
        if (yt >= ry && yt <= (ry + h)) {
            return true;
        }
    }
    return false;
}

bool insideNetAll(Info i, double xr, double yr, double w, double h) {
    bool inside = false;
    double x1 = getX(i);
    double y1 = getY(i);

    switch (getType(i)) {
        case 1:
            double r = getR(i);
            if ((xr + w) >= (x1 + r) && (xr) <= (x1 - r)) {
                if ((yr + h) >= (y1 + r) && (yr) <= (yr - r)) {
                    if (xr <= x1 && yr <= y1) {
                        inside = true;
                    }
                }
            }
            inside = false;
            break;

        case 2:
            break;

        case 3:
            double x2 = getX2(i);
            double y2 = getY2(i);
            if (((xr + w) >= (x1)) && ((yr + h) >= (y1))) {
                if (((xr + w) >= (x2)) && ((yr + h) >= (y2))) {
                    if (xr <= x1 && yr <= y1 && xr <= x2 && yr <= y2) {
                        inside = true;
                    }
                }
            }
            inside = false;
            break;

        case 4:
            if ((xr + w) >= (x1) && (yr + h) >= (y1)) {
                if (xr <= x1 && yr <= y1) {
                    inside = true;
                }
            }
            inside = false;

        default:
            break;
    }
    return inside;
}

bool fishInside(Info i, double x, double y, double w, double h) {
    bool inside = false;
    double x1 = getX(i);
    double y1 = getY(i);

    if (getType(i) == 1) {
        double r = getR(i);
        if ((x + w) >= (x1 + r) && (x) <= (x1 - r)) {
            if ((y + h) >= (y1 + r) && (y) <= (y - r)) {
                inside = true;
            }
        }
        inside = false;
    }
    return inside;
}