#include "infos.h"

typedef struct StDetails {
    char sw[10], cfill[15], cstrk[15];
} StDetails;

typedef struct StInfoNode {
    double x, y, w, h;
    void* detail;  
} StInfoNode;

typedef struct StInfoEdge {
    double vm, cmp;
    char ldir[50], lesq[50];
} StInfoEdge;

void* createDetails() {
    StDetails *details = calloc(1, sizeof(StDetails));
    strcpy(details->sw, "1.0px");
    strcpy(details->cfill, "none");
    strcpy(details->cstrk, "black");

    return details;
}

InfoNode createInfoNode(char *cep, double x, double y, double w, double h, void* detail) {
    StInfoNode *info = calloc(1, sizeof(StInfoNode));
    info->x = x;
    info->y = y;
    info->w = w;
    info->h = h;
    info->detail = detail;

    return info;
}
InfoEdge createInfoEdge(double vm, double cmp, char *ldir, char *lesq) {
    StInfoEdge *info = calloc(1, sizeof(StInfoEdge));
    info->vm = vm;
    info->cmp = cmp;
    strcpy(info->ldir, ldir);
    strcpy(info->lesq, lesq);

    return info;
}

char* getSw(void* detail) {
    StDetails *details = detail;
    return details->sw;
}

void setSW(void* detail, char *sw) {
    StDetails *details = detail;
    strcpy(details->sw, sw);
}

char* getCFill(void* detail) {
    StDetails *details = detail;
    return details->cfill;
}

void setCFill(void* detail, char *cfill) {
    StDetails *details = detail;
    strcpy(details->cfill, cfill);
}

char* getCStrk(void* detail) {
    StDetails *details = detail;
    return details->cstrk;
}

void setCStrk(void* detail, char *cstrk) {
    StDetails *details = detail;
    strcpy(details->cstrk, cstrk);
}

double getXNode(InfoNode info) {
    StInfoNode *i = info;
    return i->x;
}

double getYNode(InfoNode info) {
    StInfoNode *i = info;
    return i->y;
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