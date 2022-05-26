#include "qry.h"

#include "svg.h"    
#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "text.h"
#include "tree.h"

void readQry(Tree root, char *bedQry, char *bsdSvgQry, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvgQry);
    char comando[6];
    double v = 0;  // agressividade do ataque

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (strcmp(comando, "na") == 0) {
            v = na(qry, txt);

        } else if (strcmp(comando, "tp") == 0) {
            tp(root, qry, txt);

        } else if (strcmp(comando, "tr") == 0) {
            tr(qry, txt);

        } else if (strcmp(comando, "be") == 0) {
            be(root, qry, txt, svg, v);
        }
        strcpy(comando, " ");
    }
    postOrderSVG(getRoot(root), svg);

    fclose(qry);
    fclose(txt);
    killSvg(svg);
}

FILE *openQry(char *bedQry) {
    FILE *qry = fopen(bedQry, "r");
    if (qry == NULL) {
        printf("ERRO NA CRIAÇÃO DO QRY\n");
        exit(1);
    }
    return qry;
}

FILE *openTxt(char *bsdTxt) {
    FILE *txt = fopen(bsdTxt, "w");
    if (txt == NULL) {
        printf("ERRO NA CRIAÇÃO DO TXT\n");
        exit(1);
    }
    return txt;
}

double na(FILE *qry, FILE *txt) {
    double v;

    fscanf(qry, "%lf", &v);

    fprintf(txt, "\n[*] na %lf \n", v);

    return v;
}

void tp(Tree root, FILE *qry, FILE *txt) {
    double x, y;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);

    fprintf(txt, "\n[*] tp %lf %lf \n", x, y);

    postOrderTp(txt, root, getRoot(root), x, y);
}

void postOrderTp(FILE *txt, Tree t, Node root, double x, double y) {
    int ctrl;
    Info my_info;
    bool marcador;

    if (root == NULL) {
        return;
    }

    postOrderTp(txt, t, getLeft(root), x, y);
    postOrderTp(txt, t, getCenter(root), x, y);
    postOrderTp(txt, t, getRight(root), x, y);

    ctrl = getCtrl(root);
    my_info = getInfo(root);
    if (ctrl == 1) {
        marcador = tpCirc(txt, my_info, x, y);

    } else if (ctrl == 2) {
        marcador = tpRect(txt, my_info, x, y);

    } else if (ctrl == 3) {
        marcador = tpLine(txt, my_info, x, y);

    } else if (ctrl == 4) {
        marcador = tpTxt(txt, my_info, x, y);
    }

    // Escrever um asterisco vermelho e a qntd de figuras que acertou no SVG em x, y
    // ou escrever um asterisco cinza em x, y se errou
    if (marcador) {
        removeNode(t, getRoot(t), getTX(root), getTY(root));
    } else {
        fprintf(txt, "ÁGUA\n");
    }
}

bool tpCirc(FILE *txt, Info circ, double x, double y) {
    double cx, cy, cr;
    double x_aux, y_aux, r_aux;
    cx = getCircX(circ);
    cy = getCircY(circ);
    cr = getCircRADIUS(circ);

    x_aux = (x - cx) * (x - cx);
    y_aux = (y - cy) * (y - cy);
    r_aux = cr * cr;

    if (x_aux + y_aux <= r_aux) {  // Está dentro do circulo
        fprintf(txt, "Acertou Círculo id = %d, x = %lf, y = %lf, r = %lf\n", getCircID(circ), cx, cy, cr);
        return true;
    }
    return false;
}

bool tpRect(FILE *txt, Info rect, double x, double y) {
    double rx, ry, h, w;
    rx = getRectX(rect);
    ry = getRectY(rect);
    h = getRectHEIGHT(rect);
    w = getRectWIDTH(rect);

    if (x >= rx && x <= (rx + w)) {  // Está dentro do retangulo
        if (y >= ry && y <= (ry + h)) {
            fprintf(txt, "Acertou Retângulo id = %d, x = %lf, y = %lf, w = %lf, h = %lf\n", getRectID(rect), rx, ry, w, h);
            return true;
        }
    }
    return false;
}

bool tpLine(FILE *txt, Info line, double x, double y) {
    double lx1, lx2, ly1, ly2;
    double lenAC, lenCB, lenAB;
    // lenAC = distancia do x1,y1 da linha até o torpedo
    // lenCB = distancia do torpedo até o x2,y2, da linha
    // lenAB = distancia total da linha

    lx1 = getLineX(line);
    lx2 = getLineFINALX(line);
    ly1 = getLineY(line);
    ly2 = getLineFINALY(line);

    lenAC = getLineLenght(lx1, ly1, x, y);
    lenCB = getLineLenght(x, y, lx2, ly2);
    lenAB = getLineLenght(lx1, ly1, lx2, ly2);

    if (lenAC + lenCB == lenAB) {  // Está na linha
        fprintf(txt, "Acertou Linha id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf\n", getLineID(line), lx1, ly1, lx2, ly2);
        return true;
    }
    return false;
}

bool tpTxt(FILE *txt, Info text, double x, double y) {
    double tx, ty;
    tx = getTxtX(text);
    ty = getTxtY(text);

    if (tx == x && ty == y) {  // é a própria âncora do texto
        fprintf(txt, "Acertou Texto id = %d, x = %lf, y %lf, anchor = %s\n", getTxtID(text), tx, ty, getTxtANCHOR(text));
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

    fprintf(txt, "\n[*] tr %lf %lf %lf %lf %d \n", x, y, dx, dy, id);
}

void be(Tree root, FILE *qry, FILE *txt, FILE *svg, double v) {
    double x, y, w, h;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);
    fscanf(qry, "%lf", &w);
    fscanf(qry, "%lf", &h);

    fprintf(txt, "\n[*] be %lf %lf %lf %lf \n", x, y, w, h);
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"red\" />\n", x, y, w, h);

    postOrderBe(svg, txt, root, getRoot(root), x, y, w, h, v);
}

double calcReduc(double v, double areaEquip, double areaSel) {
    double reduc;
    reduc = v * areaEquip / areaSel;

    return reduc;
}

double calcSelArea(double x, double y, double w, double h) {
    double a;

    a = (x + w) * (y + h);
    return a;
}

void postOrderBe(FILE *svg, FILE *txt, Tree root, Node node, double x, double y, double w, double h, double v) {
    bool check;
    double reduc;
    double selArea = calcSelArea(x, y, w, h);

    if (!node) {
        return;
    }

    postOrderBe(svg, txt, root, getLeft(node), x, y, w, h, v);
    postOrderBe(svg, txt, root, getCenter(node), x, y, w, h, v);
    postOrderBe(svg, txt, root, getRight(node), x, y, w, h, v);

    Info fig = getInfo(node);
    switch (getCtrl(node)) {
        case 1:
            check = isInsideCirc(fig, x, y, w, h);
            if (check) {
                reduc = calcReduc(v, getCircArea(fig), selArea);
                setProtecCirc(fig, reduc);
                printReducCirc(svg, txt, fig, root, node);
            }
            break;

        case 2:
            check = isInsideRect(fig, x, y, w, h);
            if (check) {
                reduc = calcReduc(v, getRectArea(fig), selArea);
                setProtecRect(fig, reduc);
                printReducRect(svg, txt, fig, root, node);
            }
            break;

        case 3:
            check = isInsideLine(fig, x, y, w, h);
            if (check) {
                reduc = calcReduc(v, getLineArea(fig), selArea);
                setProtecLine(fig, reduc);
                printReducLine(svg, txt, fig, root, node);
            }
            break;

        case 4:
            check = isInsideText(fig, x, y, w, h);
            if (check) {
                reduc = calcReduc(v, 0.1, selArea);
                setProtecTxt(fig, reduc);
                printReducText(svg, txt, fig, root, node);
            }
            break;

        default:
            printf("ERRO!!!!\n");
            break;
    }
}

bool isInsideCirc(Info circ, double x, double y, double w, double h) {
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

void printReducCirc(FILE *svg, FILE *txt, Info circ, Tree root, Node node) {
    double r = 1.75;
    char color[] = "red";
    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getCircX(circ), getCircY(circ), r, color, color);
    fprintf(txt, "Atingido Círculo id = %d, x = %lf, y = %lf, r = %lf, proteção = %lf ", getCircID(circ), getCircX(circ), getCircY(circ), getCircRADIUS(circ), getProtecCirc(circ));
    // printf("protec c %lf\n", getProtecCirc(circ));
    if (getProtecCirc(circ) <= 0) {
        removeNode(root, getRoot(root), getTX(node), getTY(node));
        fprintf(txt, "REMOVIDO\n");
    } else {
        fprintf(txt, "\n");
    }
}

bool isInsideRect(Info rect, double x, double y, double w, double h) {
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

void printReducRect(FILE *svg, FILE *txt, Info rect, Tree root, Node node) {
    double r = 1.75;
    char color[] = "red";
    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getRectX(rect), getRectY(rect), r, color, color);
    fprintf(txt, "Atingido retângulo id = %d, x = %lf, y = %lf, w = %lf, h = %lf proteção = %lf ", getRectID(rect), getRectX(rect), getRectY(rect), getRectWIDTH(rect), getRectHEIGHT(rect), getProtecRect(rect));
    // printf("protec r %lf\n", getProtecRect(rect));
    if (getProtecRect(rect) <= 0) {
        removeNode(root, getRoot(root), getTX(node), getTY(node));
        fprintf(txt, "REMOVIDO\n");
    } else {
        fprintf(txt, "\n");
    }
}

bool isInsideLine(Info line, double x, double y, double w, double h) {
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

void printReducLine(FILE *svg, FILE *txt, Info line, Tree root, Node node) {
    double r = 1.75;
    char color[] = "red";
    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getLineX(line), getLineY(line), r, color, color);
    fprintf(txt, "Atingido linha id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf proteção = %lf ", getLineID(line), getLineX(line), getLineY(line), getLineFINALX(line), getLineFINALY(line), getProtecLine(line));
    // printf("protec l %lf\n", getProtecLine(line));
    if (getProtecLine(line) <= 0) {
        removeNode(root, getRoot(root), getTX(node), getTY(node));
        fprintf(txt, "REMOVIDO\n");
    } else {
        fprintf(txt, "\n");
    }
}

bool isInsideText(Info text, double x, double y, double w, double h) {
    double txtX = getTxtX(text);
    double txtY = getTxtY(text);

    if ((x + w) >= (txtX) && (y + h) >= (txtY)) {
        if (x <= txtX && y <= txtY) {
            return true;
        }
    }
    return false;
}

void printReducText(FILE *svg, FILE *txt, Info text, Tree root, Node node) {
    double r = 1.75;
    char color[] = "red";
    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getTxtX(text), getTxtY(text), r, color, color);
    fprintf(txt, "Atingido texto id = %d, x = %lf, y = %lf, proteção = %lf ", getTxtID(text), getTxtX(text), getTxtY(text), getProtecTxt(text));
    // printf("protec t %lf\n", getProtecTxt(text));
    if (getProtecTxt(text) <= 0) {
        removeNode(root, getRoot(root), getTX(node), getTY(node));
        fprintf(txt, "REMOVIDO\n");
    } else {
        fprintf(txt, "\n");
    }
}
