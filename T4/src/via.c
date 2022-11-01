#include "via.h"
#include "digraph.h"
#include "infos.h"

Digraph readVia(char *bedVia) {
    FILE *via = openVia(bedVia);
    char tipo[5], id[30], ldir[30], lesq[30], nomeEdge[30];
    double x, y, vm, cmp;
    Node i, j;

    int nVertex;
    fscanf(via, "%d", &nVertex);
    Digraph g = createGraph(nVertex);
    
    int posic = 0;
    while (!feof(via)) {
        fscanf(via, "%s", tipo);

        if (!strcmp(tipo, "v")) {
            fscanf(via, "%s %lf %lf", id, &x, &y);
            setNodeName(g, posic, id);
            setNodeXY(g, posic, x, y);
            posic++;

        } else if (!strcmp(tipo, "e")) {
            fscanf(via, "%d %d %s %s %lf %lf %s", &i, &j, ldir, lesq, &vm, &cmp, nomeEdge);
            InfoEdge info = createInfoEdge(vm, cmp, ldir, lesq, nomeEdge);
            addEdge(g, i, j, info);

        }
        strcpy(tipo, " ");
    }
    fclose(via);
    return g;
}

FILE *openVia(char *bedVia) {
    FILE *via = fopen(bedVia, "r");
    if (!via) {
        printf("ERRO NA CRIAÇÃO DO VIA\n");
        exit(1);
    }
    return via;
}