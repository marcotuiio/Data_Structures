#include "geo.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "text.h"
#include "tree.h"
#include "list.h"

void readGeo(char *bedGeo) {  // FAZER GEO RETORNAR UMA ARVORE ???/
    FILE *geo = openGeo(bedGeo);
    char tipo[5];
    Lista my_list = createList();

    while (!feof(geo)) {
        fscanf(geo, "%s", tipo);

        if (strcmp(tipo, "c") == 0) {
            Info circle = criaCirc();
            buildCircle(geo, circle, my_list);            

        } else if (strcmp(tipo, "r") == 0) {
            Info rect = criaRec();
            buildRectangle(geo, rect, my_list);

        } else if (strcmp(tipo, "l") == 0) {
            Info line = criaLinha();
            buildLine(geo, line, my_list);

        } else if (strcmp(tipo, "t") == 0) {
            Info text = criaTxt();
            buildText(geo, text, my_list);
        }
    }
    fclose(geo);
    // TRANSFORMAR LISTA EM ARVORE
    // Tree my_tree = createTree();
    // function List-to-Tree(my_list, my_tree);
    freeList(my_list);

    // return my_tree
}

FILE *openGeo(char *bedGeo) {
    FILE *geo = fopen(bedGeo, "r");
    if (geo == NULL) {
        printf("ERRO NA CRIAÇÃO DO GEO\n");
        exit(1);
    }
    return geo;
}