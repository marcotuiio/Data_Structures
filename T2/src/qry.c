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

void sel(Tree root, Info fig, double x, double y, double w, double h) {
    // percorrer toda a arvore
    bool check;

    switch (getFigType(fig)) {
    case 'c':
        check = isInsideCirc(fig, x, y, w, h);
        if (check) {
            // ta dentro
        }
        break;

    case 'r':
        isInsideRect(fig, x, y, w, h);
        if (check) {
            // ta dentro
        }
        break;

    case 'l':
        check = isInsideLine(fig, x, y, w, h);
        if (check) {
            // ta dentro
        }
        break;
    
    case 't':
        check = isInsideText(fig, x, y, w, h);
        if (check) {
            // ta dentro
        }
        break;

    default:

        break;
    }
}

bool isInsideCirc(Info circ, x, y, w, h) {
    int idC = getCircID(circ);
    double circX = getCircX(circ);
    double circY = getCircY(circ);
    double circRadius = getCircRADIUS(circ);

    if ((x + w) >= (circX + circRadius) && (x) <= (circX - circRadius)) {
        if ((y + h) >= (circY + circRadius) && (y) <= (circY - circRadius)) {
            if (x <= circX && y <= circY) {
                insereFim(sC, auxI2);
                insereFim(g, auxG2);

                return true;
            }
        }
    }
    return false;
}

bool isInsideRect(Info rect, x, y, w, h) {
    int idR = getRectID(rect);
    double recX = getRectX(rect);
    double recY = getRectY(rect);
    double recHeight = getRectHEIGHT(rect);
    double recWidth = getRectWIDTH(rect);

    if (((x + w) >= (recX + recWidth))) {
        if (((y + h) >= (recY + recHeight))) {
            if (x <= recX && y <= recY) {
                insereFim(sR, auxI1);
                insereFim(g, auxG1);

                return true;
            }
        }
    }
    return false;
}

bool isInsideLine(Info line, x, y, w, h) {
    int idL = getLineID(line);
    double linX1 = getLineX(line);
    double linY1 = getLineY(line);
    double linX2 = getLineFINALX(line);
    double linY2 = getLineFINALY(line);

    if ((x + w) >= (linX1) && (y + h) >= (linY1)) {
        if ((x + w) >= (linX2) && (y + h) >= (linY2)) {
            if (x <= linX1 && y <= linY1 && x <= linX2 && y <= linY2) {
                insereFim(sL, auxI4);
                insereFim(g, auxG4);

                return true;
            }
        }
    }
    return true;
}
bool isInsideText(Info text, x, y, w, h) {
    int idT = getTxtID(text);
    double txtX = getTxtX(text);
    double txtY = getTxtY(text);

    if ((x + w) >= (txtX) && (y + h) >= (txtY)) {
        if (x <= txtX && y <= txtY) {
            insereFim(sT, auxI3);
            insereFim(g, auxG3);

            return true;
        }
    }
    return false;
}
