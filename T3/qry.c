#include "qry.h"

struct aux1 {
    double e;
    FILE *txt;
};
typedef struct aux1 AUXE;

struct aux2 {
    int i;
    double dx, dy;
    FILE *txt;
    SRBTree t;
};
typedef struct aux2 AUXMV;

struct aux3 {
    int i;
    char lado[4];
    double w, h, d;
    FILE *txt;
    Info nau;
    SRBTree t;
};
typedef struct aux3 AUXLR;

struct aux4 {
    int i;
    char lado[4];
    double d;
    FILE *txt;
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

// PP frente, EB esquerda, BB direita, PR trás
void readQry(SRBTree t, char *bedQry, char *bsdSvgQry, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvgQry);
    char comando[6];
    // double energy = 0;  // agressividade do ataque

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (!strcmp(comando, "e")) {
            // energy = e(qry, txt);

        } else if (!strcmp(comando, "mv")) {
            mv(qry, txt, t);

        } else if (!strcmp(comando, "lr")) {
            lr(qry, txt, t);

        } else if (!strcmp(comando, "d")) {
            d(qry, txt, t);

        } else if (!strcmp(comando, "mc")) {
            mc(qry, txt, t);
        }
        strcpy(comando, " ");
    }
    writeSvg(svg, t);

    fclose(qry);
    fclose(txt);
    killSvg(svg);
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

void find_id(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXLR *aux0 = aux;
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
        fprintf(txt, "id = %d, x = %lf, y = %lf, e = %lf\n", getId(i), getX(i), getY(i), e);
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
    aux->dx = dx;
    aux->dy = dy;
    aux->txt = txt;
    aux->t = t;

    percursoProfundidade(t, mv_aux, aux);
    free(aux);
}

void mv_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXMV *data = aux;
    FILE *txt = data->txt;
    int id = data->i;
    double dx = data->dx;
    double dy = data->dy;
    SRBTree t = data->t;

    // Fazer funçoes para cuidar da MBB e energia de deslocamento !!!!
    if (getId(i) == id) {
        if (energyDeslocamento(i, dx)) {
            fprintf(txt, "id = %d, xi = %lf, yi = %lf, ", getId(i), getX(i), getY(i));
            removeSRB(t, getX(i), getY(i), getX(i), getY(i), getX(i)+getW(i), getY(i)+getH(i));
            setX(i, x + dx);
            setY(i, y + dy);
            fprintf(txt, "xf = %lf, yf = %lf\n", getX(i), getY(i));
            insertSRB(t, x + dx, y + dy, getX(i), getY(i), getX(i)+getW(i), getY(i)+getH(i), i);
        }
    }
}

void lr(FILE *qry, FILE *txt, SRBTree t) {
    int i;
    char lado[4];
    double d, w, h;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%s", lado);
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
    aux->t = t;
    Info nau = NULL;
    aux->nau = nau;
    percursoProfundidade(t, find_id, aux);

    percursoProfundidade(t, lr_aux, aux);
    free(aux);
}

void lr_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXLR *data = aux;
    FILE *txt = data->txt;
    int id = data->i;
    char lado[4];
    strcpy(lado, data->lado);
    double w = data->w;
    double h = data->h;
    double d = data->d;
    Info nau = data->nau;

    // olhar energia para jogar rede, ver o que ta dentro, remover e atribuir as recompensas
    // redes são lançadas a partir da ancora do retangulo (nau)
    if (getId(i) != id) {
        if (energyArremesso(nau, d, w * h)) {
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

            bool pescou = insideNet(i, xr, yr, w, h);
            if (pescou) {
                // remover e fazer tabela de recompensa para energia
                char recompensa[20];
                if (getType(i) == 1) {
                    strcpy(recompensa, "PEIXE");
                    addGold(nau, 5);
                } else if (getType(i) == 3) {
                    strcpy(recompensa, "CAMARÃO");
                    addGold(nau, 10);
                } else if (getType(i) == 4) {
                    if (!strcmp(getText(i), "$")) {
                        strcpy(recompensa, "MOEDA");
                        setEnergy(nau, getEnergy(nau) + 0.5);
                    } else if (!strcmp(getText(i), ">-|-<")) {
                        strcpy(recompensa, "LAGOSTA");
                        addGold(nau, 20);
                    } else {
                        strcpy(recompensa, "DETRITOS");
                    }
                }
                fprintf(txt, "NAU = %d, x = %lf, y= %lf, gold = %lf, e = %lf\n", getId(nau), getX(nau), getY(nau), getGold(nau), getEnergy(nau));
                fprintf(txt, "\tPESCOU %s, id = %d, x = %lf, y = %lf\n", recompensa, getId(i), getX(i), getY(i));
            }
        }
    }
}

void d(FILE *qry, FILE *txt, SRBTree t) {
    int i;
    char lado[4];
    double d;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%s", lado);
    fscanf(qry, "%lf", &d);

    fprintf(txt, "\n[*] d %d %s %lf \n", i, lado, d);

    AUXD *aux = calloc(1, sizeof(AUXD));
    aux->i = i;
    strcpy(aux->lado, lado);
    aux->d = d;
    aux->txt = txt;
    aux->t = t;
    Info nau = NULL;
    aux->nau = nau;
    percursoProfundidade(t, find_id, aux);

    percursoProfundidade(t, d_aux, aux);
    free(aux);
}

void d_aux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {
    AUXD *data = aux;
    FILE *txt = data->txt;
    int id = data->i;
    char lado[4];
    strcpy(lado, data->lado);
    double d = data->d;
    Info nau = data->nau;
    SRBTree t = data->t;
    double xt, yt;
    // fazer os calculos de energia para tiro e reportar txt!!

    // o tiro é lançado na parte central do lado definido do retangulo (nau)
    if (getId(i) != id) {
        if (energyShot(nau, d)) {
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
            bool shot = hitRectangle(i, xt, yt);
            fprintf(txt, "Nau id = %d, Atirou em: x = %lf, y = %lf\n", getId(nau), xt, yt);
            if (shot) {
                // arrumar MBB !!
                addGold(nau, getGold(i));
                fprintf(txt, "\t Acertou e destrui nau id = %d, x = %lf, y = %lf, gold = %lf\n", getId(i), getX(i), getY(i), getGold(i));
                removeSRB(t, getX(i), getY(i), getX(i), getY(i), getX(i)+getW(i), getY(i)+getH(i));
            }
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

    // arrumar MBB !!
    if (getType(i) == 1) {
        if (fishInside(i, x1, y1, w, h)) {
            fprintf(txt, "id = %d, xi = %lf, yi = %lf, ", getId(i), getX(i), getY(i));
            removeSRB(t, getX(i), getY(i), getX(i), getY(i), getX(i)+getW(i), getY(i)+getH(i));
            setX(i, x + dx);
            setY(i, y + dy);
            fprintf(txt, "xf = %lf, yf = %lf\n", getX(i), getY(i));
            insertSRB(t, x + dx, y + dy, getX(i), getY(i), getX(i)+getW(i), getY(i)+getH(i), i);
        }
    }
}