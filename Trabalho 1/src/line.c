#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "line.h"

struct line {
    char type;
    int id;
    float x1;
    float y1;
    float x2;
    float y2;
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
    fscanf(arq, "%d", infos);
    line->id = atoi(infos);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    line->x1 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    line->y1 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    line->x2 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%f", infos);
    line->y2 = strtod(infos, &eptr);

    strcpy(infos, "");
    fscanf(arq, "%s", infos);
    line->color = infos;

    strcpy(infos, "");

    return line;
}

int getLineID(Line1 l){
    Linha *line = (Linha*) l;

    return line->id;
}

float getLineX(Line1 l){
    Linha *line = (Linha*) l;

    return line->x1;
}

float getLineY(Line1 l){
    Linha *line = (Linha*) l;

    return line->y1;
}

float getLinex2(Line1 l){
    Linha *line = (Linha*) l;

    return line->x2;
}

float getLiney2(Line1 l){
    Linha *line = (Linha*) l;

    return line->y2;
}

char getLineCOLOR(Line1 l){
    Linha *line = (Linha*) l;

    return line->color;
}
