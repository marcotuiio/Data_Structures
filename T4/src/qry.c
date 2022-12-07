#include "qry.h"

typedef struct auxCatac {
    double x, y, w, h;
    FILE *txt;
    Rb tree;
} auxCatac;

typedef struct originAdress {
    double x, y, num;
    char cep[30], face[3];
} originAdress;

typedef struct auxBloqs {
    char nome[30], sentido[5];
    double x, y, w, h;
    FILE *txt;
} auxBloqs;

void readQry(Rb t, Digraph g, char *bedQry, char *bsdSvg, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvg);
    char comando[8];
    originAdress *origin = calloc(1, sizeof(originAdress));

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (!strcmp(comando, "@o?")) {
            oFunc(qry, txt, svg, t, g, origin);

        } else if (!strcmp(comando, "catac")) {
            catac(qry, txt, svg, t, g);

        } else if (!strcmp(comando, "pnt")) {
            pnt(qry, txt, svg, t, g);

        } else if (!strcmp(comando, "blq")) {
            blq(qry, txt, svg, t, g);

        } else if (!strcmp(comando, "rbl")) {
            rbl(qry, txt, svg, t, g);

        } else if (!strcmp(comando, "rf")) {
            rf(qry, txt, svg, t, g);

        } else if (!strcmp(comando, "b")) {
            bFunc(qry, txt, svg, t, g);

        } else if (!strcmp(comando, "p?")) {
            pFunc(qry, txt, svg, t, g, origin);
        }
        strcpy(comando, "");
    }

    writeSvg(svg, t, g);
    free(origin);
    fclose(qry);
    fclose(txt);
}

FILE *openQry(char *bedQry) {
    FILE *qry = fopen(bedQry, "r");
    if (!qry) {
        printf("ERRO NA CRIAÇÃO DO QRY\n");
        exit(1);
    }
    return qry;
}

FILE *openTxt(char *bsdTxt) {
    FILE *txt = fopen(bsdTxt, "w");
    if (!txt) {
        printf("ERRO NA CRIAÇÃO DO TXT\n");
        exit(1);
    }
    return txt;
}

void lookCep(InfoRb i, void *aux) {
    void **data = aux;
    if (i && !strcmp(getCep(i), (char *)data[0])) {
        data[1] = i;
    }
}

void oFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g, void *origin) {
    char cep[30], face[3];
    double num;

    fscanf(qry, "%s %s %lf", cep, face, &num);
    fprintf(txt, "\n[*] @o? %s %s %lf\n", cep, face, num);

    void *data[] = {cep, NULL};
    percursoProfundidade(t, lookCep, data);

    if (!data[1]) {
        fprintf(txt, "CEP: %s, NÃO ENCONTRADO\n", cep);
        return;
    }

    double x1, y1, x2, y2;
    originAdress *o = origin;
    if (!strcmp(face, "S")) {
        x1 = getXNode(data[1]) + num;
        y1 = getYNode(data[1]) - 10;
        x2 = getXNode(data[1]) + num;
        y2 = getYNode(data[1]) + 10;
        o->x = x1;
        o->y = getYNode(data[1]);
    } else if (!strcmp(face, "N")) {
        x1 = getXNode(data[1]) + num;
        y1 = getYNode(data[1]) + getHNode(data[1]) - 10;
        x2 = getXNode(data[1]) + num;
        y2 = getYNode(data[1]) + getHNode(data[1]) + 10;
        o->x = x1;
        o->y = getYNode(data[1]) + getHNode(data[1]);
    } else if (!strcmp(face, "O")) {
        x1 = getXNode(data[1]) + getWNode(data[1]) - 10;
        y1 = getYNode(data[1]) + num;
        x2 = getXNode(data[1]) + getWNode(data[1]) + 10;
        y2 = getYNode(data[1]) + num;
        o->x = getXNode(data[1]) + getWNode(data[1]);
        o->y = y1;
    } else if (!strcmp(face, "L")) {
        x1 = getXNode(data[1]) - 10;
        y1 = getYNode(data[1]) + num;
        x2 = getXNode(data[1]) + 10;
        y2 = getYNode(data[1]) + num;
        o->x = getXNode(data[1]);
        o->y = y1;
    }

    o->num = num;
    strcpy(o->cep, cep);
    strcpy(o->face, face);

    fprintf(txt, "CEP: %s, FACE: %s, NUM: %lf, X: %lf, Y: %lf\n", cep, face, num, o->x, o->y);

    fprintf(svg, LINE, x1, y1, x2, y2, "purple");
}

void catac(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    double x, y, w, h;

    fscanf(qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
    fprintf(txt, "\n[*] catac %lf %lf %lf %lf\n", x, y, w, h);

    auxCatac *aux = malloc(sizeof(auxCatac));
    aux->x = x;
    aux->y = y;
    aux->w = w;
    aux->h = h;
    aux->txt = txt;
    aux->tree = t;

    percursoProfundidade(t, catacQuadras, aux);
    catacEdges(g, aux);
    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"#AB37C8\" stroke=\"#AA0044\" fill-opacity=\"50%%\" />\n", x, y, w, h);

    free(aux);
}

void catacQuadras(InfoRb i, void *aux) {
    auxCatac *data = aux;

    if (i && insideQuadra(i, data->x, data->y, data->w, data->h)) {
        fprintf(data->txt, "\tQUADRA REMOVIDA: %s, X: %lf, Y: %lf\n", getCep(i), getXNode(i), getYNode(i));
        RbNode removed = getNodeRB(data->tree, getXNode(i), getYNode(i));
        // printf("cep removed %s\n", getCep(getInfoRB(removed)));
        free(getDetails(getInfoRB(removed)));
        free(getInfoRB(removed));
        setInfoRB(removed, NULL);
    }
}

void catacEdges(Digraph g, void *extra) {
    auxCatac *data = extra;

    for (Node v = 0; v < getGraphSize(g); v++) {
        Lista adj = adjacentEdges(g, v);
        for (Edge e = getFirst(adj); e; e = getNext(e)) {
            Node from = getFromNode(g, e);
            Node to = getToNode(g, e);
            double x1 = getXVertex(getNodeInfo(g, from));
            double y1 = getYVertex(getNodeInfo(g, from));
            double x2 = getXVertex(getNodeInfo(g, to));
            double y2 = getYVertex(getNodeInfo(g, to));
            if (insideEdge(data->x, data->y, data->w, data->h, x1, y1, x2, y2)) {
                fprintf(data->txt, "\tARESTA REMOVIDA: %s, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getNomeEdge(getEdgeInfo(g, e)), x1, y1, x2, y2);
                removeEdge(g, e);
            }
        }
    }
}

void pnt(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    char cep[30], cfill[20], cstrk[20];

    fscanf(qry, "%s %s %s", cep, cfill, cstrk);
    fprintf(txt, "\n[*] pnt %s %s %s\n", cep, cfill, cstrk);

    void *data[] = {cep, NULL};
    percursoProfundidade(t, lookCep, data);

    if (data[1]) {
        fprintf(txt, "CEP: %s, CFILL_INICIAL: %s, CSTRK_INICIAL: %s, ", cep, getCFill(data[1]), getCStrk(data[1]));
        setCFill(getDetails(data[1]), cfill);
        setCStrk(getDetails(data[1]), cstrk);
        fprintf(txt, "CFILL_FINAL: %s, CSTRK_FINAL: %s\n", getCFill(data[1]), getCStrk(data[1]));
    } else {
        fprintf(txt, "CEP: %s, NÃO Encontrado\n", cep);
    }
}

void blq(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    char nome[30], sentido[5];
    double x, y, w, h;

    fscanf(qry, "%s %s %lf %lf %lf %lf", nome, sentido, &x, &y, &w, &h);
    fprintf(txt, "\n[*] blq %s %s %lf %lf %lf %lf\n", nome, sentido, x, y, w, h);

    auxBloqs *aux = calloc(1, sizeof(auxBloqs));
    aux->x = x;
    aux->y = y;
    aux->w = w;
    aux->h = h;
    aux->txt = txt;
    strcpy(aux->nome, nome);
    strcpy(aux->sentido, sentido);
    bloqEdges(g, aux);
    free(aux);
}

void bloqEdges(Digraph g, void *extra) {
    auxBloqs *data = extra;

    for (Node v = 0; v < getGraphSize(g); v++) {
        Lista adj = adjacentEdges(g, v);
        for (Edge e = getFirst(adj); e; e = getNext(e)) {
            Node from = getFromNode(g, e);
            Node to = getToNode(g, e);
            double x1 = getXVertex(getNodeInfo(g, from));
            double y1 = getYVertex(getNodeInfo(g, from));
            double x2 = getXVertex(getNodeInfo(g, to));
            double y2 = getYVertex(getNodeInfo(g, to));
            char sentidoPrimAresta[5], sentidoSecAresta[5];
            strcpy(sentidoPrimAresta, getSentidoPrimEdge(getEdgeInfo(g, e)));
            strcpy(sentidoSecAresta, getSentidoSecEdge(getEdgeInfo(g, e)));
            if (insideEdge(data->x, data->y, data->w, data->h, x1, y1, x2, y2)) {
                if (!strcmp(data->sentido, sentidoPrimAresta)) {
                    fprintf(data->txt, "\tARESTA BLOQUEADA: %s, Sentido: %s, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getNomeEdge(getEdgeInfo(g, e)), sentidoPrimAresta, x1, y1, x2, y2);
                    disableEdge(g, e);
                    setBloqNameEdge(getEdgeInfo(g, e), data->nome);
                }
                if (!strcmp(data->sentido, sentidoSecAresta)) {
                    fprintf(data->txt, "\tARESTA BLOQUEADA: %s, Sentido: %s, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getNomeEdge(getEdgeInfo(g, e)), sentidoSecAresta, x1, y1, x2, y2);
                    disableEdge(g, e);
                    setBloqNameEdge(getEdgeInfo(g, e), data->nome);
                }
            }
        }
    }
}

void rbl(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    char nome[30];

    fscanf(qry, "%s", nome);
    fprintf(txt, "\n[*] rbl %s\n", nome);

    for (Node v = 0; v < getGraphSize(g); v++) {
        Lista adj = adjacentEdges(g, v);
        for (Edge e = getFirst(adj); e; e = getNext(e)) {
            if (!strcmp(getBloqNameEdge(getEdgeInfo(g, e)), nome)) {
                fprintf(txt, "\tARESTA DESBLOQUEADA: %s, Sentido_Prim: %s, Sentido_Sec: %s, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getNomeEdge(getEdgeInfo(g, e)), getSentidoPrimEdge(getEdgeInfo(g, e)), getSentidoSecEdge(getEdgeInfo(g, e)), getXVertex(getNodeInfo(g, getFromNode(g, e))), getYVertex(getNodeInfo(g, getFromNode(g, e))), getXVertex(getNodeInfo(g, getToNode(g, e))), getYVertex(getNodeInfo(g, getToNode(g, e))));
                enableEdge(g, e);
                setBloqNameEdge(getEdgeInfo(g, e), "");
            }
        }
    }
}

void rf(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    char cep[30], face[3];
    double fator;

    fscanf(qry, "%s %s %lf", cep, face, &fator);
    fprintf(txt, "\n[*] rf %s %s %lf\n", cep, face, fator);
    Lista floresta = criaListaAux();
    void *data[] = {txt, &fator, cep, face, floresta, NULL, svg};
    dfs(g, classTree, classForward, classReturn, classCross, restarted, data);
    freeListaAux(floresta);
}

bool classTree(Digraph g, Edge e, int td, int tf, void *extra) {
    // if (!e) return true;
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    double vm_i = getVMEdge(getEdgeInfo(g, e));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "Aresta de Árvore: %s, VM_Inicial: %lf, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), vm_i, getVMEdge(getEdgeInfo(g, e)));
    return false;
}

bool classForward(Digraph g, Edge e, int td, int tf, void *extra) {
    // if (!e) return true;
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    double vm_i = getVMEdge(getEdgeInfo(g, e));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "Aresta de Avanço: %s, VM_Inicial: %lf, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), vm_i, getVMEdge(getEdgeInfo(g, e)));
    FILE *svg = data[6];
    double x1, y1, x2, y2;
    calcXY(g, e, &x1, &y1, &x2, &y2);
    x1 = y1 = x2 = y2 = 0;
    fprintf(svg, LINE, x1, y1, x2, y2, "#0000ff");
    return false;
}

bool classReturn(Digraph g, Edge e, int td, int tf, void *extra) {
    // if (!e) return true;
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    double vm_i = getVMEdge(getEdgeInfo(g, e));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "Aresta de Retorno: %s, VM_Inicial: %lf, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), vm_i, getVMEdge(getEdgeInfo(g, e)));
    FILE *svg = data[6];
    double x1, y1, x2, y2;
    x1 = y1 = x2 = y2 = 0;
    calcXY(g, e, &x1, &y1, &x2, &y2);
    fprintf(svg, LINE, x1, y1, x2, y2, "#ff6600");
    return false;
}

bool classCross(Digraph g, Edge e, int td, int tf, void *extra) {
    // if (!e) return true;
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    double vm_i = getVMEdge(getEdgeInfo(g, e));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "PONTE em Aresta Cruzada: %s, VM_Inicial: %lf, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), vm_i, getVMEdge(getEdgeInfo(g, e)));
    FILE *svg = data[6];
    double x1, y1, x2, y2;
    x1 = y1 = x2 = y2 = 0;
    calcXY(g, e, &x1, &y1, &x2, &y2);
    fprintf(svg, LINE, x1, y1, x2, y2, "magenta");
    return false;
}

void calcXY(Digraph g, Edge e, double *x1, double *y1, double *x2, double *y2) {
    Node from = getFromNode(g, e);
    Node to = getToNode(g, e);
    Lista a1 = adjacentEdges(g, from);
    Lista a2 = adjacentEdges(g, to);
    InfoNode fromInfo = getInfoFromVertex(a1);
    InfoNode toInfo = getInfoFromVertex(a2);
    *x1 = getXVertex(fromInfo);
    *y1 = getYVertex(fromInfo);
    *x2 = getXVertex(toInfo);
    *y2 = getYVertex(toInfo);
}

bool restarted(Digraph g, void *extra) {
    void **data = extra;
    FILE *txt = data[0];
    Lista floresta = data[4];
    insereAux(floresta, *(Node *)data[5]);
    fprintf(txt, "REINICIANDO e inserindo nó %d na floresta\n", *(Node *)data[5]);
    return false;
}

void bFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    double x, y, fator;

    fscanf(qry, "%lf %lf %lf", &x, &y, &fator);
    fprintf(txt, "\n[*] b %lf %lf %lf\n", x, y, fator);

    Node toStart = -1;
    for (Node i = 0; i < getGraphSize(g); i++) {
        double x1 = getXVertex(getNodeInfo(g, i));
        double y1 = getYVertex(getNodeInfo(g, i));
        if (fabs(x1 - x) <= 30 && fabs(y1 - y) <= 30) {  // Atenção!!!!
            toStart = i;
        }
    }
    if (toStart == -1) {
        fprintf(txt, "NÃO FOI ENCONTRADO NENHUM VÉRTICE COM AS COORDENADAS (%lf, %lf)\n", x, y);
        return;
    }
    // printf("toStart: %g\n", toStart);
    void *data[] = {&fator, txt, svg};
    bfs(g, toStart, bFuncEdges, data);
}

bool bFuncEdges(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    double fator = *(double *)data[0];
    FILE *txt = data[1];
    FILE *svg = data[2];
    fprintf(txt, "Aresta no percurso em Largura %s, VM_Inicial: %lf, ", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fator);
    fprintf(txt, "VM_Final: %lf\n", getVMEdge(getEdgeInfo(g, e)));
    double x1, y1, x2, y2;
    calcXY(g, e, &x1, &y1, &x2, &y2);
    fprintf(svg, LINE, x1, y1, x2, y2, "#c83737");
    return false;
}

void pFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g, void *origin) {
    char cep[30], face[3], cmc[30], cmr[30];  // cmc = cor percurso curto, cmr = cor percurso rapido
    double num;

    fscanf(qry, "%s %s %lf %s %s", cep, face, &num, cmc, cmr);
    fprintf(txt, "\n[*] p? %s %s %lf %s %s\n", cep, face, num, cmc, cmr);

    void *data[] = {cep, NULL};
    percursoProfundidade(t, lookCep, data);
    if (!data[1]) {
        fprintf(txt, "CEP de Destino: %s, NÃO ENCONTRADO\n", cep);
        return;
    }

    double x2, y2;
    if (!strcmp(face, "S")) {
        x2 = getXNode(data[1]) + num;
        y2 = getYNode(data[1]);
    } else if (!strcmp(face, "N")) {
        x2 = getXNode(data[1]) + num;
        y2 = getYNode(data[1]);
    } else if (!strcmp(face, "O")) {
        x2 = getXNode(data[1]);
        y2 = getYNode(data[1]) + num;
    } else if (!strcmp(face, "L")) {
        x2 = getXNode(data[1]);
        y2 = getYNode(data[1]) + num;
    }

    originAdress *o = origin;
    Node i = getNodeGivenXY(g, o->x, o->y);
    Node j = getNodeGivenXY(g, x2, y2);
    if (i == -1) {
        fprintf(txt, "Nó de origem não encontrado\n");
        return;
    }
    if (j == -1) {
        fprintf(txt, "Nó de destino não encontrado\n");
        return;
    }
    // printf("DIJKSTRA: i: %d, j: %d\n", i, j);

    fprintf(txt, "Iniciando percurso de CEP: %s (X: %lf, Y: %lf) para CEP: %s (X: %lf, Y: %lf)\n", o->cep, o->x, o->y, cep, x2, y2);
    Node *path_speed = fullDijkstra(g, i, j, 1);  // 0 = distancia, 1 = velocidade
    drawPath(g, path_speed, svg, txt, VELOCIDADE, cmr, cmc);
    Node *path_distance = fullDijkstra(g, i, j, 0);  // 0 = distancia, 1 = velocidade
    drawPath(g, path_distance, svg, txt, DISTANCIA, cmr, cmc);

    if (path_speed) free(path_speed);
    if (path_distance) free(path_distance);
}

Node getNodeGivenXY(Digraph g, double x, double y) {
    for (Node i = 0; i < getGraphSize(g); i++) {
        if (fabs(getXVertex(getNodeInfo(g, i)) - x) <= 50.0 && fabs(getYVertex(getNodeInfo(g, i)) - y) <= 50.0) {
            return i;
        }
    }
    return -1;
}

void drawPath(Digraph g, Node *caminho, FILE *svg, FILE *txt, int type, char *cmr, char *cmc) {
    int i;
    double x1, y1, x2, y2;
    for (i = 0; i < getGraphSize(g) - 1; i++) {
        if (caminho[i] == -1)
            continue;
        if (type == VELOCIDADE) {
            x1 = getXVertex(getNodeInfo(g, caminho[i]));
            y1 = getYVertex(getNodeInfo(g, caminho[i]));
            x2 = getXVertex(getNodeInfo(g, caminho[i + 1]));
            y2 = getYVertex(getNodeInfo(g, caminho[i + 1]));
            fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke:%s; stroke-width:4; stroke-dasharray:2,2\"/> <circle x=\"0\" y=\"0\" r=\"5\" stroke=\"red\" fill=\"blue\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n", x1, y1, x2, y2, cmr, x1, y1, x2, y2);

        } else if (type == DISTANCIA) {
            x1 = getXVertex(getNodeInfo(g, caminho[i])) - 6;
            y1 = getYVertex(getNodeInfo(g, caminho[i])) - 6;
            x2 = getXVertex(getNodeInfo(g, caminho[i + 1])) - 6;
            y2 = getYVertex(getNodeInfo(g, caminho[i + 1])) - 6;
            fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke:%s; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"blue\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n", x1, y1, x2, y2, cmc, x1, y1, x2, y2);
        }
    }

    if (type == 1) {
        fprintf(txt, "\nCaminho mais curto:");
    } else {
        fprintf(txt, "\nCaminho mais rapido:");
    }

    char direcaoAnterior[30] = "direcaoAnterior";
    char direcaoAtual[30] = "direcaoAtual";
    Edge aresta;
    for (i = 0; i < getGraphSize(g) - 1; i++) {
        if (caminho[i] == -1) {
            continue;
        }
        aresta = getEdge(g, caminho[i], caminho[i + 1]);
        InfoEdge info = getEdgeInfo(g, aresta);
        x1 = getXVertex(getNodeInfo(g, caminho[i]));
        y1 = getYVertex(getNodeInfo(g, caminho[i]));
        x2 = getXVertex(getNodeInfo(g, caminho[i + 1]));
        y2 = getYVertex(getNodeInfo(g, caminho[i + 1]));

        if (x1 < x2) {
            strcpy(direcaoAtual, "Oeste");

        } else if (x1 > x2) {
            strcpy(direcaoAtual, "Leste");

        } else if (y1 < y2) {
            strcpy(direcaoAtual, "Norte");

        } else if (y2 > y2) {
            strcpy(direcaoAtual, "Sul");
        }

        if (!strcmp(direcaoAnterior, "direcaoAnterior")) {
            fprintf(txt, "\nSiga na direcao %s na Rua %s", direcaoAtual, getNomeEdge(info));

        } else if (strcmp(direcaoAtual, direcaoAnterior) == 1) {
            fprintf(txt, " ate o cruzamento com a Rua %s.\n", getNomeEdge(info));
            fprintf(txt, "Siga na direcao %s na Rua %s", direcaoAtual, getNomeEdge(info));
        }

        strcpy(direcaoAnterior, direcaoAtual);
    }

    if (!strcmp(direcaoAnterior, "direcaoAnterior")) {
        fprintf(txt, "NÃO FOI POSSÍVEL ENCONTRAR UM CAMINHO ENTRE OS ENDEREÇOS\n");
        fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:1; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"6s\" repeatCount=\"indefinite\" /> </circle>\n", x1, y1, x2, y2, x1, y1, x2, y2);

    } else {
        fprintf(txt, ". Chegou em seu destino.\n");
    }
}