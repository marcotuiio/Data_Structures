#include "via.h"
#include "digraph.h"
#include "infos.h"

Digraph readVia(char *bedVia) {
    FILE *via = openVia(bedVia);
    char tipo[5], id[30], ldir[30], lesq[30], nomeEdge[30], i[30], j[30];
    double x, y, vm, cmp;

    int nVertex;
    fscanf(via, "%d", &nVertex);
    Digraph g = createGraph(nVertex);
    
    int posic = 0;
    while (!feof(via)) {
        fscanf(via, "%s", tipo);

        if (!strcmp(tipo, "v")) {
            fscanf(via, "%s %lf %lf", id, &x, &y);
            setNodeName(g, posic, id);
            InfoNode infoV = createInfoVertex(x, y, id);
            setNodeInfo(g, posic, infoV);
            posic++;

        } else if (!strcmp(tipo, "e")) {
            fscanf(via, "%s %s %s %s %lf %lf %s", i, j, ldir, lesq, &cmp, &vm, nomeEdge);
            Node from = getNode(g, i);
            Node to = getNode(g, j);
            if (from != -1 && to != -1) {
                InfoEdge infoE = createInfoEdge(vm, cmp, ldir, lesq, nomeEdge);
                addEdge(g, from, to, infoE);
            }
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