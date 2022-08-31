#include "qry.h"

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

double e(FILE *qry, FILE *txt) {
    double e;

    fscanf(qry, "%lf", &e);

    fprintf(txt, "\n[*] e %lf \n", e);

    return e;
}

void mv(FILE *qry, FILE *txt, SRBTree t) {
    int i;
    double dx, dy;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%lf", &dx);
    fscanf(qry, "%lf", &dy);

    fprintf(txt, "\n[*] mv %d %lf %lf \n", i, dx, dy);
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
}

void d(FILE *qry, FILE *txt, SRBTree t) {
    int i;
    char lado[4];
    double d;

    fscanf(qry, "%d", &i);
    fscanf(qry, "%s", lado);
    fscanf(qry, "%lf", &d);

    fprintf(txt, "\n[*] d %d %s %lf \n", i, lado, d);
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
}