#include "qry.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"
#include "fila_circ.h"
#include "line.h"
#include "list.h"
#include "rectangle.h"
#include "svg.h"
#include "system.h"
#include "text.h"

struct pg {
    double x;
    double y;
};
typedef struct pg Ponto;

void readComands(FILE *qry_dir, Lista r, Lista c, Lista l, Lista t, FILE *svg, FILE *txt) {
    printf("\n--- INICIO READ QRY ---\n");
    Fila_Circular poligono = criaFila(200);
    Lista selecRec = criaLista();
    Lista selecCirc = criaLista();
    Lista selecLine = criaLista();
    Lista selecTxt = criaLista();

    while (!feof(qry_dir)) {
        char *comando[10][30];
        char *eptr;

        fscanf(qry_dir, "%s", comando);

        if (strcmp(comando, "inp") == 0) {  // Inserir no poligono (fila insere no fim)
            printf("\n%s\n", comando);      // *FEITO* mas adaptar para de fato inserir no svg
            inp(txt, qry_dir, comando, poligono, r, c, l, t);

        } else if (strcmp(comando, "rmp") == 0) {  // Remove uma coordenada do poligono (primeira da fila)
            printf("\n%s\n", comando);             // *FEITO* mas adaptar para de fato remover do svg
            rmp(txt, comando, poligono);

        } else if (strcmp(comando, "pol") == 0) {  // Produz um conjunto de linhas e insere no poligono
            printf("\n%s\n", comando);
            pol(txt, qry_dir, comando, eptr);

        } else if (strcmp(comando, "clp") == 0) {  // Remove todas as coordenadas
            printf("\n%s\n", comando);             // *FEITO*
            clp(txt, poligono);

        } else if (strcmp(comando, "sel") == 0) {  // Seleciona as figuras inteiramente dentro da regiao
            printf("\n%s\n", comando);             // *FEITO*
            sel(txt, svg, qry_dir, comando, eptr, selecRec, selecCirc, selecLine, selecTxt, r, c, l, t);

        } else if (strcmp(comando, "sel+") == 0) {  // bla bla
            printf("\n%s\n", comando);
            selplus(txt, qry_dir, comando, eptr);

        } else if (strcmp(comando, "dels") == 0) {  // Remove todas as figuras selecionadas
            printf("\n%s\n", comando);              // *FEITO*
            dels(txt, selecRec, selecCirc, selecLine, selecTxt);

        } else if (strcmp(comando, "dps") == 0) {  // Cria novas formas e bla bla
            printf("\n%s\n", comando);             // *FEITO* 
            dps(txt, svg, qry_dir, comando, eptr, selecRec, selecCirc, selecLine, selecTxt);

        } else if (strcmp(comando, "ups") == 0) {  // Altera cor e translada as figuras selecionadas
            printf("\n%s\n", comando);
            ups(txt, svg, qry_dir, comando, eptr, selecRec, selecCirc, selecLine, selecTxt);
        }
    }

    fclose(qry_dir);
    fclose(txt);
    free(poligono);
    // free(selecRec);
    // free(selecCirc);
    // free(selecLine);
    // free(selecTxt);
}

void inp(FILE *txt, FILE *arq, char *infos[], Fila_Circular q, Lista r, Lista c, Lista l, Lista t) {
    printf("--- INICIO INP ---\n");
    int i, id_aux;
    double x, y;
    Item pnt;

    fscanf(arq, "%s", infos);
    i = atoi(infos);

    fprintf(txt, "\n[*] inp\n");

    for (Cell auxC1 = getFirst(r); auxC1 != NULL; auxC1 = getNext(r, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        id_aux = getRectID(auxI1);
        if (i == id_aux) {
            x = getRectX(auxI1);
            y = getRectY(auxI1);
            pnt = criaPonto(x, y);

            enfila_circ(q, pnt);
            fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x, y);
        }
    }

    for (Cell auxC2 = getFirst(c); auxC2 != NULL; auxC2 = getNext(c, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        id_aux = getCircID(auxI2);
        if (i == id_aux) {
            x = getCircX(auxI2);
            y = getCircY(auxI2);
            pnt = criaPonto(x, y);

            enfila_circ(q, pnt);
            fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x, y);
        }
    }

    for (Cell auxC3 = getFirst(t); auxC3 != NULL; auxC3 = getNext(t, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        id_aux = getTxtID(auxI3);
        if (i == id_aux) {
            x = getTxtX(auxI3);
            y = getTxtY(auxI3);
            pnt = criaPonto(x, y);

            enfila_circ(q, pnt);
            fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x, y);
        }
    }

    for (Cell auxC4 = getFirst(l); auxC4 != NULL; auxC4 = getNext(l, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        id_aux = getLineID(auxI4);
        if (i == id_aux) {
            x = getLineX(auxI4);
            y = getLineY(auxI4);
            double x2 = getLineFINALX(auxI4);
            double y2 = getLineFINALY(auxI4);
            if (x < x2) {
                pnt = criaPonto(x, y);
                fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x, y);
            } else if (x2 < x) {
                pnt = criaPonto(x2, y2);
                fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x2, y2);
            } else if (x == x2) {
                if (y < y2) {
                    pnt = criaPonto(x, y);
                    fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x, y);
                } else if (y2 < y) {
                    pnt = criaPonto(x2, y2);
                    fprintf(txt, "Inserido ponto em: x = %lf, y = %lf\n", x2, y2);
                }
            }
            enfila_circ(q, pnt);
        }
    }
    // printf("%d\n", i);
}

Item criaPonto(double x, double y) {
    Ponto *new_point = calloc(1, sizeof(Ponto));

    new_point->x = x;
    new_point->y = y;

    //printf("npx %lf\n", new_point->x);
    //printf("npy %lf\n", new_point->y);

    return new_point;
}

void rmp(FILE *txt, char *infos[], Fila_Circular q) {
    printf("--- INICIO RMP ---\n");
    Item aux = desenfila_circ(q);
    Ponto *pnt = (Ponto*) aux;
    double x, y;
    x = pnt->x;
    y = pnt->y;

    fprintf(txt, "\n[*] rmp\n");
    fprintf(txt, "Removido ponto de coordenadas: x = %lf, y = %lf\n", x, y);
}

void pol(FILE *txt, FILE *arq, char *infos[], char *eptr) {
    printf("--- INICIO POL ---\n");
    int i;
    double d, e;
    char corb[15], corp[15];

    fscanf(arq, "%s", infos);
    i = atoi(infos);

    fscanf(arq, "%s", infos);
    d = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    e = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(corp, infos);

    fprintf(txt, "\n[*] pol\n");
    // printf("id %d\n", i);
    // printf("d %lf\n", d);
    // printf("e %lf\n", e);
    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
}

void clp(FILE *txt, Fila_Circular q) {
    printf("--- INICIO CLP ---\n");
    removeTudo(q);
    fprintf(txt, "\n[*] clp\n");
    fprintf(txt, "Todas as coordenadas do polígono corrente removidas\n");
}

void sel(FILE *txt, FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT, Lista r, Lista c, Lista l, Lista t) {
    printf("--- INICIO SEL ---\n");
    double x, y, w, h;
    double radius = 1.75000;
    char stroke[] = "red";
    char fill[] = "white";

    fscanf(arq, "%s", infos);
    x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    w = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    h = strtod(infos, &eptr);

    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"3%%\" />\n", x, y, w, h, stroke, fill);
    fprintf(txt, "\n[*] sel\n");
    fprintf(txt, "Retângulo de seleção: x = %lf, y = %lf, h = %lf, w = %lf, stroke = %s\n", x, y, h, w, stroke);

    for (Cell auxC1 = getFirst(r); auxC1 != NULL; auxC1 = getNext(r, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        double recX = getRectX(auxI1);
        double recY = getRectY(auxI1);
        double recHeight = getRectHEIGHT(auxI1);
        double recWidth = getRectWIDTH(auxI1);

        if (((x + w) >= (recX + recWidth)) && (recX >= x)) {
            if (((y + h) >= (recY + recHeight)) && (recY >= y)) {
                insereFim(sR, auxI1);

                fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", recX, recY, radius, stroke, fill);
                fprintf(txt, "Selecionado: Retângulo x = %lf, y = %lf, height = %lf, width = %lf\n", recX, recY, recHeight, recWidth);
            }
        }
    }

    for (Cell auxC2 = getFirst(c); auxC2 != NULL; auxC2 = getNext(c, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        double circX = getCircX(auxI2);
        double circY = getCircY(auxI2);
        double circRadius = getCircRADIUS(auxI2);

        if ((x + w) >= (circX + circRadius) && (x) <= (circX - circRadius)) {
            if ((y + h) >= (circY + circRadius) && (y) <= (circY - circRadius)) {
                insereFim(sC, auxI2);

                fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", circX, circY, radius, stroke, fill);
                fprintf(txt, "Selecionado: Círculo x = %lf, y = %lf, radius = %lf\n", circX, circY, circRadius);
            }
        }
    }

    for (Cell auxC3 = getFirst(t); auxC3 != NULL; auxC3 = getNext(t, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        double txtX = getTxtX(auxI3);
        double txtY = getTxtY(auxI3);

        if ((x + w) >= (txtX) && (y + h) >= (txtY)) {
            insereFim(sT, auxI3);

            fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", txtX, txtY, radius, stroke, fill);
            fprintf(txt, "Selecionado: Texto x = %lf, y = %lf\n", txtX, txtY);
        }
    }

    for (Cell auxC4 = getFirst(l); auxC4 != NULL; auxC4 = getNext(l, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        double linX1 = getLineX(auxI4);
        double linY1 = getLineY(auxI4);
        double linX2 = getLineFINALX(auxI4);
        double linY2 = getLineFINALY(auxI4);

        if ((x + w) >= (linX1) && (y + h) >= (linY1)) {
            if ((x + w) >= (linX2) && (y + h) >= (linY2)) {
                insereFim(sL, auxI4);

                fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", linX1, linY1, radius, stroke, fill);
                fprintf(txt, "Selecionado: Linha x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf\n", linX1, linY1, linX2, linY2);
            }
        }
    }

    // printf("x %lf\n", x);
    // printf("y %lf\n", y);
    // printf("w %lf\n", w);
    // printf("h %lf\n", h);
}

void selplus(FILE *txt, FILE *arq, char *infos[], char *eptr) {
    printf("--- INICIO SEL+ ---\n");
    double x, y, w, h;

    fscanf(arq, "%s", infos);
    x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    w = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    h = strtod(infos, &eptr);

    fprintf(txt, "\n[*] sel+\n");
    // printf("x %lf\n", x);
    // printf("y %lf\n", y);
    // printf("w %lf\n", w);
    // printf("h %lf\n", h);
}

void dels(FILE *txt, Lista sR, Lista sC, Lista sL, Lista sT) {
    printf("--- INICIO DELS ---\n");
    removeAll(sR);
    removeAll(sC);
    removeAll(sL);
    removeAll(sT);

    fprintf(txt, "\n[*] dels\n");
    fprintf(txt, "Removidas todas as figuras selecionadas do Banco de Dados\n");
}

void dps(FILE *txt, FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT) {
    printf("--- INICIO DPS ---\n");
    int i;
    double dx, dy, aux1, aux2;
    double final_dx, final_dy;
    char corb[15], corp[15], aux3[100], aux4[1];

    fscanf(arq, "%s", infos);
    i = atoi(infos);

    fscanf(arq, "%s", infos);
    dx = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    dy = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    strcpy(corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(corp, infos);

    fprintf(txt, "\n[*] dps\n");

    for (Cell auxC1 = getFirst(sR); auxC1 != NULL; auxC1 = getNext(sR, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        final_dx = getRectX(auxI1) + dx;
        final_dy = getRectY(auxI1) + dy;
        aux1 = getRectHEIGHT(auxI1);
        aux2 = getRectWIDTH(auxI1);

        fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"40%%\" />\n", i, final_dx, final_dy, aux2, aux1, corb, corp);
        fprintf(txt, "Criado retângulo: id = %d, x = %lf, y = %lf, w = %lf, h = %lf, stroke = %s, fill = %s\n", i, final_dx, final_dy, aux2, aux1, corb, corp);

        i++;
    }

    for (Cell auxC2 = getFirst(sC); auxC2 != NULL; auxC2 = getNext(sC, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        final_dx = getCircX(auxI2) + dx;
        final_dy = getCircY(auxI2) + dy;
        aux1 = getCircRADIUS(auxI2);
        
        fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"40%%\" />\n", i, final_dx, final_dy, aux1, corb, corp);
        fprintf(txt, "Criado Círculo: id = %d, x = %lf, y = %lf, r = %lf, stroke = %s, fill = %s\n", i, final_dx, final_dy, aux1, corb, corp);

        i++;
    }

    for (Cell auxC3 = getFirst(sT); auxC3 != NULL; auxC3 = getNext(sT, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        final_dx = getTxtX(auxI3) + dx;
        final_dy = getTxtY(auxI3) + dy;
        strcpy(aux3, getTxtTEXT(auxI3));
        strcpy(aux4, getTxtANCHOR(auxI3));

        fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"40%%\" >\"%s\"</text>\n", i, final_dx, final_dy, aux4, corb, corp, aux3);
        fprintf(txt, "Criado Texto: id = %d, x = %lf, y = %lf, stroke = %s, fill = %s\n", i, final_dx, final_dy, corb, corp);

        i++;        
    }

    for (Cell auxC4 = getFirst(sL); auxC4 != NULL; auxC4 = getNext(sL, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        final_dx = getLineX(auxI4) + dx;
        final_dy = getLineY(auxI4) + dy;
        aux1 = getLineFINALX(auxI4) + dx;
        aux2 = getLineFINALY(auxI4) + dy;

        fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"50%%\" />\n", i, final_dx, final_dy, aux1, aux2, corb);
        fprintf(txt, "Criada Linha: id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, color = %s\n", i, final_dx, final_dy, aux1, aux2, corb);

        i++;
    }

    // printf("id %d\n", i);
    // printf("dx %lf\n", dx);
    // printf("dy %lf\n", dy);
    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
}

void ups(FILE *txt, FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT) {
    printf("--- INICIO DPS ---\n");
    int n;
    double dx, dy;
    char corb[15], corp[15];

    fscanf(arq, "%s", infos);
    strcpy(corb, infos);

    fscanf(arq, "%s", infos);
    strcpy(corp, infos);

    fscanf(arq, "%s", infos);
    dx = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    dy = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    n = atoi(infos);

    fprintf(txt, "\n[*] ups\n");

    // INTEGRAR N NA FUNÇÃO, POIS NÃO DEVO ALTERAR TOAS AS FIGURAS NO BANCO DE DADOS
    //  APENAS ALGUMAS COM RELAÇÃO A N

    for (Cell auxC1 = getFirst(sR); auxC1 != NULL; auxC1 = getNext(sR, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        setrectEDGE(auxI1, corb);
        setrectFILL(auxI1, corp);
        setrectX(auxI1, dx);
        setrectY(auxI1, dy);

        drawRectangle(svg, auxI1);
        fprintf(txt, "Retângulo atualizado: dx = %lf, dy = %lf, stroke = %s, fill = %s\n", dx, dy, corb, corp);
    }

    for (Cell auxC2 = getFirst(sC); auxC2 != NULL; auxC2 = getNext(sC, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        setcircEDGE(auxI2, corb);
        setcircFILL(auxI2, corp);
        setcircX(auxI2, dx);
        setcircY(auxI2, dy);

        drawCircle(svg, auxI2);
        fprintf(txt, "Círculo atualizado: dx = %lf, dy = %lf, stroke = %s, fill = %s\n", dx, dy, corb, corp);
    }

    for (Cell auxC3 = getFirst(sT); auxC3 != NULL; auxC3 = getNext(sT, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        settxtEDGE(auxI3, corb);
        settxtFILL(auxI3, corp);
        settxtX(auxI3, dx);
        settxtY(auxI3, dy);

        drawText(svg, auxI3);
        fprintf(txt, "Texto atualizado: dx = %lf, dy = %lf, stroke = %s, fill = %s\n", dx, dy, corb, corp);
    }

    for (Cell auxC4 = getFirst(sL); auxC4 != NULL; auxC4 = getNext(sL, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        setlineCOLOR(auxI4, corb);
        setlineX(auxI4, dx);
        setlineY(auxI4, dy);

        drawLine(svg, auxI4);
        fprintf(txt, "Linha atualizada: dx = %lf, dy = %lf, color = %s\n", dx, dy, corb);
    }

    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
    // printf("dx %lf\n", dx);
    // printf("dy %lf\n", dy);
    // printf("n %d\n", n);
}
