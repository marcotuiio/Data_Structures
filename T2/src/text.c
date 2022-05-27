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
    double protec;
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
    txt->protec = 5.00;

    insertTree(root, getRoot(root), txt->x, txt->y, txt, 4);  // txt ctrl = 4;
    
    // printf("\nid %d\n", txt->id);
    // printf("x %lf\n", txt->x);
    // printf("y %lf\n", txt->y);
    // printf("a %s\n", txt->anchor);
    // printf("corb %s\n", txt->corb);
    // printf("corp %s\n", txt->corp);
    // printf("txt %s\n", txt->text);
}

void replicateTxt(Tree t, Info base_t, Info new_t, double dx, double dy, int id, FILE *txt) {
    Texto *text = base_t;
    Texto *new_txt = new_t;

    new_txt->id = id;
    new_txt->x = text->x + dx;
    new_txt->y = text->y + dy;
    strcpy(new_txt->corb, text->corp);
    strcpy(new_txt->corp, text->corb);
    strcpy(new_txt->anchor, text->anchor);
    strcpy(new_txt->text, text->text);
    new_txt->protec = 5.00;

    insertTree(t, getRoot(t), new_txt->x, new_txt->y, new_txt, 4);

    fprintf(txt, "Texto Base id = %d, x = %lf, y = %lf, corb = %s, corp = %s, text = %s\n", text->id, text->x, text->y, text->corb, text->corp, text->text);
    fprintf(txt, "Texto Replicado id = %d, x = %lf, y = %lf, corb = %s, corp = %s, text = %s\n", new_txt->id, new_txt->x, new_txt->y, new_txt->corb, new_txt->corp, new_txt->text);
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

void setProtecTxt(Info t, double reduc) {
    Texto *txt = t;

    txt->protec = txt->protec - reduc;
}

double getProtecTxt(Info t) {
    Texto *txt = t;

    return txt->protec;
}

void freeTxt(Info t) {
    Texto *txt = t;

    free(txt);
}