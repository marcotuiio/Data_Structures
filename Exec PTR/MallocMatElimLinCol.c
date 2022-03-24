#include <stdio.h>
#include <stdlib.h>
#define n 10

int  **criaMatriz();
void leMatriz(int **m, FILE *arq);
void encontraMenor(int **m);
void encontraMaior(int **m);
void escreveMatriz(int **m, int size); 

void main(){
    int **matriz;

    matriz = criaMatriz();
    
    FILE * arq;
    arq = fopen("LMx04.txt", "r");
    leMatriz(matriz, arq);
    fclose(arq);
    
    printf("\nMATRIZ NORMAL:\n"); 
    escreveMatriz(matriz, n); 
    encontraMenor(matriz);
    encontraMaior(matriz);

    printf("\nMATRIZ RESULTANTE:\n");
    escreveMatriz(matriz, n-1);

    free(matriz);
}

int **criaMatriz(){
    int i;
    int **m;
    m = malloc(n * sizeof(int));
    for(i=0; i<n; i++){
        m[i] = malloc(n * sizeof(int));
    }
    return(m);
}

void leMatriz(int **m, FILE *arq){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            fscanf(arq, "%d", (m[i]+j));
        }
    }
}

void escreveMatriz(int **m, int size){
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            printf("%d ", *(m[i]+j));
        }
        printf("\n");
    } 
}

void encontraMenor(int **m){
    int i, j, menor, linha;
    menor = *(m[0]+0);

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(*(m[i]+j) < menor){
                menor = *(m[i]+j);
                linha = i;
            }
        }
    }
    printf("\nMenor elemento = %d, linha = %d\n", menor, linha+1);

    free(m[linha]);
    for(i=linha; i<n-1; i++){
        m[i] = m[i+1];
    }
}

void encontraMaior(int **m){
    int i, j, maior, coluna;
    maior = *(m[0]+0);
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(*(m[i]+j) > maior){
                maior = *(m[i]+j);
                coluna = j;
            }
        }
    }
    printf("\nMaior elemento = %d, coluna = %d\n", maior, coluna+1);

    for(i=0; i<n-1; i++){
        for(j=coluna; j<n; j++){
            *(m[i]+j) = *(m[i]+j+1);
        }
        free(m[i]+n-1);
    }
}

