#include "qry.h"

void readQry(char *bedQry, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    char comando[4];

    while(!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (strcmp(comando, "na") == 0) {
            na(qry, txt);

        } else if (strcmp(comando, "tp") == 0) {
            tp(qry, txt);

        } else if (strcmp(comando, "tr") == 0) {
            tr(qry, txt);

        } else if (strcmp(comando, "be") == 0) {
            be(qry, txt);
        }
    }
    fclose(qry);
}

FILE *openQry(char *bedQry) {
    FILE *qry = fopen(bedQry, "r");
    if (qry == NULL) {
        printf("ERRO NA CRIAÇÃO DO QRY\n");
        exit(1);
    }
    return qry;
}

FILE *OpenTxt(char *bsdTxt) {
    FILE *txt = fopen(bsdTxt, "w");
    if (txt == NULL) {
        printf("ERRO NA CRIAÇÃO DO TXT\n");
        exit(1);
    }
    return txt;
}

void na(FILE *qry, FILE *txt) {
    double v;

    fscanf(qry, "%lf", &v);

    fprintf(txt, "\nna %lf \n", v);

}

void tp(FILE *qry, FILE *txt) {
    double x, y;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);

    fprintf(txt, "tp %lf %lf \n", x, y);

}

void tr(FILE *qry, FILE *txt) {
    double x, y, dx, dy;
    int id;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);
    fscanf(qry, "%lf", &dx);
    fscanf(qry, "%lf", &dy);
    fscanf(qry, "%d", &id);

    fprintf(txt, "tr %lf %lf %lf %lf %d \n", x, y, dx, dy, id);

}

void be(FILE *qry, FILE *txt) {
    double x, y, w, h;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);
    fscanf(qry, "%lf", &w);
    fscanf(qry, "%lf", &h);

    fprintf(txt, "tr %lf %lf %lf %lf \n", x, y, w, h);
}