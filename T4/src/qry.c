#include "qry.h"

void readQry(Rb t, Digraph d, char *bedQry, char *bsdSvg, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvg);
    char comando[8];

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (!strcmp(comando, "@o?")) {
            oFunc(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "catac")) {
            catac(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "pnt")) {
            pnt(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "blq")) {
            blq(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "rbl")) {
            rbl(qry, txt, svg, t, d);
        
        } else if (!strcmp(comando, "rf")) {
            rf(qry, txt, svg, t, d);
        
        } else if (!strcmp(comando, "b")) {
            bFunc(qry, txt, svg, t, d);
        
        } else if (!strcmp(comando, "p?")) {
            pFunc(qry, txt, svg, t, d);
        }
        strcpy(comando, " ");
    }

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

void oFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void catac(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void pnt(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void blq(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void rbl(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void rf(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void bFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}

void pFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    return;
}