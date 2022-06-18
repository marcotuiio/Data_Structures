#include "qry.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "svg.h"
#include "text.h"
#include "tree.h"

struct pnts {
    double pt_destr;
    double pt_inativ;
};
typedef struct pnts game_points;


void readQry(Tree root, char *bedQry, char *bsdSvgQry, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvgQry);
    Pontos my_points = createPontos();
    char comando[6];
    double v = 0;  // agressividade do ataque

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (strcmp(comando, "na") == 0) {
            v = na(qry, txt);

        } else if (strcmp(comando, "tp") == 0) {
            tp(my_points, root, qry, svg, txt);

        } else if (strcmp(comando, "tr") == 0) {
            tr(root, qry, svg, txt);

        } else if (strcmp(comando, "be") == 0) {
            be(my_points, root, qry, txt, svg, v);
        }
        strcpy(comando, " ");
    }
    preOrderSVG(getRoot(root), svg);
    printPoints(my_points, txt);
    
    fclose(qry);
    fclose(txt);
    killSvg(svg);
    free(my_points);
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

Pontos createPontos() {
    game_points *new_pnts = calloc(1, sizeof(game_points));
    new_pnts->pt_destr = 0;
    new_pnts->pt_inativ = 0;
    return new_pnts;
}

void updateDestr(Pontos pnts, double pt_destr) {
    game_points *my_pnts = pnts;
    double aux = my_pnts->pt_destr + pt_destr;

    my_pnts->pt_destr = aux;
}

void updateInativ(Pontos pnts, double pt_inativ) {
    game_points *my_pnts = pnts;
    double aux = my_pnts->pt_inativ + pt_inativ;

    my_pnts->pt_inativ = aux;
}

void printPoints(Pontos pnts, FILE *txt) {
    game_points *my_pnts = pnts;

    fprintf(txt, "\n>> RESULTADOS FINAIS DO JOGO:\n");
    fprintf(txt, "\tPontos de destruição = %.2f\n", my_pnts->pt_destr);
    fprintf(txt, "\tPontos de inatividade = %.2f\n", my_pnts->pt_inativ);
    fprintf(txt, "\tPontuação Total = %.2f\n", my_pnts->pt_destr + my_pnts->pt_inativ);
}

double na(FILE *qry, FILE *txt) {
    double v;

    fscanf(qry, "%lf", &v);

    fprintf(txt, "\n[*] na %lf \n", v);

    return v;
}

void tp(Pontos pnts, Tree root, FILE *qry, FILE *svg, FILE *txt) {
    double x, y;
    char check[] = "VAZIO";

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);

    fprintf(txt, "\n[*] tp %lf %lf \n", x, y);

    preOrderTp(pnts, txt, root, getRoot(root), x, y, check);
    if (!strcmp(check, "VAZIO")) {
        fprintf(txt, "ÁGUA\n");
        fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"black\" font-size=\"14\" fill=\"grey\">*</text>\n", x, y);  
   
    } else {
        fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"red\" font-size=\"20\" fill=\"red\" >*</text>\n", x, y);
    }
}

void preOrderTp(Pontos pnts, FILE *txt, Tree t, Node root, double x, double y, char *check) {
    Info my_info;
    bool marcador = false;

    if (!root) {
        return;
    }
    
    if (!getRemovedStatus(root)) {
        my_info = getInfo(root);

        switch (getCtrl(root)) {
            case 1:
                marcador = tpCirc(my_info, x, y);
                if(marcador) {
                    fprintf(txt, "Acertou Círculo id = %d, x = %lf, y = %lf, r = %lf\n", getCircID(my_info), getCircX(my_info), getCircY(my_info), getCircRADIUS(my_info));
                    double auxdr = getCircArea(my_info) / 5;
                    updateDestr(pnts, 75 / auxdr);
                    // removeNode(t, getRoot(t), getTX(root), getTY(root), getCircID(my_info));
                    markRemoved(t, root);
                    strcpy(check, "CHEIO");
                } 
                break;

            case 2:
                marcador = tpRect(my_info, x, y);
                if(marcador) {
                    fprintf(txt, "Acertou Retângulo id = %d, x = %lf, y = %lf, w = %lf, h = %lf\n", getRectID(my_info), getRectX(my_info), getRectY(my_info), getRectWIDTH(my_info), getRectHEIGHT(my_info));
                    double auxdr = getRectArea(my_info) / 5;
                    updateDestr(pnts, 90 / auxdr);
                    // removeNode(t, getRoot(t), getTX(root), getTY(root), getRectID(my_info));
                    markRemoved(t, root);
                    strcpy(check, "CHEIO");
                } 
                break;

            case 3:
                marcador = tpLine(my_info, x, y);
                if (marcador) {
                    fprintf(txt, "Acertou Linha id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf\n", getLineID(my_info), getLineX(my_info), getLineY(my_info), getLineFINALX(my_info), getLineFINALY(my_info));
                    updateDestr(pnts, 150);
                    // removeNode(t, getRoot(t), getTX(root), getTY(root), getLineID(my_info));
                    markRemoved(t, root);
                    strcpy(check, "CHEIO");
                } 
                break;

            case 4:
                marcador = tpTxt(my_info, x, y);
                if (marcador) {
                    fprintf(txt, "Acertou Texto id = %d, x = %lf, y = %lf, txt = %s\n", getTxtID(my_info), getTxtX(my_info), getTxtY(my_info), getTxtTEXT(my_info));
                    updateDestr(pnts, 500);
                    // removeNode(t, getRoot(t), getTX(root), getTY(root), getTxtID(my_info));
                    markRemoved(t, root);
                    strcpy(check, "CHEIO");
                } 
                break;

            default:
                break;
        } 
    }

    preOrderTp(pnts, txt, t, getLeft(root), x, y, check);
    preOrderTp(pnts, txt, t, getCenter(root), x, y, check);
    preOrderTp(pnts, txt, t, getRight(root), x, y, check);
}

bool tpCirc(Info circ, double x, double y) {
    double cx, cy, cr;
    double x_aux, y_aux, r_aux;
    cx = getCircX(circ);
    cy = getCircY(circ);
    cr = getCircRADIUS(circ);

    x_aux = (x - cx) * (x - cx);
    y_aux = (y - cy) * (y - cy);
    r_aux = cr * cr;

    if (x_aux + y_aux <= r_aux) {  // Está dentro do circulo
        return true;
    }
    return false;
}

bool tpRect(Info rect, double x, double y) {
    double rx, ry, h, w;
    rx = getRectX(rect);
    ry = getRectY(rect);
    h = getRectHEIGHT(rect);
    w = getRectWIDTH(rect);

    if (x >= rx && x <= (rx + w)) {  // Está dentro do retangulo
        if (y >= ry && y <= (ry + h)) {
            return true;
        }
    }
    return false;
}

bool tpLine(Info line, double x, double y) {
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
        return true;
    }
    return false;
}

bool tpTxt(Info text, double x, double y) {
    double tx, ty;
    tx = getTxtX(text);
    ty = getTxtY(text);

    if (tx == x && ty == y) {  // é a própria âncora do texto
        return true;
    }
    return false;
}

void tr(Tree root, FILE *qry, FILE *svg, FILE *txt) {
    double x, y, dx, dy;
    int id;
    char check[] = "VAZIO";

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);
    fscanf(qry, "%lf", &dx);
    fscanf(qry, "%lf", &dy);
    fscanf(qry, "%d", &id);

    fprintf(txt, "\n[*] tr %lf %lf %lf %lf %d \n", x, y, dx, dy, id);
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"red\">@</text>\n", x, y);

    preOrderTr(txt, root, getRoot(root), x, y, dx, dy, id, check);
    if (!strcmp(check, "VAZIO")) {
        fprintf(txt, "ÁGUA\n");
    }
}

void preOrderTr(FILE *txt, Tree t, Node root, double x, double y, double dx, double dy, int id, char *check) {
    Info my_info;
    bool marcador;

    if (!root) {
        return;
    }

    if (!getRemovedStatus(root)) {
        my_info = getInfo(root);

        switch (getCtrl(root)) {
            case 1:
                marcador = tpCirc(my_info, x, y);
                if (marcador) {
                    Info new_circ = criaCirc();
                    replicateCirc(t, my_info, new_circ, dx, dy, id);
                    fprintf(txt, "Círculo Base id = %d, x = %lf, y = %lf, r = %lf, corb = %s, corp = %s\n", getCircID(my_info), getCircX(my_info), getCircY(my_info), getCircRADIUS(my_info), getcircEDGE(my_info), getCircFILL(my_info));
                    fprintf(txt, "Círculo Replicado id = %d, x = %lf, y = %lf, r = %lf, corb = %s, corp = %s\n", getCircID(new_circ), getCircX(new_circ), getCircY(new_circ), getCircRADIUS(new_circ), getcircEDGE(new_circ), getCircFILL(new_circ));
                    id++;
                    strcpy(check, "CHEIO");
                } 
                break;

            case 2:
                marcador = tpRect(my_info, x, y);
                if (marcador) {
                    Info new_rect = criaRec();
                    replicateRect(t, my_info, new_rect, dx, dy, id);
                    fprintf(txt, "Retangulo Base id = %d, x = %lf, y = %lf, w = %lf, h = %lf, corb = %s, corp = %s\n", getRectID(my_info), getRectX(my_info), getRectY(my_info), getRectWIDTH(my_info), getRectHEIGHT(my_info), getRectEDGE(my_info), getRectFILL(my_info));
                    fprintf(txt, "Retangulo Replicado id = %d, x = %lf, y = %lf, w = %lf, h = %lf, corb = %s, corp = %s\n", getRectID(new_rect), getRectX(new_rect), getRectY(new_rect), getRectWIDTH(new_rect), getRectHEIGHT(new_rect), getRectEDGE(new_rect), getRectFILL(new_rect));
                    id++;
                    strcpy(check, "CHEIO");
                } 
                break;

            case 3:
                marcador = tpLine(my_info, x, y);
                if (marcador) {
                    Info new_line = criaLinha();
                    replicateLine(t, my_info, new_line, dx, dy, id);
                    fprintf(txt, "Linha Base id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, cor = %s\n", getLineID(my_info), getLineX(my_info), getLineY(my_info), getLineFINALX(my_info), getLineFINALY(my_info), getLineCOLOR(my_info));
                    fprintf(txt, "Linha Replicada id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, cor = %s\n", getLineID(new_line), getLineX(new_line), getLineY(new_line), getLineFINALX(my_info), getLineFINALY(new_line), getLineCOLOR(new_line));
                    id++;
                    strcpy(check, "CHEIO");
                } 
                break;

            case 4:
                marcador = tpTxt(my_info, x, y);
                if (marcador) {
                    Info new_text = criaTxt();
                    replicateTxt(t, my_info, new_text, dx, dy, id);
                    fprintf(txt, "Texto Base id = %d, x = %lf, y = %lf, corb = %s, corp = %s, text = %s\n", getTxtID(my_info), getTxtX(my_info), getTxtY(my_info), getTxtEDGE(my_info), getTxtFILL(my_info), getTxtTEXT(my_info));
                    fprintf(txt, "Texto Replicado id = %d, x = %lf, y = %lf, corb = %s, corp = %s, text = %s\n", getTxtID(new_text), getTxtX(new_text), getTxtY(new_text), getTxtEDGE(new_text), getTxtFILL(new_text), getTxtTEXT(new_text));
                    id++;
                    strcpy(check, "CHEIO");
                } 
                break;

            default:
                break;
        }
    }

    preOrderTr(txt, t, getLeft(root), x, y, dx, dy, id, check);
    preOrderTr(txt, t, getCenter(root), x, y, dx, dy, id, check);
    preOrderTr(txt, t, getRight(root), x, y, dx, dy, id, check);
}

void be(Pontos pnts, Tree root, FILE *qry, FILE *txt, FILE *svg, double v) {
    double x, y, w, h;

    fscanf(qry, "%lf", &x);
    fscanf(qry, "%lf", &y);
    fscanf(qry, "%lf", &w);
    fscanf(qry, "%lf", &h);

    fprintf(txt, "\n[*] be %lf %lf %lf %lf \n", x, y, w, h);
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"red\" />\n", x, y, w, h);

    preOrderBe(pnts, svg, txt, root, getRoot(root), x, y, w, h, v);
}

double calcReduc(double v, double areaEquip, double areaSel) {
    double reduc;

    reduc = v * areaEquip / areaSel;
    return reduc;
}

double calcSelArea(double w, double h) {
    double a;

    a = w * h;
    return a;
}

void preOrderBe(Pontos pnts, FILE *svg, FILE *txt, Tree root, Node node, double x, double y, double w, double h, double v) {
    Info fig;
    bool marcador;
    double reduc;
    double selArea = calcSelArea(w, h);

    if (!node) {
        return;
    }

    if (!getRemovedStatus(node)) {
        fig = getInfo(node);

        switch (getCtrl(node)) {
            case 1:
                marcador = isInsideCirc(fig, x, y, w, h);
                if (marcador) {
                    reduc = calcReduc(v, getCircArea(fig), selArea);
                    if (getProtecCirc(fig) > 0) {
                        setProtecCirc(fig, reduc);
                    }
                    printReducCirc(pnts, svg, txt, fig, root, node);
                }
                break;

            case 2:
                marcador = isInsideRect(fig, x, y, w, h);
                if (marcador) {
                    reduc = calcReduc(v, getRectArea(fig), selArea);
                    if (getProtecRect(fig) > 0) {
                        setProtecRect(fig, reduc);
                    }
                    printReducRect(pnts, svg, txt, fig, root, node);
                }
                break;

            case 3:
                marcador = isInsideLine(fig, x, y, w, h);
                if (marcador) {
                    reduc = calcReduc(v, getLineArea(fig), selArea);
                    if (getProtecLine(fig) > 0) {
                        setProtecLine(fig, reduc);
                    }
                    printReducLine(pnts, svg, txt, fig, root, node);
                }
                break;

            case 4:
                marcador = isInsideText(fig, x, y, w, h);
                if (marcador) {
                    reduc = calcReduc(v, 0.1, selArea);
                    if (getProtecTxt(fig) > 0) {
                        setProtecTxt(fig, reduc);
                    }
                    printReducText(pnts, svg, txt, fig, root, node);
                }
                break;

            default:
                break;
        }
    }

    preOrderBe(pnts, svg, txt, root, getLeft(node), x, y, w, h, v);
    preOrderBe(pnts, svg, txt, root, getCenter(node), x, y, w, h, v);
    preOrderBe(pnts, svg, txt, root, getRight(node), x, y, w, h, v);
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

void printReducCirc(Pontos pnts, FILE *svg, FILE *txt, Info circ, Tree root, Node node) {
    double r = 3.50;
    char color[] = "red";

    if (getRemovedStatus(node)) {
        return;
    }

    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getCircX(circ), getCircY(circ), r, color, color);
    fprintf(txt, "Atingido Círculo id = %d, x = %lf, y = %lf, r = %lf, proteção = %lf ", getCircID(circ), getCircX(circ), getCircY(circ), getCircRADIUS(circ), getProtecCirc(circ));
    // printf("protec c %lf\n", getProtecCirc(circ));

    if (getProtecCirc(circ) <= 0) {
        updateInativ(pnts, 75);
        // removeNode(root, getRoot(root), getTX(node), getTY(node), getCircID(circ));
        markRemoved(root, node);
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

void printReducRect(Pontos pnts, FILE *svg, FILE *txt, Info rect, Tree root, Node node) {
    double r = 2.05;
    char color[] = "red";

    if (getRemovedStatus(node)) {
        return;
    }

    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getRectX(rect), getRectY(rect), r, color, color);
    fprintf(txt, "Atingido retângulo id = %d, x = %lf, y = %lf, w = %lf, h = %lf proteção = %lf ", getRectID(rect), getRectX(rect), getRectY(rect), getRectWIDTH(rect), getRectHEIGHT(rect), getProtecRect(rect));
    // printf("protec r %lf\n", getProtecRect(rect));

    if (getProtecRect(rect) <= 0) {
        updateInativ(pnts, 90);
        // removeNode(root, getRoot(root), getTX(node), getTY(node), getRectID(rect));
        markRemoved(root, node);
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
    return false;
}

void printReducLine(Pontos pnts, FILE *svg, FILE *txt, Info line, Tree root, Node node) {
    double r = 2.05;
    char color[] = "red";

    if (getRemovedStatus(node)) {
        return;
    }

    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getLineX(line), getLineY(line), r, color, color);
    fprintf(txt, "Atingido linha id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf proteção = %lf ", getLineID(line), getLineX(line), getLineY(line), getLineFINALX(line), getLineFINALY(line), getProtecLine(line));
    // printf("protec l %lf\n", getProtecLine(line));

    if (getProtecLine(line) <= 0) {
        updateInativ(pnts, 50);
        // removeNode(root, getRoot(root), getTX(node), getTY(node), getLineID(line));
        markRemoved(root, node);
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

void printReducText(Pontos pnts, FILE *svg, FILE *txt, Info text, Tree root, Node node) {
    double r = 2.05;
    char color[] = "red";

    if (getRemovedStatus(node)) {
        return;
    }

    fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", getTxtX(text), getTxtY(text), r, color, color);
    fprintf(txt, "Atingido texto id = %d, x = %lf, y = %lf, proteção = %lf ", getTxtID(text), getTxtX(text), getTxtY(text), getProtecTxt(text));
    // printf("protec t %lf\n", getProtecTxt(text));

    if (getProtecTxt(text) <= 0) {
        updateInativ(pnts, 30);
        // removeNode(root, getRoot(root), getTX(node), getTY(node), getTxtID(text));
        markRemoved(root, node);
        fprintf(txt, "REMOVIDO\n");
    } else {
        fprintf(txt, "\n");
    }
}
