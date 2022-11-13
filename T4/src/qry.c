#include "qry.h"

typedef struct auxCatac {
    double x, y, w, h;
    FILE *txt;
    Rb tree;
} auxCatac;

void readQry(Rb t, Digraph d, char *bedQry, char *bsdSvg, char *bsdTxt) {
    FILE *qry = openQry(bedQry);
    FILE *txt = openTxt(bsdTxt);
    FILE *svg = createSvg(bsdSvg);
    char comando[8];

    while (!feof(qry)) {
        fscanf(qry, "%s", comando);

        if (!strcmp(comando, "@o?")) {
            oFunc(qry, txt, svg, t, d);

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
            pFunc(qry, txt, svg, t, d);
        }
        strcpy(comando, " ");
    }

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

void oFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    char cep[30], face[3];
    double num;

    fscanf(qry, "%s %s %lf", cep, face, &num);
    fprintf(txt, "\n[*] @o? %s %s %lf\n", cep, face, num);

    void *data[] = {cep, NULL};
    lookCep(t, data);
    fprintf(txt, "CEP: %s, %s, %lf || %p\n", cep, face, num, data[1]);
    
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
    
    fprintf(svg, LINE, x1, y1, x2, y2, "red");
}

void lookCep(InfoRb i, void *aux) {
    void **data = aux;
    if (!strcmp(getCep(i), data[0])) {
        data[1] = i;
    }
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
}

void bFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    double x, y, fator;

    fscanf(qry, "%lf %lf %lf", &x, &y, &fator);
    fprintf(txt, "\n[*] b %lf %lf %lf\n", x, y, fator);
}

void pFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d) {
    char cep[30], face[3], cmc[30], cmr[30]; // cmc = cor percurso curto, cmr = cor percurso rapido
    double num;

    fscanf(qry, "%s %s %lf %s %s", cep, face, &num, cmc, cmr);
    fprintf(txt, "\n[*] p %s %s %lf %s %s\n", cep, face, num, cmc, cmr);
}