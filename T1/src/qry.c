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

void readComands(FILE *qry_dir, Lista r, Lista c, Lista l, Lista t, FILE *svg) {
    printf("\n--- INICIO READ QRY ---\n");
    Fila_Circular poligono = criaFila(200);
    Lista BancoDeDados = criaLista();

    while (!feof(qry_dir)) {
        char *comando[10][30];
        char *eptr;

        fscanf(qry_dir, "%s", comando);

        if (strcmp(comando, "inp") == 0) {  // Inserir no poligono (fila insere no fim) 
            printf("\n%s\n", comando);      // *FEITO*
            inp(qry_dir, comando, poligono);

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
            sel(svg, qry_dir, comando, eptr, BancoDeDados, r, c, l, t);

        } else if (strcmp(comando, "sel+") == 0) {  // bla bla
            printf("\n%s\n", comando);
            selplus(qry_dir, comando, eptr);

        } else if (strcmp(comando, "dels") == 0) {  // Remove todas as figuras selecionadas
            printf("\n%s\n", comando);              // *FEITO*    
            dels(BancoDeDados);

        } else if (strcmp(comando, "dps") == 0) {  // Cria novas formas e bla bla
            printf("\n%s\n", comando);
            dps(qry_dir, comando, eptr);

        } else if (strcmp(comando, "ups") == 0) {  // Altera cor ou translada as figuras selcionadas
            printf("\n%s\n", comando);
            ups(qry_dir, comando, eptr);
        }
    }

    fclose(qry_dir);
}

void inp(FILE *arq, char *infos[], Fila_Circular q) {
    printf("--- INICIO INP ---\n");
    int i;

    fscanf(arq, "%s", infos);
    i = atoi(infos);

    enfila_circ(q, i);

    // printf("%d\n", i);
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

void sel(FILE *svg, FILE *arq, char *infos[], char *eptr, Lista selec, Lista r, Lista c, Lista l, Lista t) {
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
                insereFim(selec, auxI1);

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
                insereFim(selec, auxI2);

                fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"25%%\" />\n", circX, circY, radius, stroke, fill);
            }
        }
    }

    for (Cell auxC3 = getFirst(t); auxC3 != NULL; auxC3 = getNext(t, auxC3)) {
        Item auxI3 = getInfo(auxC3);

        double txtX = getTxtX(auxI3);
        double txtY = getTxtY(auxI3);

        if ((x + w) >= (txtX) && (y + h) >= (txtY)) {
            insereFim(selec, auxI3);

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
                insereFim(selec, auxI4);

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

void dels(Lista selec) {
    printf("--- INICIO DELS ---\n");
    removeAll(selec);
}

void dps(FILE *arq, char *infos[], char *eptr) {
    printf("--- INICIO DPS ---\n");
    int i;
    double dx, dy;
    char corb[15], corp[15];

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

    // printf("id %d\n", i);
    // printf("dx %lf\n", dx);
    // printf("dy %lf\n", dy);
    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
}

void ups(FILE *arq, char *infos[], char *eptr) {
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

    // printf("corb %s\n", corb);
    // printf("corp %s\n", corp);
    // printf("dx %lf\n", dx);
    // printf("dy %lf\n", dy);
    // printf("n %d\n", n);
}
