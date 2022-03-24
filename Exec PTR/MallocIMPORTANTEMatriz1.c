#include <stdio.h>
#include <stdlib.h>
#define lin 3
#define col 4

int  **criaMatriz();
void escreveMatriz(int **m);
void leMatriz(int **m);
void somaMatriz(int **a, int **b, int **c);

void main(){
    int **a, **b, **soma;

    a = criaMatriz();
    b = criaMatriz();
    soma = criaMatriz();

    leMatriz(a);
    leMatriz(b);

    printf("\nMatriz A:\n");
    escreveMatriz(a);
    printf("\nMatriz B:\n");
    escreveMatriz(b);

    somaMatriz(a, b, soma);
    printf("\nMatriz C:\n");
    escreveMatriz(soma);
}

int **criaMatriz(){
    int i;
    int **m;
    m = malloc(lin * sizeof(int));
    for(i=0; i<col; i++){
        m[i] = malloc(col * sizeof(int));
    }
    return(m);
}

void leMatriz(int **m){
    int i, j;
    for(i=0; i<lin; i++){
        for(j=0; j<col; j++){
            printf("Matriz[%d][%d] = ", i+1, j+1);
            scanf("%d", (m[i]+j));
        }
    }
}

void escreveMatriz(int **m){
    int i, j;
    for(i=0; i<lin; i++){
        for(j=0; j<col; j++){
            printf("%d ", *(m[i]+j));
        }
        printf("\n");
    }
}

void somaMatriz(int **a, int **b, int **c){
    int i, j;
    for(i=0; i<lin; i++){
        for(j=0; j<col; j++){
            *(c[i]+j) = *(a[i]+j) + *(b[i]+j);
        }
    }
}
