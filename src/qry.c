#include "libs.h"
#include "qry.h"
#include "SRBtree.h"
#include "figures.h"
#include "list.h"

typedef struct aux {
    
    char cep[30];
    void* quadra;
    FILE* txt;
    FILE* svg;
    double x, y, w, h;
    SRbTree tree;

} Aux;

void readingQry(FILE* qryFile, SRbTree arvore, FILE* svg, FILE* arqTxt) {

    char comando[300];

    while (fscanf(qryFile, "%s", comando) != EOF) {

        if (strcmp(comando, "@o?") == 0) {
            char cep[30], face[2];
            double num;
            fscanf(qryFile, "%s %s %lf", cep, face, &num);
            fprintf(arqTxt, "\n[*] @o? %s %s %lf\n", cep, face, num);
            oFunc(cep, face, num, arvore, svg);

        } else if (strcmp(comando, "catac") == 0) {
            double x, y, w, h;
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            fprintf(arqTxt, "\n[*] catac %lf %lf %lf %lf\n", x, y, w, h);
            catac(x, y, w, h, arqTxt, svg, arvore);

        } else if (strcmp(comando, "pnt") == 0) {
            char cep[30], cfill[20], cstrk[20];
            fscanf(qryFile, "%s %s %s", cep, cfill, cstrk);
            fprintf(arqTxt, "\n[*] pnt %s %s %s\n", cep, cfill, cstrk);
            pnt(cep, cfill, cstrk, arvore, arqTxt);

        } else if (strcmp(comando, "blq") == 0) {
            char nome[30], sentido[10];
            double x, y, w, h;
            fscanf(qryFile, "%s %s %lf %lf %lf %lf", nome, sentido, &x, &y, &w, &h);
            fprintf(arqTxt, "\n[*] blq %s %s %lf %lf %lf %lf\n", nome, sentido, x, y, w, h);

        } else if (strcmp(comando, "rbl") == 0) {
            char nome[30];
            fscanf(qryFile, "%s", nome);
            fprintf(arqTxt, "\n[*] rbl00 %s\n", nome);

        } else if (strcmp(comando, "rf") == 0) {
            char cep[30], face[2];
            double fator;
            fscanf(qryFile, "%s %s %lf", cep, face, &fator);
            fprintf(arqTxt, "\n[*] rf %s %s %lf\n", cep, face, fator);

        } else if (strcmp(comando, "b") == 0) {
            double x, y, fator;
            fscanf(qryFile, "%lf %lf %lf", &x, &y, &fator);
            fprintf(arqTxt, "\n[*] b %lf %lf %lf\n", x, y, fator);
            
        } else if (strcmp(comando, "p?") == 0) {
            char cep[30], face[2], cmc[20], cmr[20];
            fscanf(qryFile, "%s %s %s %s", cep, face, cmc, cmr);
            fprintf(arqTxt, "\n[*] p? %s %s %s %s\n", cep, face, cmc, cmr);
            
        }

        strcpy(comando, " ");
    }
    fprintf(arqTxt, "\n================ RELATORIO FINAL ================\n");
    //percursoProfundidade(arvore, printResultados, arqTxt);
    
}

// ========================================= QUERIES =============================================================

void buscaCep(void* i, void* aux) {

    // i = quadra
    // aux = aux
    Aux* a = (Aux*) aux;
    if (strcmp(a->cep, getCep(i)) == 0) {
        a->quadra = i;
    }
}

void buscaRegiaoRetangular(void* i, void* aux) {
    //printf("entrou buscaRegiao\n");
    Aux* a = (Aux*) aux;

    if (getX(i) >= a->x) {
        if (getX(i) + getW(i) <= a->x + a->w) {
            if (getY(i) >= a->y) {
                if (getY(i) + getH(i) <= a->y + a->h) {
                    printf("ta dentro da regiao\n");
                    a->quadra = i;
                    fprintf(a->txt, "figura removida: x = %.2f y = %.2f cor borda = %s cor preenchimento = %s\n", getX(a->quadra), getY(a->quadra), getCorb(a->quadra), getCorp(a->quadra));
                    Figura fig = removeSRb(a->tree, getX(a->quadra), getY(a->quadra), 0, 0, 0 ,0);
                }
            }
        }
    }
}

void pnt(char* cep, char* cfill, char* cstrk, SRbTree tree, FILE* txt) {

    Aux* structAux = malloc(sizeof(Aux));
    strcpy(structAux->cep, cep);
    percursoProfundidade(tree, buscaCep, structAux);
    setBorda(structAux->quadra, cstrk);
    setPreench(structAux->quadra, cfill);
    fprintf(txt, "blablabla");
    free(structAux);
}

// armazena a posição geográfica do endereço cep/face/num
void oFunc(char* cep, char* face, double num, SRbTree tree, FILE* svg) {

    Aux* structAux = malloc(sizeof(Aux));
    strcpy(structAux->cep, cep);
    percursoProfundidade(tree, buscaCep, structAux);
    double xPosic, yPosic;
    xPosic = getX(structAux->quadra);
    yPosic = getY(structAux->quadra);
    
    if (strcmp(face, "S") == 0) {
        xPosic = xPosic + num;
    } else if (strcmp(face, "O") == 0) {
        xPosic = xPosic + getW(structAux->quadra);
        yPosic = yPosic + num;
    } else if (strcmp(face, "N") == 0) {
        xPosic = xPosic + num;
        yPosic = yPosic + getH(structAux->quadra);
    } else if (strcmp(face, "L") == 0) {
        yPosic = yPosic + num;
    }

    fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", xPosic, yPosic-5, xPosic, yPosic, "red");
    free(structAux);
}

void catac(double x, double y, double w, double h, FILE* arqTxt, FILE* arqSvg, SRbTree tree) {

    Aux* structAux = calloc(1, sizeof(Aux));
    structAux->x = x;
    structAux->y = y;
    structAux->w = w;
    structAux->h = h;
    structAux->txt = arqTxt;
    structAux->tree = tree;
    printf("antes do percurso\n");
    percursoProfundidade(tree, buscaRegiaoRetangular, structAux);
    fprintf(arqSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=#AB37C8 stroke=#AA0044 stroke-opacity=\"%f\"/>", x, y, w, h, 0.5);
    free(structAux);
}

void blq(char* nome, char* sentido, double x, double y, double w, double h) {
    printf("oi");
}

void rbl(char* nome) {
    printf("oi");

}

void rf(char* cep, char* face, double fator) {
    printf("oi");

}

void bFunc(double x, double y, double fator) {
    printf("oi");

}

void pFunc(char* cep, char* face, double num, char* cmc, char* cmr) {
    printf("oi");

}