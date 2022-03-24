#include <stdio.h>

int main(){
    int i, j, maior, menor, lin, col;
    int A[10][10];

    FILE * matriz;
    matriz=fopen("LMx04.txt", "r");

    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            fscanf(matriz, "%d", &A[i][j]);
        }
    }
    fclose(matriz);

    maior = A[0][0];
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(A[i][j] > maior){
                maior = A[i][j];
                lin = i;
            }
        }
    }

    menor = 99999;
    for(j=1; j<10; j++){
        if(A[lin][j] < menor){
            menor = A[lin][j];
            col = j;
        }
    }

    printf("MINIMAX == %d[%d][%d]", menor, lin+1, col+1);

    return 0;
}
