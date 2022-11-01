#include "infos.h"

typedef struct StDetails {
    char sw[10], cfill[15], cstrk[15];
} StDetails;

typedef struct StQuadra {
    char cep[30];
    double x, y, w, h;
    void *detail;
} StQuadra;

typedef struct StInfoEdge {
    double vm, cmp;
    char ldir[30], lesq[30], nome[30];
} StInfoEdge;

void *createDetails() {
    StDetails *details = calloc(1, sizeof(StDetails));
    strcpy(details->sw, "1.0px");
    strcpy(details->cfill, "none");
    strcpy(details->cstrk, "black");

    return details;
}

InfoAvl createInfoAvl(char *cep, double x, double y, double w, double h, void *detail) {
    StQuadra *info = calloc(1, sizeof(StQuadra));
    strcpy(info->cep, cep);
    info->x = x;
    info->y = y;
    info->w = w;
    info->h = h;
    info->detail = detail;

    return info;
}

InfoEdge createInfoEdge(double vm, double cmp, char *ldir, char *lesq, char *nomeEdge) {
    StInfoEdge *info = calloc(1, sizeof(StInfoEdge));
    info->vm = vm;
    info->cmp = cmp;
    strcpy(info->ldir, ldir);  // se nao tiver nennhuma quadra = "-"
    strcpy(info->lesq, lesq);  // se nao tiver nennhuma quadra = "-"
    strcpy(info->nome, nomeEdge);

    return info;
}

char *getSw(InfoAvl info) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    return details->sw;
}

void setSW(InfoAvl info, char *sw) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    strcpy(details->sw, sw);
}

char *getCFill(InfoAvl info) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    return details->cfill;
}

void setCFill(InfoAvl info, char *cfill) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    strcpy(details->cfill, cfill);
}

char *getCStrk(InfoAvl info) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    return details->cstrk;
}

void setCStrk(InfoAvl info, char *cstrk) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    strcpy(details->cstrk, cstrk);
}

char* getCep(InfoAvl info) {
    StQuadra *quadra = info;
    return quadra->cep;
}

double getXNode(InfoAvl info) {
    StQuadra *i = info;
    return i->x;
}

double getYNode(InfoAvl info) {
    StQuadra *i = info;
    return i->y;
}

double getWNode(InfoAvl info) {
    StQuadra *i = info;
    return i->w;
}

double getHNode(InfoAvl info) {
    StQuadra *i = info;
    return i->h;
}

double getVMEdge(InfoEdge info) {
    StInfoEdge *i = info;
    return i->vm;
}

double getCMPEdge(InfoEdge info) {
    StInfoEdge *i = info;
    return i->cmp;
}

char *getLdirEdge(InfoEdge info) {
    StInfoEdge *i = info;
    return i->ldir;
}

char *getLesqEdge(InfoEdge info) {
    StInfoEdge *i = info;
    return i->lesq;
}