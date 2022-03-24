#include <stdio.h>
#include <stdlib.h>
#define n 10

struct cel{
       int conteudo;
       int linha;
       int coluna;
       struct cel *prox;
};
typedef struct cel celula;

void InsereInicio(celula **ini, int l, int c, int v);
void InserirElemento(celula **ini, int l, int c, int v);
void leMatriz(celula **lista);
void somaLin_Col(celula *inicio);
void escreveMatriz(celula *inicio);

void main(){
    celula *inicio;
    inicio = NULL;

    leMatriz(&inicio);
    somaLin_Col(inicio);
    escreveMatriz(inicio);

    return;
}

void InsereInicio(celula **ini, int l, int c, int v){
    celula *aux;
    aux= (celula*)malloc (sizeof (celula));
    aux->linha = l;
    aux->coluna = c;
    aux->conteudo = v;
    aux->prox = NULL;

    if(*ini != NULL){
        aux->prox = *ini;
    }
    *ini = aux;

    return ;
}

void InserirElemento(celula **ini, int l, int c, int v){
    celula *aux;
    celula *p;
    celula *anterior = NULL;
    aux= (celula*)malloc (sizeof (celula));
    aux->linha = l;
    aux->coluna = c;
    aux->conteudo = v;
    aux->prox = NULL;

    p = aux;
    while ((p->conteudo > v) && (p->prox != NULL)){
       anterior = p;
       p = p->prox;
    }
    if (p->conteudo <= v){
        if (anterior == NULL)
            InsereInicio(ini, l, c, v);
        else{ 
            aux->prox=anterior->prox;
            anterior->prox=aux;
            }
    }else{
        p->prox=aux;
    }

    return ;
}

void leMatriz(celula **lista){
    int num, i, j;

    FILE * arq;
    arq = fopen("listaMatrix.txt", "r");

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            fscanf(arq, "%d", &num);
            if(lista == NULL){
                InsereInicio(lista, i, j, num);
            }else
                InserirElemento(lista, i, j, num);
        }
    }
    fclose(arq); 
}

void somaLin_Col(celula *inicio){
    celula *aux;
    int i, somalinha, somacoluna;
    for(i=0; i<n; i++){
        somalinha = 0;
        somacoluna = 0;
        aux = inicio;
        while(aux != NULL){
            if(i == aux->linha){
                somalinha += aux->conteudo;
            }
            if(i == aux->coluna){
                somacoluna += aux->conteudo;
            }
            aux = aux->prox;
        }
        printf("\nSoma Linha %d = %d\n", i+1, somalinha);
        printf("Soma Coluna %d = %d\n", i+1, somacoluna);
    }
    puts(" ");
}

void escreveMatriz(celula *inicio){
    celula * aux;
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            aux = inicio;
            while((aux->linha != i) || (aux->coluna != j)){
                aux = aux->prox;
            }
            printf("%d ", aux->conteudo);
        }
        printf("\n");
    }
    puts(" ");
}