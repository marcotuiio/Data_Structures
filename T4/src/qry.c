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
        strcpy(comando, " ");
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

    fprintf(svg, LINE, x1, y1, x2, y2, "red");
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
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"#AB37C8\" stroke=\"#AA0044\" fill-opacity=\"50%%\" />\n", x, y, w, h);

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
            char sentidoAresta[5];
            strcpy(sentidoAresta, getSentidoEdge(getEdgeInfo(g, e)));
            if (insideEdge(data->x, data->y, data->w, data->h, x1, y1, x2, y2)) {
                if (!strcmp(data->sentido, sentidoAresta)) {
                    fprintf(data->txt, "\tARESTA BLOQUEADA: %s, Sentido: %s, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getNomeEdge(getEdgeInfo(g, e)), sentidoAresta, x1, y1, x2, y2);
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
                fprintf(txt, "\tARESTA DESBLOQUEADA: %s, Sentido: %s, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getNomeEdge(getEdgeInfo(g, e)), getSentidoEdge(getEdgeInfo(g, e)), getXVertex(getNodeInfo(g, getFromNode(g, e))), getYVertex(getNodeInfo(g, getFromNode(g, e))), getXVertex(getNodeInfo(g, getToNode(g, e))), getYVertex(getNodeInfo(g, getToNode(g, e))));
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
    void *data[] = {txt, &fator, cep, face};
    dfs(g, classTree, classForward, classReturn, classCross, restarted, data);
}

bool classTree(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "Aresta de Árvore: %s, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    return false;
}

bool classForward(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "Aresta de Avanço: %s, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    return false;
}

bool classReturn(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "Aresta de Retorno: %s, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    return false;
}

bool classCross(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    FILE *txt = data[0];
    double fat = *(double *)data[1];
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fat);
    fprintf(txt, "PONTE em Aresta Cruzada: %s, Velocidade Máxima: %lf\n", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    return false;
}

bool restarted(Digraph g, void *extra) {
    FILE *txt = extra;
    fprintf(txt, "REINICIADO\n");
    return false;
}

void bFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g) {
    double x, y, fator;

    fscanf(qry, "%lf %lf %lf", &x, &y, &fator);
    fprintf(txt, "\n[*] b %lf %lf %lf\n", x, y, fator);

    Node toStart = 0;
    for (Node i = 0; i < getGraphSize(g); i++) {
        double x1 = getXVertex(getNodeInfo(g, i));
        double y1 = getYVertex(getNodeInfo(g, i));
        if (fabs(x1 - x) <= 0 && fabs(y1 - y) <= 0) {  // Atenção!!!!
            toStart = i;
        }
    }
    // printf("toStart: %g\n", toStart);
    void *data[] = {&fator, txt};
    bfs(g, toStart, bFuncEdges, data);
}

bool bFuncEdges(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    double fator = *(double *)data[0];
    FILE *txt = data[1];
    fprintf(txt, "Aresta no percurso em Largura %s, VMi: %lf, ", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * fator);
    fprintf(txt, "VMf: %lf\n", getVMEdge(getEdgeInfo(g, e)));
    return false;
}

void pFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph g, void *origin) {
    char cep[30], face[3], cmc[30], cmr[30];  // cmc = cor percurso curto, cmr = cor percurso rapido
    double num;

    fscanf(qry, "%s %s %lf %s %s", cep, face, &num, cmc, cmr);
    fprintf(txt, "\n[*] p %s %s %lf %s %s\n", cep, face, num, cmc, cmr);

    void *data[] = {cep, NULL};
    percursoProfundidade(t, lookCep, data);
    if (!data[1]) {
        fprintf(txt, "CEP de Destino: %s, NÃO ENCONTRADO\n", cep);
        return;
    }

    double x1, y1;
    if (!strcmp(face, "S")) {
        x1 = getXNode(data[1]) + num;
        y1 = getYNode(data[1]);
    } else if (!strcmp(face, "N")) {
        x1 = getXNode(data[1]) + num;
        y1 = getYNode(data[1]);
    } else if (!strcmp(face, "O")) {
        x1 = getXNode(data[1]);
        y1 = getYNode(data[1]) + num;
    } else if (!strcmp(face, "L")) {
        x1 = getXNode(data[1]);
        y1 = getYNode(data[1]) + num;
    }

    originAdress *o = origin;
    fprintf(txt, "Iniciando percurso de CEP: %s (X: %lf, Y: %lf) para CEP: %s (X: %lf, Y: %lf)\n", o->cep, o->x, o->y, cep, x1, y1);
}