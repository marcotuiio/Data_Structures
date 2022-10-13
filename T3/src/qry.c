#include "qry.h"

struct aux1 {
    double e;
    FILE *txt;
};
typedef struct aux1 AUXE;

struct aux2 {
    int i;
    Info nau;
    double dx, dy;
    FILE *txt;
    SRBTree t;
};
typedef struct aux2 AUXMV;

struct aux3 {
    int i;
    char lado[4];
    double w, h, d, xr, yr;
    FILE *txt;
    FILE *svg;
    Info nau;
    SRBTree t;
};
typedef struct aux3 AUXLR;

struct aux4 {
    int i;
    char lado[4];
    double d, xt, yt;
    FILE *txt;
    FILE *svg;
    Info nau;
    SRBTree t;
};
typedef struct aux4 AUXD;

struct aux5 {
    double dx, dy, x, y, w, h;
    FILE *txt;
    SRBTree t;
};
typedef struct aux5 AUXMC;

void readQry(SRBTree t, char *bedQry, char *bsdSvgQry, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvgQry);
    char comando[6];

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (!strcmp(comando, "e")) {
            e(qry, txt, t);

        } else if (!strcmp(comando, "mv")) {
            mv(qry, txt, t);

        } else if (!strcmp(comando, "lr")) {
            lr(qry, txt, svg, t);

        } else if (!strcmp(comando, "d")) {
            d(qry, txt, svg, t);

        } else if (!strcmp(comando, "mc")) {
            mc(qry, txt, t);
        }
        strcpy(comando, " ");
    }
    writeSvg(svg, t);

    fprintf(txt, "\n\t\t\t|------ RESULTADOS FINAIS DA PESCARIA PIRATA ------|\n");
    percursoProfundidade(t, printResultados, txt);

    fclose(qry);
    fclose(txt);
}

FILE *openQry(char *bedQry) {
    FILE *qry = fopen(bedQry, "r");
    if (!qry) {
        printf("ERRO NA CRIAÇÃO DO QRY\n");
        exit(1);
    }
    return qry;
}

FILE *openTxt(char *bsdTxt) {
    FILE *txt = fopen(bsdTxt, "w");
    if (!txt) {
        printf("ERRO NA CRIAÇÃO DO TXT\n");
        exit(1);
    }
    return txt;
}

void find_idMV(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXMV *aux0 = aux;
    int id = aux0->i;

    if (i && getId(i) == id) {
        aux0->nau = i;
    }
}

void find_idLR(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXLR *aux0 = aux;
    int id = aux0->i;

    if (i && getId(i) == id) {
        aux0->nau = i;
    }
}

void find_idD(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXD *aux0 = aux;
    int id = aux0->i;

    if (getId(i) == id) {
        aux0->nau = i;
    }
}

void e(FILE *qry, FILE *txt, SRBTree t) {
    double e;

    fscanf(qry, "%lf", &e);

    fprintf(txt, "\n[*] e %lf \n", e);

    AUXE *aux = calloc(1, sizeof(AUXE));
    aux->e = e;
    aux->txt = txt;

    percursoProfundidade(t, e_aux, aux);
    free(aux);
}
void e_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXE *data = aux;
    FILE *txt = data->txt;
    double e = data->e;

    if (getType(i) == 2) {
        setEnergy(i, e);
        fprintf(txt, "\tAtribuida energia id = %d, x = %lf, y = %lf, e = %lf\n", getId(i), getX(i), getY(i), e);
    }
}

void mv(FILE *qry, FILE *txt, SRBTree t) {
    int i;
    double dx, dy;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%lf", &dx);
    fscanf(qry, "%lf", &dy);

    fprintf(txt, "\n[*] mv %d %lf %lf \n", i, dx, dy);

    AUXMV *aux = calloc(1, sizeof(AUXMV));
    aux->i = i;
    aux->nau = NULL;

    percursoProfundidade(t, find_idMV, aux);
    if (!aux->nau) {
        fprintf(txt, "\tNao foi possivel encontrar a figura id = %d\n", i);
        free(aux);
        return;
    }

    if (getType(aux->nau) == 2) {
        bool teste = energyDeslocamento(aux->nau, dx, dy);
        if (!teste) {
            fprintf(txt, "\tEnergia insuficiente para deslocar a nau id = %d\n", i);
            free(aux);
            return;
        }
    }

    Info old = removeSRB(t, getX(aux->nau), getY(aux->nau), 0, 0, 0, 0);
    fprintf(txt, "\tDeslocou id = %d, xi = %lf, yi = %lf, ", getId(old), getX(old), getY(old));
    setX(old, dx);
    setY(old, dy);
    fprintf(txt, "xf = %lf, yf = %lf\n", getX(old), getY(old));
    if (old) {
        if (getType(old) == 1) {
            insertSRB(t, getX(old), getY(old), getX(old) - getR(old), getY(old) - getR(old), getX(old) + getR(old), getY(old) + getR(old), old);
        } else if (getType(old) == 2) {
            insertSRB(t, getX(old), getY(old), getX(old), getY(old), getX(old) + getW(old), getY(old) + getH(old), old);
        } else if (getType(old) == 3) {
            double y_aux, y2_aux;
            setX2(old, dx);
            setY2(old, dy);
            findLineXY(&y_aux, &y2_aux, old);
            insertSRB(t, getX(old), getY(old), getX(old), y_aux, getX2(old), y2_aux, old);
        } else if (getType(old) == 4) {
            insertSRB(t, getX(old), getY(old), getX(old), getY(old), getX(old), getY(old), old);
        }
    }

    free(aux);
}

void lr(FILE *qry, FILE *txt, FILE *svg, SRBTree t) {
    int i;
    char lado[4];
    double d, w, h;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%s", lado);  // PP frente, EB esquerda, BB direita, PR trás
    fscanf(qry, "%lf", &d);
    fscanf(qry, "%lf", &w);
    fscanf(qry, "%lf", &h);

    fprintf(txt, "\n[*] lr %d %s %lf %lf %lf \n", i, lado, d, w, h);

    AUXLR *aux = calloc(1, sizeof(AUXLR));
    aux->i = i;
    strcpy(aux->lado, lado);
    aux->w = w;
    aux->h = h;
    aux->d = d;
    aux->txt = txt;
    aux->svg = svg;
    aux->t = t;
    aux->nau = NULL;
    percursoProfundidade(t, find_idLR, aux);

    if (!aux->nau) {
        fprintf(txt, "\tNao existe nau com id = %d\n", i);
        free(aux);
        return;
    }

    double need = 0;
    if (energyArremesso(aux->nau, d, w * h, &need)) {
        calc_net(aux);
        percursoProfundidade(t, lr_aux, aux);
    } else {
        fprintf(txt, "\tNau id = %d, e = %lf, energia_necessaria = %lf ENERGIA INSUFICIENTE PARA LANÇAMENTO\n", getId(aux->nau), getEnergy(aux->nau), need);
    }
    free(aux);
}

void calc_net(void *aux) {
    AUXLR *data = aux;
    FILE *svg = data->svg;
    char lado[4];
    strcpy(lado, data->lado);
    double w = data->w;
    double h = data->h;
    double d = data->d;
    Info nau = data->nau;

    double xr, yr;
    if (!strcmp(lado, "PP")) {  // lado da frente, lado a ancora, rede para cima
        xr = getX(nau);
        yr = getY(nau) - h - d;

    } else if (!strcmp(lado, "EB")) {  // esquerda, lado a ancora, rede para esquerda
        xr = getX(nau) - w - d;
        yr = getY(nau);

    } else if (!strcmp(lado, "BB")) {  // direita, lado ancora+largura, rede para direita
        xr = getX(nau) + getW(nau) + d;
        yr = getY(nau);

    } else if (!strcmp(lado, "PR")) {  // baixo, lado da ancora+altura, rede para baixo
        xr = getX(nau);
        yr = getY(nau) + getH(nau) + d;
    }

    char stroke[] = "red";
    char fill[] = "white";
    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"2%%\"/>\n", xr, yr, w, h, stroke, fill);
    data->xr = xr;
    data->yr = yr;
}

void lr_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXLR *data = aux;
    FILE *txt = data->txt;
    int id = data->i;
    Info nau = data->nau;
    double xr = data->xr;
    double yr = data->yr;
    double w = data->w;
    double h = data->h;

    if (insideNet(i, xr, yr, w, h) && getId(i) != id) {
        char recompensa[20];
        int monetario;
        if (getType(i) == 1) {
            strcpy(recompensa, "PEIXE");
            monetario = 5;
            addGold(nau, 5);
        } else if (getType(i) == 3) {
            strcpy(recompensa, "CAMARÃO");
            monetario = 10;
            addGold(nau, 10);
        } else if (getType(i) == 4) {
            if (!strcmp(getText(i), " $")) {
                strcpy(recompensa, "MOEDA");
                monetario = 0;
                setEnergy(nau, getEnergy(nau) + 0.5);
            } else if (!strcmp(getText(i), " >-|-<")) {
                strcpy(recompensa, "LAGOSTA");
                monetario = 20;
                addGold(nau, 20);
            } else {
                monetario = 0;
                strcpy(recompensa, "DETRITOS");
            }
        }

        fprintf(txt, "\tNAU = %d, x = %lf, y= %lf, gold = %lf, e = %lf\n", getId(nau), getX(nau), getY(nau), getGold(nau), getEnergy(nau));
        fprintf(txt, "\t  PESCOU %s, VALOR MONETÁRIO M$%d, id = %d, x = %lf, y = %lf\n", recompensa, monetario, getId(i), getX(i), getY(i));
        Info dead = removeSRB(data->t, getX(i), getY(i), 0, 0, 0, 0);
        if (dead) {
            free(dead);
        }
    }
}

void d(FILE *qry, FILE *txt, FILE *svg, SRBTree t) {
    int i;
    char lado[4];
    double d;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%s", lado);  // PP frente, EB esquerda, BB direita, PR trás
    fscanf(qry, "%lf", &d);

    fprintf(txt, "\n[*] d %d %s %lf \n", i, lado, d);

    AUXD *aux = calloc(1, sizeof(AUXD));
    aux->i = i;
    strcpy(aux->lado, lado);
    aux->d = d;
    aux->txt = txt;
    aux->svg = svg;
    aux->t = t;
    aux->nau = NULL;
    percursoProfundidade(t, find_idD, aux);

    if (energyShot(aux->nau, d)) {
        calc_shot(aux);
        percursoProfundidade(t, d_aux, aux);
    } else {
        fprintf(txt, "\tNAU id = %d, e = %lf, energia_necessaria = %lf ENERGIA INSUFICIENTE PARA LANÇAMENTO\n", getId(aux->nau), getEnergy(aux->nau), d);
    }
    free(aux);
}

void calc_shot(void *aux) {
    AUXD *data = aux;
    FILE *txt = data->txt;
    FILE *svg = data->svg;
    char lado[4];
    strcpy(lado, data->lado);
    double d = data->d;
    Info nau = data->nau;
    double xt, yt;

    if (!strcmp(lado, "PP")) {  // lado da frente, tiro para cima
        xt = getX(nau) + getW(nau) / 2;
        yt = getY(nau) - d;

    } else if (!strcmp(lado, "EB")) {  // esquerda, lado a ancora, rede para esquerda
        xt = getX(nau) - d;
        yt = getY(nau) + getH(nau) / 2;

    } else if (!strcmp(lado, "BB")) {  // direita, lado ancora+largura, rede para direita
        xt = getX(nau) + getW(nau) + d;
        yt = getY(nau) + getH(nau) / 2;

    } else if (!strcmp(lado, "PR")) {  // baixo, lado da ancora+altura, rede para baixo
        xt = getX(nau) + getW(nau) / 2;
        yt = getY(nau) + getH(nau) + d;
    }

    data->xt = xt;
    data->yt = yt;
    char stroke[] = "black";
    char fill[] = "red";
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"60%%\" >*</text>\n", xt, yt, stroke, fill);
    fprintf(txt, "\tNAU id = %d, Atirou em: x = %lf, y = %lf\n", getId(nau), xt, yt);
}

void d_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXD *data = aux;
    FILE *txt = data->txt;
    int id = data->i;
    Info nau = data->nau;
    SRBTree t = data->t;
    double xt = data->xt;
    double yt = data->yt;

    // o tiro é lançado na parte central do lado definido do retangulo (nau)
    if (getId(i) != id && getType(i) == 2) {
        if (hitRectangle(i, xt, yt)) {
            addGold(nau, getGold(i));
            fprintf(txt, "\t  DESTRUIDA Nau id = %d, x = %lf, y = %lf, gold = %lf\n", getId(i), getX(i), getY(i), getGold(i));
            Info dead = removeSRB(t, getX(i), getY(i), getX(i), getY(i), getX(i) + getW(i), getY(i) + getH(i));
            if (dead) {
                free(dead);
            }
        } else {
            fprintf(txt, "\t  ERROU id %d\n", getId(i));
        }
    }
}

void mc(FILE *qry, FILE *txt, SRBTree t) {
    double dx, dy, x, y, w, h;

    fscanf(qry, "%lf", &dx);
    fscanf(qry, "%lf", &dy);
    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);
    fscanf(qry, "%lf", &w);
    fscanf(qry, "%lf", &h);

    fprintf(txt, "\n[*] mc %lf %lf %lf %lf %lf %lf \n", dx, dy, x, y, w, h);

    AUXMC *aux = calloc(1, sizeof(AUXMC));
    aux->dx = dx;
    aux->dy = dy;
    aux->x = x;
    aux->y = y;
    aux->w = w;
    aux->h = h;
    aux->txt = txt;
    aux->t = t;

    percursoProfundidade(t, mc_aux, aux);

    free(aux);
}

void mc_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXMC *data = aux;
    FILE *txt = data->txt;
    double dx = data->dx;
    double dy = data->dy;
    double x1 = data->x;
    double y1 = data->y;
    double w = data->w;
    double h = data->h;
    SRBTree t = data->t;

    if (i && getType(i) == 1) {
        if (fishInside(i, x1, y1, w, h)) {
            fprintf(txt, "\tPEIXE id = %d, xi = %lf, yi = %lf, ", getId(i), getX(i), getY(i));
            Info old = removeSRB(t, getX(i), getY(i), getX(i) - getR(i), getY(i) - getR(i), getX(i) + getR(i), getY(i) + getR(i));
            if (old) {
                setX(old, dx);
                setY(old, dy);
                fprintf(txt, "xf = %lf, yf = %lf\n", getX(i), getY(i));
                insertSRB(t, getX(old), getY(old), getX(old) - getR(old), getY(old) - getR(old), getX(old) + getR(old), getY(old) + getR(old), old);
            }
        }
    }
}

void printResultados(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    FILE *txt = aux;

    if (getType(i) == 2) {
        fprintf(txt, "\tNAU id = %d, x = %lf, y = %lf, gold = %lf, energy = %lf\n", getId(i), getX(i), getY(i), getGold(i), getEnergy(i));
    }
}
