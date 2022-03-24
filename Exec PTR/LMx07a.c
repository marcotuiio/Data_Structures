#include <stdio.h>
#define T 12

void escreveMatriz(int matriz[T][T]);

int main(){
    int A[T][T]; 
    int i, j, m, n, soma, maior, contador, lin, col;
    float media;
    contador = soma = 0;

    FILE * matriz;
    matriz=fopen("LMx07.txt", "r");

    for(i=0; i<T; i++){
        for(j=0; j<T; j++){
            fscanf(matriz, "%d", &A[i][j]);
        }
    }
    escreveMatriz(A);
    maior = A[0][5];

    m = 0;  //marca linha de inicio 
    n = 11; //marca linha de final
    j = 5;  //coluna de interesse
    while(j > 0){
        for(i=m; i<n; i++){
            soma = soma + A[i][j];
            contador++;
            if(A[i][j] > maior){
                maior = A[i][j];
                lin = i;
                col = j;
            }
        }
        m++;
        n--;
        j--;
    }

    m = 0;  //marca linha de inicio 
    n = 11; //marca linha de final
    j = 6;  //coluna de interesse
    while(j != 13){
        for(i=m; i<n; i++){
            soma = soma + A[i][j];
            contador++;
            if(A[i][j] > maior){
                maior = A[i][j];
            }
        }
        m++;
        n--;
        j++;
    }
    media = (float) soma / contador;

    printf("A media na area azul foi = %.2f\n", media);
    printf("O maior elemento da area azul = %d[%d][%d]\n", maior, lin+1, col+1);

    return 0;
}

void escreveMatriz(int matriz[T][T]){
    int i, j;
    for(i=0; i<T; i++){
        for(j=0; j<T; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}