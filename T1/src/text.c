#include "text.h"

struct txt {
    char type[3];
    int id;
    double x;
    double y;
    char corp[15];
    char corb[15];
    char anchor[3];
    char text[100];
    char textaux[100];
};
typedef struct txt Texto;

Text1 criaTxt() {
    Texto *new_txt = calloc(1, sizeof(Texto));
    return new_txt;
}

Item buildText(FILE *arq, Text1 txt, char *infos, char *eptr) {
    // printf("\nInicio Build Text\n");
    Texto *Text = (Texto *)txt;

    strcpy(Text->type, infos);

    fscanf(arq, "%s", infos);
    Text->id = atoi(infos);

    fscanf(arq, "%s", infos);
    Text->x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    Text->y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(Text->corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(Text->corp, infos);

    fscanf(arq, "%s", infos);
    strcpy(Text->anchor, infos);

    fscanf(arq, "%[^\n]", infos);
    strcpy(Text->text, infos);

    strcpy(Text->textaux, Text->text);

    // printf("txtaux %s\n", Text->textaux);
    // printf("\nid %d\n", Text->id);
    // printf("x %lf\n", Text->x);
    // printf("y %lf\n", Text->y);
    // printf("a %s\n", Text->anchor);
    // printf("corb %s\n", Text->corb);
    // printf("corp %s\n", Text->corp);
    // printf("txt %s\n", Text->text);

    return Text;
}

int getTxtID(Item t) {
    Texto *txt = (Texto *)t;

    return txt->id;
}

double getTxtX(Item t) {
    Texto *txt = (Texto *)t;

    return txt->x;
}

double getTxtY(Item t) {
    Texto *txt = (Texto *)t;

    return txt->y;
}

char *getTxtFILL(Item t) {
    Texto *txt = (Texto *)t;

    return txt->corp;
}

char *getTxtEDGE(Item t) {
    Texto *txt = (Texto *)t;

    return txt->corb;
}

char *getTxtANCHOR(Item t) {
    Texto *txt = (Texto *)t;
    // printf("get anchor %s\n", txt->anchor);
    // strcpy(txt->anchor, strtok(txt->anchor, " "));
    // printf("get anchor %s\n", strtok(txt->anchor, " "));

    return txt->anchor;
}

char *getTxtTEXT(Item t) {
    Texto *txt = (Texto *)t;
    // printf("get txt %s\n", txt->text);

    return txt->text;
}

char *getTxtTEXTAUX(Item t) {
    Texto *txt = (Texto *)t;
    // printf("get txt %s\n", txt->textaux);

    return txt->textaux;
}

void settxtFILL(Item t, char *new_corp) {
    Texto *txt = (Texto *)t;

    strcpy(txt->corp, new_corp);
}

void settxtEDGE(Item t, char *new_corb) {
    Texto *txt = (Texto *)t;

    strcpy(txt->corb, new_corb);
}

void settxtX(Item t, double dx) {
    Texto *txt = (Texto *)t;

    txt->x = getTxtX(t) + dx;
}

void settxtY(Item t, double dy, int n) {
    Texto *txt = (Texto *)t;

    txt->y = getTxtY(t) + n * dy;
}