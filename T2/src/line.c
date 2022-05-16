#include "line.h"
#include "list.h"

struct line {
    char type[3];
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char color[15];
};
typedef struct line Linha;

Info criaLinha() {
    Linha *new_line = calloc(1, sizeof(Linha));
    return new_line;
}

void buildLine(FILE *geo, Info l, Lista my_list) {
    // printf("\nInicio Build Line\n");
    Linha *line = l;

    strcpy(line->type, "l");

    fscanf(geo, "%d", &line->id);
    fscanf(geo, "%lf", &line->x1);
    fscanf(geo, "%lf", &line->y1);
    fscanf(geo, "%lf", &line->x2);
    fscanf(geo, "%lf", &line->y2);
    fscanf(geo, "%s", line->color);

    insereFim(my_list, line, line->x1, line->y1);
    // printf("\nid %d\n", line->id);
    // printf("x %lf\n", line->x1);
    // printf("y %lf\n", line->y1);
    // printf("x %lf\n", line->x2);
    // printf("y %lf\n", line->y2);
    // printf("corb %s\n", line->color);

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

void setlineCOLOR(Info l, char *new_color) {
    Linha *line = (Linha *)l;

    strcpy(line->color, new_color);
}

void setlineX(Info l, double dx) {
    Linha *line = (Linha *)l;
    double aux = getLineY(l);

    line->x1 = aux + dx;
}

void setlineY(Info l, double dy, int n) {
    Linha *line = (Linha *)l;
    double aux = getLineY(l);

    line->y1 = aux + n * dy;
}

void setlineFinalX(Info l, double dx) {
    Linha *line = (Linha *)l;
    double aux = getLineFINALX(l);

    line->x2 = aux + dx;
}

void setlineFinalY(Info l, double dy, int n) {
    Linha *line = (Linha *)l;
    double aux = getLineFINALY(l);

    line->y2 = aux + n * dy;
}

double getLineLenght(Info l) {
    Linha *line = l;
    double x1, x2, y1, y2;
    double lenght;

    x1 = getLineX(line);
    x2 = getLineFINALX(line);
    y1 = getLineY(line);
    y2 = getLineFINALY(line);

    if (x1 == x2 && y1 != y2) {
        lenght = y2 - y1;
        return lenght;
    } 
    if (x1 != x2 && y1 == y2) {
        lenght = x2 - x1;
        return lenght;
    }

    double auxX = pow((x2 - x1), 2);
    double auxY = pow((y2 - y1), 2);

    lenght = sqrt(auxX + auxY);
    return lenght;
}