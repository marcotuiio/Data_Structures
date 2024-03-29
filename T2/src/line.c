#include "line.h"

#include "tree.h"

struct line {
    char type[3];
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char color[15];
    double protec;
};
typedef struct line Linha;

Info criaLinha() {
    Linha *new_line = calloc(1, sizeof(Linha));
    return new_line;
}

void buildLine(FILE *geo, Info l, Tree root) {
    // printf("\nInicio Build Line\n");
    Linha *line = l;

    strcpy(line->type, "l");

    fscanf(geo, "%d", &line->id);
    fscanf(geo, "%lf", &line->x1);
    fscanf(geo, "%lf", &line->y1);
    fscanf(geo, "%lf", &line->x2);
    fscanf(geo, "%lf", &line->y2);
    fscanf(geo, "%s", line->color);
    line->protec = 50.00;

    insertTree(root, getRoot(root), line->x1, line->y1, line, 3);  // line ctrl = 3;

    // printf("\nid %d\n", line->id);
    // printf("x %lf\n", line->x1);
    // printf("y %lf\n", line->y1);
    // printf("x %lf\n", line->x2);
    // printf("y %lf\n", line->y2);
    // printf("corb %s\n", line->color);
}

void replicateLine(Tree t, Info base_l, Info new_l, double dx, double dy, int id) {
    Linha *line = base_l;
    Linha *new_line = new_l;

    new_line->id = id;
    new_line->x1 = line->x1 + dx;
    new_line->y1 = line->y1 + dy;
    new_line->x2 = line->x2 + dx;
    new_line->y2 = line->y2 + dy;
    strcpy(new_line->color, line->color);
    new_line->protec = line->protec;

    insertTree(t, getRoot(t), new_line->x1, new_line->y1, new_line, 3);
}

int getLineID(Info l) {
    Linha *line = (Linha *)l;

    return line->id;
}

double getLineX(Info l) {
    Linha *line = (Linha *)l;

    return line->x1;
}

double getLineY(Info l) {
    Linha *line = (Linha *)l;

    return line->y1;
}

double getLineFINALX(Info l) {
    Linha *line = (Linha *)l;

    return line->x2;
}

double getLineFINALY(Info l) {
    Linha *line = (Linha *)l;

    return line->y2;
}

char *getLineCOLOR(Info l) {
    Linha *line = (Linha *)l;

    return line->color;
}

void setProtecLine(Info l, double reduc) {
    Linha *line = l;

    line->protec = line->protec - reduc;
}

double getLinePROTEC(Info l) {
    Linha *line = l;

    return line->protec;
}

double getLineArea(Info l) {
    Linha *line = l;
    double len = getLineLenght(line->x1, line->y1, line->x2, line->y2);

    double a = 0.1 * len;
    return a;
}

void freeLine(Info l) {
    Linha *line = l;

    free(line);
}

double getLineLenght(double x1, double y1, double x2, double y2) {
    double lenght;

    if (x1 == x2 && y1 != y2) {
        lenght = y2 - y1;
        return lenght;
    }
    if (x1 != x2 && y1 == y2) {
        lenght = x2 - x1;
        return lenght;
    }

    double auxX = (x2 - x1) * (x2 - x1);
    double auxY = (y2 - y1) * (y2 - y1);
    double auxL = auxX + auxY;

    lenght = sqroot(auxL);
    return lenght;
}

double sqroot(double num) {
    double root = num / 3;
    int i;
    if (num <= 0) return 0;
    for (i = 0; i < 64; i++) {
        root = (root + num / root) / 2;
    }
    return root;
}