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
    char ldir[30], lesq[30], nome[30], bloqName[30];
} StInfoEdge;

typedef struct StInfoVertex{
    double x, y;
    char nomeAux[30];
} StInfoVertex;

void *createDetails(char *sw, char *cfill, char *cstrk) {
    StDetails *details = calloc(1, sizeof(StDetails));
    strcpy(details->sw, sw);
    strcpy(details->cfill, cfill);
    strcpy(details->cstrk, cstrk);
    
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

InfoNode createInfoVertex(double x, double y, char *nome) {
    StInfoVertex *info = calloc(1, sizeof(StInfoVertex));
    info->x = x;
    info->y = y;
    strcpy(info->nomeAux, nome);

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

void setVMEdge(InfoEdge info, double vm) {
    StInfoEdge *i = info;
    i->vm = vm;
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

void setBloqNameEdge(InfoEdge info, char *bloqName) {
    StInfoEdge *i = info;
    strcpy(i->bloqName, bloqName);
}

char *getBloqNameEdge(InfoEdge info) {
    StInfoEdge *i = info;
    return i->bloqName;
}

double getXVertex(InfoNode info) {
    StInfoVertex *i = info;
    return i->x;
}

double getYVertex(InfoNode info) {
    StInfoVertex *i = info;
    return i->y;
}

char *getNomeVertex(InfoNode info) {
    StInfoVertex *i = info;
    return i->nomeAux;
}

bool insideQuadra(InfoRb info, double x, double y, double w, double h) {
    StQuadra *quadra = info;

    if ((x + w) >= (quadra->x + quadra->w)) {
        if ((y + h) >= (quadra->y + quadra->h)) {
            if (x <= quadra->x && y <= quadra->y) {
                return true;
            }
        }
    }
    return false;
}

bool insideEdge(double x, double y, double w, double h, double x1, double y1, double x2, double y2) {
    if (x + w >= x1 && x + w >= x2) {
        if (y + h >= y1 && y + h >= y2) {
            if (x <= x1 && x <= x2 && y <= y1 && y <= y2) {
                return true;
            }
        }
    }
    return false;
}