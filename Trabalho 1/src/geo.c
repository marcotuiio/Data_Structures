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
        char infos[10];
        char *eptr;
        fscanf(arq, "%s", infos);

        if (infos[0] == 'c' && infos[1] == NULL){
        Item item = buildCircle(arq, circle, infos, eptr);
        insereFim(listCIRCULO, item);

        }else if (infos[0] == 'r' && infos[1] == NULL){
        Item item = buildRectangle(arq, rectangle, infos, eptr);
        insereFim(listRETANGULO, item);

        }else if (infos[0] == 't' && infos[1] == NULL){
        Item item = buildText(arq, text, infos, eptr);
        insereFim(listTEXTO, item);

        }else if (infos[0] == 'l' && infos[1] == NULL){
        Item item = buildLine(arq, line, infos, eptr);
        insereFim(listLINHA, item); 
        }
    }
    //aqui começam os erros!
    //nao consigo extrair o valores corretamente
    //Decobrir o que ta errado com as gets
    Rectangle1 aux = getFirst(listRETANGULO);
    double x = getRectX(aux);
    printf("\ntestex %lf\n", x);
    double y = getRectY(aux);
    printf("\ntestey %lf\n", y);

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