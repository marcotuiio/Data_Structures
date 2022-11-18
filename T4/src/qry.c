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

void readQry(Rb t, Digraph d, char *bedQry, char *bsdSvg, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvg);
    char comando[8];
    originAdress *origin = calloc(1, sizeof(originAdress));

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (!strcmp(comando, "@o?")) {
            oFunc(qry, txt, svg, t, d, origin);

        } else if (!strcmp(comando, "catac")) {
            catac(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "pnt")) {
            pnt(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "blq")) {
            blq(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "rbl")) {
            rbl(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "rf")) {
            rf(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "b")) {
            bFunc(qry, txt, svg, t, d);

        } else if (!strcmp(comando, "p?")) {
            pFunc(qry, txt, svg, t, d, origin);
        }
        strcpy(comando, " ");
    }

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
    if (!strcmp(getCep(i), data[0])) {
        data[1] = i;
    }
}

void oFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d, void *origin) {
    char cep[30], face[3];
    double num;

    fscanf(qry, "%s %s %lf", cep, face, &num);
    fprintf(txt, "\n[*] @o? %s %s %lf\n", cep, face, num);

    void *data[] = {cep, NULL};
    lookCep(t, data);
    if (data[1]) {
        fprintf(txt, "CEP: %s, %s, %lf || %p\n", cep, face, num, data[1]);
    } else {
        fprintf(txt, "CEP: %s, NÃO ENCONTRADO\n", cep);
        return;
    }

    double x1, y1, x2, y2;
    if (!strcmp(face, "S")) {
        x1 = getXNode(data[1]) + num;
        y1 = getYNode(data[1]) - 5;
        x2 = getXNode(data[1]) + num;
        y2 = getYNode(data[1]) + 5;
    } else if (!strcmp(face, "N")) {
        x1 = getXNode(data[1]) + num;
        y1 = getYNode(data[1]) + 5;
        x2 = getXNode(data[1]) + num;
        y2 = getYNode(data[1]) - 5;
    } else if (!strcmp(face, "O")) {
        x1 = getXNode(data[1]) + 5;
        y1 = getYNode(data[1]) + num;
        x2 = getXNode(data[1]) - 5;
        y2 = getYNode(data[1]) + num;
    } else if (!strcmp(face, "L")) {
        x1 = getXNode(data[1]) - 5;
        y1 = getYNode(data[1]) + num;
        x2 = getXNode(data[1]) + 5;
        y2 = getYNode(data[1]) + num;
    }

    originAdress *o = origin;
    o->x = x1;
    o->y = y1;
    o->num = num;
    strcpy(o->cep, cep);
    strcpy(o->face, face);

    fprintf(svg, LINE, x1, y1, x2, y2, "red");
}

void catac(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
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

    catacQuadras(t, aux);
    bfs(d, 0, catacEdges, aux);
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"#AB37C8\" stroke=\"#AA0044\" fill-opacity=\"50%%\" />\n", x, y, w, h);

    free(aux);
}

void catacQuadras(InfoRb i, void *aux) {
    auxCatac *data = aux;
    if (insideQuadra(i, data->x, data->y, data->w, data->h)) {
        fprintf(data->txt, "\tENDEREÇO REMOVIDO: %s, X: %lf, Y: %lf\n", getCep(i), getXNode(i), getYNode(i));
        removeRB(data->tree, getXNode(i), getYNode(i));
    }
}

bool catacEdges(Digraph g, Edge e, int td, int tf, void *extra) {
    auxCatac *data = extra;
    Node from = getFromNode(g, e);
    Node to = getToNode(g, e);
    double x1 = getXVertex(getNodeInfo(g, from));
    double y1 = getYVertex(getNodeInfo(g, from));
    double x2 = getXVertex(getNodeInfo(g, to));
    double y2 = getYVertex(getNodeInfo(g, to));

    if (insideEdge(data->x, data->y, data->w, data->h, x1, y1, x2, y2)) {
        fprintf(data->txt, "\tARESTA REMOVIDA: FROM %s, TO %s, x1: %lf, y1: %lf, x2: %lf, y2: %lf\n", getNomeVertex(getNodeInfo(g, from)), getNomeVertex(getNodeInfo(g, to)), x1, y1, x2, y2);
        removeEdge(g, e);
    }
    return true;
}

void pnt(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    char cep[30], cfill[20], cstrk[20];

    fscanf(qry, "%s %s %s", cep, cfill, cstrk);
    fprintf(txt, "\n[*] pnt %s %s %s\n", cep, cfill, cstrk);

    void *data[] = {cep, NULL};
    lookCep(t, data);

    if (data[1]) {
        fprintf(txt, "CEP: %s, X: %lf, Y: %lf, iCFILL: %s, iCSTRK: %s\n", cep, getXNode(data[1]), getYNode(data[1]), getCFill(data[1]), getCStrk(data[1]));
        setCFill(data[1], cfill);
        setCStrk(data[1], cstrk);
    } else {
        fprintf(txt, "CEP: %s, NÃO Encontrado\n", cep);
    }
}

void blq(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    char nome[30], sentido[5];
    double x, y, w, h;

    fscanf(qry, "%s %s %lf %lf %lf %lf", nome, sentido, &x, &y, &w, &h);
    fprintf(txt, "\n[*] blq %s %s %lf %lf %lf %lf\n", nome, sentido, x, y, w, h);
}

void rbl(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    char nome[30];

    fscanf(qry, "%s", nome);
    fprintf(txt, "\n[*] rbl %s\n", nome);
}

void rf(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    char cep[30], face[3];
    double fator;

    fscanf(qry, "%s %s %lf", cep, face, &fator);
    fprintf(txt, "\n[*] rf %s %s %lf\n", cep, face, fator);
    void *data[] = {txt, &fator, cep, face};
    dfs(d, classTree, classForward, classReturn, classCross, restarted, data);
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

void bFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    double x, y, fator;

    fscanf(qry, "%lf %lf %lf", &x, &y, &fator);
    fprintf(txt, "\n[*] b %lf %lf %lf\n", x, y, fator);

    Node toStart;
    for (Node i = 0; i < getGraphSize(d); i++) {
        double x1 = getXVertex(getNodeInfo(d, i));
        double y1 = getYVertex(getNodeInfo(d, i));
        if (fabs(x1 - x) <= 0 && fabs(y1 - y) <= 0) {  // Atenção!!!!
            toStart = i;
        }
    }
    void *data[] = {&fator, txt};
    bfs(d, toStart, bFuncEdges, data);
}

bool bFuncEdges(Digraph g, Edge e, int td, int tf, void *extra) {
    void **data = extra;
    double *fator = data[0];
    FILE *txt = data[1];
    fprintf(txt, "EDGE %s, VMi: %lf, ", getNomeEdge(getEdgeInfo(g, e)), getVMEdge(getEdgeInfo(g, e)));
    setVMEdge(getEdgeInfo(g, e), getVMEdge(getEdgeInfo(g, e)) * (*fator));
    fprintf(txt, "VMf: %lf\n", getVMEdge(getEdgeInfo(g, e)));
    return false;
}

void pFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d, void *origin) {
    char cep[30], face[3], cmc[30], cmr[30];  // cmc = cor percurso curto, cmr = cor percurso rapido
    double num;

    fscanf(qry, "%s %s %lf %s %s", cep, face, &num, cmc, cmr);
    fprintf(txt, "\n[*] p %s %s %lf %s %s\n", cep, face, num, cmc, cmr);

    void *data[] = {cep, NULL};
    lookCep(t, data);
    if (data[1]) {
        fprintf(txt, "CEP de Destino: %s, %s, %lf || %p\n", cep, face, num, data[1]);
    } else {
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
    fprintf(txt, "Iniciando percurso de %s (%lf, %lf) para %s (%lf, %lf)\n", o->cep, o->x, o->y, cep, x1, y1);
}