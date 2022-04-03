#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "line.h"

struct line {
    char type;
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char *color;
};
typedef struct line Linha;

Line1 criaLinha(){
    Linha *new_line = calloc(1, sizeof(Linha*));
    return new_line;
}

Item buildLine(FILE *arq, Line1 l, char infos[], char *eptr){
    printf("\nInicio Build Line\n");
    Linha *line = (Linha*) l;

    line->type = infos[0];

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->id = atoi(infos);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->x1 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->y1 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->x2 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->y2 = strtod(infos, &eptr);

    //printf("ta dando erro aqui?\n");
    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->color = infos;
    //printf("%s\n", line->color);


    strcpy(infos, "");

    return line;
}

int getLineID(Line1 l){
    Linha *line = (Linha*) l;

    return line->id;
}

double getLineX(Line1 l){
    Linha *line = (Linha*) l;

    return line->x1;
}

double getLineY(Line1 l){
    Linha *line = (Linha*) l;

    return line->y1;
}

double getLineFINALX(Line1 l){
    Linha *line = (Linha*) l;

    return line->x2;
}

double getLineFINALY(Line1 l){
    Linha *line = (Linha*) l;

    return line->y2;
}

char *getLineCOLOR(Line1 l){
    Linha *line = (Linha*) l;

    return line->color;
}