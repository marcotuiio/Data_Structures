#include "line.h"

struct line {
    char type[1];
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char color[15];
};
typedef struct line Linha;

Line1 criaLinha() {
    Linha *new_line = calloc(1, sizeof(Linha));
    return new_line;
}

Item buildLine(FILE *arq, Line1 l, char *infos, char *eptr) {
    // printf("\nInicio Build Line\n");
    Linha *line = (Linha *)l;

    strcpy(line->type, infos);

    fscanf(arq, "%s", infos);
    line->id = atoi(infos);

    fscanf(arq, "%s", infos);
    line->x1 = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    line->y1 = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    line->x2 = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    line->y2 = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(line->color, infos);

    // printf("\nid %d\n", line->id);
    // printf("x %lf\n", line->x1);
    // printf("y %lf\n", line->y1);
    // printf("x %lf\n", line->x2);
    // printf("y %lf\n", line->y2);
    // printf("corb %s\n", line->color);

    return line;
}

int getLineID(Line1 l) {
    Linha *line = (Linha *)l;

    return line->id;
}

double getLineX(Line1 l) {
    Linha *line = (Linha *)l;

    return line->x1;
}

double getLineY(Line1 l) {
    Linha *line = (Linha *)l;

    return line->y1;
}

double getLineFINALX(Line1 l) {
    Linha *line = (Linha *)l;

    return line->x2;
}

double getLineFINALY(Line1 l) {
    Linha *line = (Linha *)l;

    return line->y2;
}

char *getLineCOLOR(Line1 l) {
    Linha *line = (Linha *)l;

    return line->color;
}

void setlineCOLOR(Line1 l, char *new_color) {
    Linha *line = (Linha *)l;

    strcpy(line->color, new_color);
}

void setlineX(Line1 l, double dx) {
    Linha *line = (Linha *)l;
    double aux = getLineY(l);

    line->x1 = aux + dx;
}

void setlineY(Line1 l, double dy, int n) {
    Linha *line = (Linha *)l;
    double aux = getLineY(l);

    line->y1 = aux + n * dy;
}

void setlineFinalX(Line1 l, double dx) {
    Linha *line = (Linha *)l;
    double aux = getLineFINALX(l);

    line->x2 = aux + dx;
}

void setlineFinalY(Line1 l, double dy, int n) {
    Linha *line = (Linha *)l;
    double aux = getLineFINALY(l);

    line->y2 = aux + n * dy;
}