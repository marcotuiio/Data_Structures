#include "qry.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "text.h"
#include "tree.h"

void readQry(Tree root, char *bedQry, char *bsdSvgQry, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    char comando[6];

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (strcmp(comando, "na") == 0) {
            na(qry, txt);

        } else if (strcmp(comando, "tp") == 0) {
            tp(root, qry, txt);

        } else if (strcmp(comando, "tr") == 0) {
            tr(qry, txt);

        } else if (strcmp(comando, "be") == 0) {
            be(qry, txt);
        }
        strcpy(comando, " ");
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

void tp(Tree root, FILE *qry, FILE *txt) {
    double x, y;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);

    fprintf(txt, "tp %lf %lf \n", x, y);

    postOrderTp(root, getRoot(root), x, y);
}

void postOrderTp(Tree t, Node root, double x, double y) {
    int ctrl;
    Info my_info;
    bool marcador;

    if (root == NULL) {
        return;
    }

    postOrderTp(t, getLeft(root), x, y);
    postOrderTp(t, getCenter(root), x, y);
    postOrderTp(t, getRight(root), x, y);
    ctrl = getCtrl(root);
    my_info = getInfo(root);
    if (ctrl == 1) {
        marcador = tpCircle(my_info, x, y);
        if (marcador) {
            removeNode(t, root, getTX(root), getTY(root));
        }
        
    } else if (ctrl == 2) {
    } else if (ctrl == 3) {
    } else if (ctrl == 4) {
    }
}

bool tpCircle(Info circ, double x, double y) {
    double cx, cy, cr;
    double x_aux, y_aux, r_aux;
    cx = getCircX(circ);
    cy = getCircY(circ);
    cr = getCircRADIUS(circ);

    x_aux = (x - cx) * (x - cx);
    y_aux = (y - cy) * (y - cy);
    r_aux = cr * cr;

    if (x_aux + y_aux <= r_aux) { // Está dentro do circulo
        return true;
    }
    return false;
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
            check = isInsideRect(fig, x, y, w, h);
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

bool isInsideCirc(Info circ, double x, double y, double w, double h) {
    int idC = getCircID(circ);
    double circX = getCircX(circ);
    double circY = getCircY(circ);
    double circRadius = getCircRADIUS(circ);

    if ((x + w) >= (circX + circRadius) && (x) <= (circX - circRadius)) {
        if ((y + h) >= (circY + circRadius) && (y) <= (circY - circRadius)) {
            if (x <= circX && y <= circY) {
                return true;
            }
        }
    }
    return false;
}

bool isInsideRect(Info rect, double x, double y, double w, double h) {
    int idR = getRectID(rect);
    double recX = getRectX(rect);
    double recY = getRectY(rect);
    double recHeight = getRectHEIGHT(rect);
    double recWidth = getRectWIDTH(rect);

    if (((x + w) >= (recX + recWidth))) {
        if (((y + h) >= (recY + recHeight))) {
            if (x <= recX && y <= recY) {
                return true;
            }
        }
    }
    return false;
}

bool isInsideLine(Info line, double x, double y, double w, double h) {
    int idL = getLineID(line);
    double linX1 = getLineX(line);
    double linY1 = getLineY(line);
    double linX2 = getLineFINALX(line);
    double linY2 = getLineFINALY(line);

    if ((x + w) >= (linX1) && (y + h) >= (linY1)) {
        if ((x + w) >= (linX2) && (y + h) >= (linY2)) {
            if (x <= linX1 && y <= linY1 && x <= linX2 && y <= linY2) {
                return true;
            }
        }
    }
    return true;
}
bool isInsideText(Info text, double x, double y, double w, double h) {
    int idT = getTxtID(text);
    double txtX = getTxtX(text);
    double txtY = getTxtY(text);

    if ((x + w) >= (txtX) && (y + h) >= (txtY)) {
        if (x <= txtX && y <= txtY) {
            return true;
        }
    }
    return false;
}
