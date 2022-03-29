#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "rectangle.h"
#include "circle.h"

struct text {
    char type;
    int id;
    float x;
    float y;
    char anchor;
    char *corp;
    char *corb;
    char *text;
};
typedef struct text GText;

struct line {
    char type;
    int id;
    float initX;
    float initY;
    float finalX;
    float finalY;
    char *color;
};
typedef struct line GLine;

Lista buildGeometricForms(FILE *arq) {
    printf("\nInicio Build GeoForms\n");
    Lista listRETANGULO = criaLista();
    Lista listCIRCULO = criaLista();

    Circle1 circle = criaCirc();
    Rectangle1 rectangle = criaRec();

    while(!feof(arq)) {
        char infos[10];
        char *eptr;
        fscanf(arq, "%s", infos);

         if (infos[0] == 'c' && infos[1] == NULL) {
            Item item = buildCircle(arq, circle, infos, eptr);
            insereInicio(listCIRCULO, item);

         }else if(infos[0] == 'r' && infos[1] == NULL) {
            Item item = buildRectangle(arq, rectangle, infos, eptr);
            insereInicio(listRETANGULO, item);
         }
    }

    float aux = getRectHEIGHT(rectangle);
    printf("\nteste %f\n", aux);
    getLenght(listCIRCULO);
    getLenght(listRETANGULO);
}