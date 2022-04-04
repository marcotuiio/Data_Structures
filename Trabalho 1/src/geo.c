#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include "text.h"
#include "svg.h"

Lista buildGeometricForms(FILE *arq) {
    printf("\nInicio Build GeoForms\n");
    Lista listRETANGULO = criaLista();
    Lista listCIRCULO = criaLista();
    Lista listTEXTO = criaLista();
    Lista listLINHA = criaLista();

    Circle1 circle = criaCirc();
    Rectangle1 rectangle = criaRec();
    Text1 text = criaTxt();
    Line1 line = criaLinha();

    while(!feof(arq)) {
        char *infos[10][30];
        char *eptr;

        fscanf(arq, "%s", infos);

        if (strcmp (infos[0], "c") == 0){
        Item item = buildCircle(arq, circle, *infos, eptr);
        insereFim(listCIRCULO, item);

        }else if (strcmp (infos[0], "r") == 0){
        Item item = buildRectangle(arq, rectangle, *infos, eptr);
        insereFim(listRETANGULO, item);

        }else if (strcmp (infos[0], "t") == 0){
        Item item = buildText(arq, text, *infos, eptr);
        insereFim(listTEXTO, item);

        }else if (strcmp (infos[0], "l") == 0){
        Item item = buildLine(arq, line, *infos, eptr);
        insereFim(listLINHA, item); 
        }
    }

    Rectangle1 aux = getFirst(listRETANGULO);
    int id = getRectID(aux);
    printf("\nid %d\n", id);
    double x = getRectX(aux);
    printf("testex %lf\n", x);
    double y = getRectY(aux);
    printf("testey %lf\n", y);

    getLenght(listCIRCULO);
    getLenght(listRETANGULO);
    getLenght(listLINHA);
    getLenght(listTEXTO);

    writeSvg(listRETANGULO, listCIRCULO, listTEXTO, listLINHA);

    // free(listCIRCULO);
    // free(listRETANGULO);
    // free(listTEXTO);
    // free(listLINHA);
}