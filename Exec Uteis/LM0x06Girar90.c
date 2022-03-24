#include <stdio.h>
#define n 4

void girar90(int matriz[n][n]);
void escreveMatriz(int matriz[n][n]);

void main(){
    int matriz[n][n];
    int i, j;

    FILE * fp;
    fp=fopen("LM0x06coord.txt", "r");

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            fscanf(fp, "%d", &matriz[i][j]);
        }
    }
    fclose(fp);
    
    escreveMatriz(matriz);
    printf("\n");
    girar90(matriz);
    escreveMatriz(matriz);
    printf("\n");
    girar90(matriz);
    escreveMatriz(matriz);
    printf("\n");
    girar90(matriz);
    escreveMatriz(matriz);
}

void girar90(int matriz[n][n]){
    int res[n][n];
    int i, j;
    int lOri, cDest = n-1; 
    for(lOri=0; lOri<n; lOri++){
        for(j=0; j<n; j++){
            res[j][cDest] = matriz[lOri][j];
        }
        cDest = cDest - 1;
    }  
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            matriz[i][j] = res[i][j];
        }
    }
}

void escreveMatriz(int matriz[n][n]){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}