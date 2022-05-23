#include "text.h"
#include "tree.h"

struct txt {
    char type[3];
    int id;
    double x;
    double y;
    char corp[15];
    char corb[15];
    char anchor[3];
    char text[100];
};
typedef struct txt Texto;

Info criaTxt() {
    Texto *new_txt = calloc(1, sizeof(Texto));
    return new_txt;
}

void buildText(FILE *geo, Info t, Tree root) {
    // printf("\nInicio Build Text\n");
    Texto *txt = t;

    strcpy(txt->type, "t");

    fscanf(geo, "%d", &txt->id);
    fscanf(geo, "%lf", &txt->x);
    fscanf(geo, "%lf", &txt->y);
    fscanf(geo, "%s", txt->corb);
    fscanf(geo, "%s", txt->corp);
    fscanf(geo, "%s", txt->anchor);
    fscanf(geo, "%[^\n]", txt->text);

    insertTree(root, getRoot(root), txt->x, txt->y, txt, 4);  // txt ctrl = 4;
    
    // printf("\nid %d\n", txt->id);
    // printf("x %lf\n", txt->x);
    // printf("y %lf\n", txt->y);
    // printf("a %s\n", txt->anchor);
    // printf("corb %s\n", txt->corb);
    // printf("corp %s\n", txt->corp);
    // printf("txt %s\n", txt->text);
}

int getTxtID(Info t) {
    Texto *txt = (Texto *)t;

    return txt->id;
}

double getTxtX(Info t) {
    Texto *txt = (Texto *)t;

    return txt->x;
}

double getTxtY(Info t) {
    Texto *txt = (Texto *)t;

    return txt->y;
}

char *getTxtFILL(Info t) {
    Texto *txt = (Texto *)t;

    return txt->corp;
}

char *getTxtEDGE(Info t) {
    Texto *txt = (Texto *)t;

    return txt->corb;
}

char *getTxtANCHOR(Info t) {
    Texto *txt = (Texto *)t;
    // printf("get anchor %s\n", txt->anchor);

    return txt->anchor;
}

char *getTxtTEXT(Info t) {
    Texto *txt = (Texto *)t;
    // printf("get txt %s\n", txt->text);

    return txt->text;
}

void settxtFILL(Info t, char *new_corp) {
    Texto *txt = (Texto *)t;

    strcpy(txt->corp, new_corp);
}

void settxtEDGE(Info t, char *new_corb) {
    Texto *txt = (Texto *)t;

    strcpy(txt->corb, new_corb);
}

void settxtX(Info t, double dx) {
    Texto *txt = (Texto *)t;

    txt->x = getTxtX(t) + dx;
}

void settxtY(Info t, double dy, int n) {
    Texto *txt = (Texto *)t;

    txt->y = getTxtY(t) + n * dy;
}

void freeTxt(Info t) {
    Texto *txt = t;

    free(txt);
}