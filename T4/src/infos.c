#include "infos.h"

typedef struct StDetails {
    char sw[15], cfill[15], cstrk[15];
} StDetails;

typedef struct StQuadra {
    char cep[30];
    double x, y, w, h;
    StDetails *detail;
} StQuadra;

typedef struct StInfoEdge {
    double vm, cmp;
    char ldir[30], lesq[30], nome[30];
} StInfoEdge;

void *createDetails() {
    StDetails *details = calloc(1, sizeof(StDetails));
    strcpy(details->sw, "zzzzzzzzz");
    strcpy(details->cfill, "zzzzzzzzz");
    strcpy(details->cstrk, "zzzzzzzzz");

    return details;
}

void *getDetails(InfoRb info) {
    StQuadra *quadra = info;
    return quadra->detail;
}

InfoRb createInfoRb(char *cep, double x, double y, double w, double h, void *detail) {
    StQuadra *info = calloc(1, sizeof(StQuadra));
    StDetails *details = detail;
    strcpy(info->cep, cep);
    info->x = x;
    info->y = y;
    info->w = w;
    info->h = h;
    info->detail = details;

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

char *getSW(InfoRb info) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    return details->sw;
}

void setSW(void *detail, char *sw) {
    StDetails *details = detail;
    strcpy(details->sw, sw);
}

char *getCFill(InfoRb info) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    return details->cfill;
}

void setCFill(void *detail, char *cfill) {
    StDetails *details = detail;
    strcpy(details->cfill, cfill);
}

char *getCStrk(InfoRb info) {
    StQuadra *quadra = info;
    StDetails *details = quadra->detail;
    return details->cstrk;
}

void setCStrk(void *detail, char *cstrk) {
    StDetails *details = detail;
    strcpy(details->cstrk, cstrk);
}

char* getCep(InfoRb info) {
    StQuadra *quadra = info;
    return quadra->cep;
}

double getXNode(InfoRb info) {
    StQuadra *i = info;
    return i->x;
}

double getYNode(InfoRb info) {
    StQuadra *i = info;
    return i->y;
}

double getWNode(InfoRb info) {
    StQuadra *i = info;
    return i->w;
}

double getHNode(InfoRb info) {
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

char *getNomeEdge(InfoEdge info) {
    StInfoEdge *i = info;
    return i->nome;
}