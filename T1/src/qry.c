#include "qry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <fila_circ.h>

void readComands (FILE *qry_dir) {
    printf("--- INICIO READ QRY ---\n");

    while (!feof(qry_dir)) {
        char *comando[10][20];
        char *eptr;

        fscanf(qry_dir, "%s", comando);

        if (strcmp(comando, "inp") == 0) { //Inserir no poligono (fila insere no fim)


        } else if (strcmp(comando, "rmp") == 0) { //Remove uma coordenada do poligono (primeira da fila)


        } else if (strcmp(comando, "pol") == 0) { //PRoduz um conjunto de linhas e insere no poligono


        } else if (strcmp(comando, "clp") == 0) { //Remove todas as coordenadas


        } else if (strcmp(comando, "sel") == 0) { //Seleciona as figuras inteiramente dentro da regiao 


        } else if (strcmp(comando, "sel+") == 0) { //bla bla


        } else if (strcmp(comando, "dels") == 0) { //Remove todas as figuras selecionadas


        } else if (strcmp(comando, "dps") == 0) { //Cria novas formas e bla bla


        } else if (strcmp(comando, "ups") == 0) { //Altera cor ou translada as figuras selcionadas


        }

    }
}