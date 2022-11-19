#include "via.h"

#include "digraph.h"
#include "infos.h"

Digraph readVia(char *bedVia) {
    FILE *via = openVia(bedVia);
    char tipo[5], id[30], ldir[30], lesq[30], nomeEdge[30], i[30], j[30];
    double x, y, vm, cmp;

    Node nVertex;
    fscanf(via, "%d", &nVertex);
    Digraph g = createGraph(nVertex);

    Node posic = 0;
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
                char sentido[5] = "----";
                InfoNode inFrom = getNodeInfo(g, from);
                InfoNode inTo = getNodeInfo(g, to);
                double x1 = getXVertex(inFrom);
                double y1 = getXVertex(inFrom);
                double x2 = getXVertex(inTo);
                double y2 = getXVertex(inTo);

                // printf("x1: %lf, y1: %lf, x2: %lf, y2: %lf\n", x1, y1, x2, y2);
                if (x1 == x2) {
                    if (y1 < y2) {
                        strcpy(sentido, "sn");
                    } else {
                        strcpy(sentido, "ns");
                    }
                
                } else if (y1 == y2) {
                    if (x1 < x2) {
                        strcpy(sentido, "lo");
                    } else {
                        strcpy(sentido, "ol");
                    }
                }
                // printf("Sentido: %s\n", sentido);

                InfoEdge infoE = createInfoEdge(vm, cmp, ldir, lesq, nomeEdge);
                setSentidoEdge(infoE, sentido);
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