#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "text.h"

struct txt{
    char type[1];
    int id;
    double x;
    double y;
    double anchor;
    char corp[15];
    char corb[15];
    char text[100];
};
typedef struct txt Texto;

Text1 criaTxt(){
    Texto *new_txt = calloc(1, sizeof(Texto));
    return new_txt;
}

Item buildText(FILE *arq, Text1 txt, char *infos[], char *eptr){
    printf("\nInicio Build Text\n");
    Texto *Text = (Texto*) txt;

    strcpy(Text->type, infos);

    fscanf(arq, "%s", infos);
    Text->id = atoi(infos);

    fscanf(arq, "%s", infos);
    Text->x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    Text->y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    Text->anchor = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(Text->corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(Text->corp, infos);

    fscanf(arq, "%s", infos);
    strcpy(Text->text, infos);

    printf("\nid %d\n", Text->id);
    printf("x %lf\n", Text->x);
    printf("y %lf\n", Text->y);
    printf("a %lf\n", Text->anchor);
    printf("corb %s\n", Text->corb);
    printf("corp %s\n", Text->corp);
    printf("txt %s\n", Text->text);

    return Text;
}

int getTxtID(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->id;
}

double getTxtX(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->x;
}

double getTxtY(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->y;
}

double getTxtANCHOR(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->anchor;
}

char *getTxtFILL(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->corp;
}

char *getTxtEDGE(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->corb;
}

char *getTxtTEXT(Text1 t){
    Texto *txt = (Texto*) t;

    return txt->text;
}