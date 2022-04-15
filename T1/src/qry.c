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

void readComands(FILE *qry_dir, Lista r, Lista c, Lista l, Lista t, FILE *svg, char *diroutput) {
    printf("\n--- INICIO READ QRY ---\n");
    Fila_Circular poligono = criaFila(200);
    Lista selecRec = criaLista();
    Lista selecCirc = criaLista();
    Lista selecLine = criaLista();
    Lista selecTxt = criaLista();

    FILE *txt = createTxt(diroutput);

    while (!feof(qry_dir)) {
        char *comando[10][30];
        char *eptr;

        fscanf(qry_dir, "%s", comando);

        if (strcmp(comando, "inp") == 0) {  // Inserir no poligono (fila insere no fim)
            printf("\n%s\n", comando);      // *FEITO*
            inp(qry_dir, comando, poligono, r, c, l, t);

        } else if (strcmp(comando, "rmp") == 0) {  // Remove uma coordenada do poligono (primeira da fila)
            printf("\n%s\n", comando);             // *FEITO*
            rmp(comando, poligono);

        } else if (strcmp(comando, "pol") == 0) {  // Produz um conjunto de linhas e insere no poligono
            printf("\n%s\n", comando);
            pol(qry_dir, comando, eptr);

        } else if (strcmp(comando, "clp") == 0) {  // Remove todas as coordenadas
            printf("\n%s\n", comando);             // *FEITO*
            clp(poligono);

        } else if (strcmp(comando, "sel") == 0) {  // Seleciona as figuras inteiramente dentro da regiao
            printf("\n%s\n", comando);             // *FEITO*
            sel(svg, qry_dir, comando, eptr, selecRec, selecCirc, selecLine, selecTxt, r, c, l, t);

        } else if (strcmp(comando, "sel+") == 0) {  // bla bla
            printf("\n%s\n", comando);
            selplus(qry_dir, comando, eptr);

        } else if (strcmp(comando, "dels") == 0) {  // Remove todas as figuras selecionadas
            printf("\n%s\n", comando);              // *FEITO*
            dels(selecRec, selecCirc, selecLine, selecTxt);

        } else if (strcmp(comando, "dps") == 0) {  // Cria novas formas e bla bla
            printf("\n%s\n", comando);             // *FEITO* 
            dps(svg, qry_dir, comando, eptr, selecRec, selecCirc, selecLine, selecTxt);

        } else if (strcmp(comando, "ups") == 0) {  // Altera cor e translada as figuras selecionadas
            printf("\n%s\n", comando);
            ups(svg, qry_dir, comando, eptr, selecRec, selecCirc, selecLine, selecTxt);
        }
    }

    fclose(qry_dir);
    free(poligono);
    free(selecRec);
    free(selecCirc);
    free(selecLine);
    free(selecTxt);
}

FILE *createTxt(char *output) {
    char toRemove[] = ".svg";
    char *txtdir = malloc(strlen(output));
    stpcpy(txtdir, strtok(output, toRemove));
    strcat(txtdir, ".txt");

    FILE *txt = fopen(txtdir, "w");

    printf("\nCriado txt com sucesso: %s\n", txtdir);

    return txt;
}

void inp(FILE *arq, char *infos[], Fila_Circular q, Lista r, Lista c, Lista l, Lista t) {
    printf("--- INICIO INP ---\n");
    int i, id_aux;
    double x, y;
    Item pnt;

    fscanf(arq, "%s", infos);
    i = atoi(infos);

    for (Cell auxC1 = getFirst(r); auxC1 != NULL; auxC1 = getNext(r, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        id_aux = getRectID(auxI1);
        if (i == id_aux) {
            x = getRectX(auxI1);
            y = getRectY(auxI1);
            pnt = criaPonto(x, y);

            enfila_circ(q, pnt);
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
        }
    }

    for (Cell auxC4 = getFirst(l); auxC4 != NULL; auxC4 = getNext(l, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        id_aux = getLineID(auxI4);
        if (i == id_aux) {
            x = getLineX(auxI4);
            y = getLineY(auxI4);
            pnt = criaPonto(x, y);

            enfila_circ(q, pnt);
        }
    }
    // printf("%d\n", i);
}

Item criaPonto(double x, double y) {
    Ponto *new_point = calloc(1, sizeof(Ponto));

    new_point->x = x;
    new_point->y = y;

    printf("npx %lf\n", new_point->x);
    printf("npy %lf\n", new_point->y);

    return new_point;
}

void rmp(char *infos[], Fila_Circular q) {
    printf("--- INICIO RMP ---\n");
    desenfila_circ(q);
}

void pol(FILE *arq, char *infos[], char *eptr) {
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

    // printf("id %d\n", i);
    // printf("d %lf\n", d);
    // printf("e %lf\n", e);
    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
}

void clp(Fila_Circular q) {
    printf("--- INICIO CLP ---\n");
    removeTudo(q);
}

void sel(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT, Lista r, Lista c, Lista l, Lista t) {
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

    for (Cell auxC1 = getFirst(r); auxC1 != NULL; auxC1 = getNext(r, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        double recX = getRectX(auxI1);
        double recY = getRectY(auxI1);
        double recHeight = getRectHEIGHT(auxI1);
        double recWidth = getRectWIDTH(auxI1);

        if ((x + recX + recWidth <= w) && (recX >= x)) {
            if ((y + recY + recHeight <= h) && recY >= y) {
                insereFim(sR, auxI1);

                fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", recX, recY, radius, stroke, fill);
            }
        }
    }

    for (Cell auxC2 = getFirst(c); auxC2 != NULL; auxC2 = getNext(c, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        double circX = getCircX(auxI2);
        double circY = getCircY(auxI2);
        double circRadius = getCircRADIUS(auxI2);

        if ((x + w) >= (circX + circRadius) && (w - x) >= (circX - circRadius)) {
            if ((y + h) >= (circY + circRadius) && (h - y) >= (circY - circRadius)) {
                insereFim(sC, auxI2);

                fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", circX, circY, radius, stroke, fill);
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
            }
        }
    }

    // printf("x %lf\n", x);
    // printf("y %lf\n", y);
    // printf("w %lf\n", w);
    // printf("h %lf\n", h);
}

void selplus(FILE *arq, char *infos[], char *eptr) {
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

    // printf("x %lf\n", x);
    // printf("y %lf\n", y);
    // printf("w %lf\n", w);
    // printf("h %lf\n", h);
}

void dels(Lista sR, Lista sC, Lista sL, Lista sT) {
    printf("--- INICIO DELS ---\n");
    removeAll(sR);
    removeAll(sC);
    removeAll(sL);
    removeAll(sT);
}

void dps(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT) {
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

    for (Cell auxC1 = getFirst(sR); auxC1 != NULL; auxC1 = getNext(sR, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        final_dx = getRectX(auxI1) + dx;
        final_dy = getRectY(auxI1) + dy;
        aux1 = getRectHEIGHT(auxI1);
        aux2 = getRectWIDTH(auxI1);

        fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"40%%\" />\n", i, final_dx, final_dy, aux2, aux1, corb, corp);
        
        i++;
    }

    for (Cell auxC2 = getFirst(sC); auxC2 != NULL; auxC2 = getNext(sC, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        final_dx = getCircX(auxI2) + dx;
        final_dy = getCircY(auxI2) + dy;
        aux1 = getCircRADIUS(auxI2);
        
        fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"40%%\" />\n", i, final_dx, final_dy, aux1, corb, corp);

        i++;
    }

    for (Cell auxC3 = getFirst(sT); auxC3 != NULL; auxC3 = getNext(sT, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        final_dx = getTxtX(auxI3) + dx;
        final_dy = getTxtY(auxI3) + dy;
        strcpy(aux3, getTxtTEXT(auxI3));
        strcpy(aux4, getTxtANCHOR(auxI3));

        fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"40%%\" >\"%s\"</text>\n", i, final_dx, final_dy, aux4, corb, corp, aux3);

        i++;        
    }

    for (Cell auxC4 = getFirst(sL); auxC4 != NULL; auxC4 = getNext(sL, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        final_dx = getLineX(auxI4) + dx;
        final_dy = getLineY(auxI4) + dy;
        aux1 = getLineFINALX(auxI4) + dx;
        aux2 = getLineFINALY(auxI4) + dy;

        fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"50%%\" />\n", i, final_dx, final_dy, aux1, aux2, corb);

        i++;
    }

    // printf("id %d\n", i);
    // printf("dx %lf\n", dx);
    // printf("dy %lf\n", dy);
    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
}

void ups(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista sR, Lista sC, Lista sL, Lista sT) {
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

    // INTEGRAR N NA FUNÇÃO, POIS NÃO DEVO ALTERAR TOAS AS FIGURAS NO BANCO DE DADOS
    //  APENAS ALGUMAS COM RELAÇÃO A N

    for (Cell auxC1 = getFirst(sR); auxC1 != NULL; auxC1 = getNext(sR, auxC1)) {
        Item auxI1 = getInfo(auxC1);

        setrectEDGE(auxI1, corb);
        setrectFILL(auxI1, corp);
        setrectX(auxI1, dx);
        setrectY(auxI1, dy);

        drawRectangle(svg, auxI1);
    }

    for (Cell auxC2 = getFirst(sC); auxC2 != NULL; auxC2 = getNext(sC, auxC2)) {
        Item auxI2 = getInfo(auxC2);

        setcircEDGE(auxI2, corb);
        setcircFILL(auxI2, corp);
        setcircX(auxI2, dx);
        setcircY(auxI2, dy);

        drawCircle(svg, auxI2);
    }

    for (Cell auxC3 = getFirst(sT); auxC3 != NULL; auxC3 = getNext(sT, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        settxtEDGE(auxI3, corb);
        settxtFILL(auxI3, corp);
        settxtX(auxI3, dx);
        settxtY(auxI3, dy);

        drawText(svg, auxI3);
    }

    for (Cell auxC4 = getFirst(sL); auxC4 != NULL; auxC4 = getNext(sL, auxC4)) {
        Item auxI4 = getInfo(auxC4);

        setlineCOLOR(auxI4, corp);
        setlineX(auxI4, dx);
        setlineY(auxI4, dy);

        drawLine(svg, auxI4);
    }

    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
    // printf("dx %lf\n", dx);
    // printf("dy %lf\n", dy);
    // printf("n %d\n", n);
}
