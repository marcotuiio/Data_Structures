#include "qry.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila_circ.h"

void readComands(FILE *qry_dir) {
    printf("\n--- INICIO READ QRY ---\n");

    Fila_Circular poligono = criaFila(200);

    while (!feof(qry_dir)) {
        char *comando[10][30];
        char *eptr;

        fscanf(qry_dir, "%s", comando);

        if (strcmp(comando, "inp") == 0) {  // Inserir no poligono (fila insere no fim)
            printf("\n%s\n", comando);
            inp(qry_dir, comando, poligono);

        } else if (strcmp(comando, "rmp") == 0) {  // Remove uma coordenada do poligono (primeira da fila)
            printf("\n%s\n", comando);
            rmp(comando, poligono);

        } else if (strcmp(comando, "pol") == 0) {  // Produz um conjunto de linhas e insere no poligono
            printf("\n%s\n", comando);
            pol(qry_dir, comando, eptr);

        } else if (strcmp(comando, "clp") == 0) {  // Remove todas as coordenadas
            printf("\n%s\n", comando);
            clp(poligono);

        } else if (strcmp(comando, "sel") == 0) {  // Seleciona as figuras inteiramente dentro da regiao
            printf("\n%s\n", comando);
            sel(qry_dir, comando, eptr);

        } else if (strcmp(comando, "sel+") == 0) {  // bla bla
            printf("\n%s\n", comando);
            selplus(qry_dir, comando, eptr);

        } else if (strcmp(comando, "dels") == 0) {  // Remove todas as figuras selecionadas
            printf("\n%s\n", comando);
            dels();

        } else if (strcmp(comando, "dps") == 0) {  // Cria novas formas e bla bla
            printf("\n%s\n", comando);
            dps(qry_dir, comando, eptr);

        } else if (strcmp(comando, "ups") == 0) {  // Altera cor ou translada as figuras selcionadas
            printf("\n%s\n", comando);
            ups(qry_dir, comando, eptr);
        }
    }
}

void inp(FILE *arq, char *infos[], Fila_Circular q) {
    printf("--- INICIO INP ---\n");
    int i;

    fscanf(arq, "%s", infos);
    i = atoi(infos);

    enfila_circ(q, i);

    printf("%d\n", i);
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

    printf("id %d\n", i);
    printf("d %lf\n", d);
    printf("e %lf\n", e);
    printf("corb %s\n", corb);
    printf("corp %s\n", corp);
}

void clp(Fila_Circular q) {  // colocar fila para dar free
    printf("--- INICIO CLP ---\n");

    removeTudo(q);
}

void sel(FILE *arq, char *infos[], char *eptr) {
    printf("--- INICIO SEL ---\n");
    double x, y, w, h;

    fscanf(arq, "%s", infos);
    x = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    y = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    w = strtod(infos, &eptr);

    fscanf(arq, "%s", infos);
    h = strtod(infos, &eptr);

    printf("x %lf\n", x);
    printf("y %lf\n", y);
    printf("w %lf\n", w);
    printf("h %lf\n", h);
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

    printf("x %lf\n", x);
    printf("y %lf\n", y);
    printf("w %lf\n", w);
    printf("h %lf\n", h);
}

void dels() {
    printf("--- INICIO DELS ---\n");
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

    printf("id %d\n", i);
    printf("dx %lf\n", dx);
    printf("dy %lf\n", dy);
    printf("corb %s\n", corb);
    printf("corp %s\n", corp);
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

    printf("corb %s\n", corb);
    printf("corp %s\n", corp);
    printf("dx %lf\n", dx);
    printf("dy %lf\n", dy);
    printf("n %d\n", n);
}