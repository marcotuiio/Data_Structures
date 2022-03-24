#include <stdio.h>
#define N 6

void EscreveMatriz(int *p);
void PreencheMatriz(int *p, int l, int c, int S, int val);
void main(){

    int matriz[N][N];
    int *p;

    p = matriz[0];
    PreencheMatriz(p,0,0,6,1);
    printf("================\n");
    EscreveMatriz(p);

    PreencheMatriz(p,1,1,4,2);
    printf("================\n");
    EscreveMatriz(p);

    PreencheMatriz(p,2,2,2,3);
    printf("================\n");
    EscreveMatriz(p);    
}

void PreencheMatriz(int *p, int l, int c, int S, int val){
    int i,j;
    for (i=l; i<l+S; i++){  
        for(j=c; j<c+S; j++){
           *(p+i*N+j) = val; 
        }         
    }
}

void EscreveMatriz(int *p){
    int i,j;
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            printf("%d ",*(p+i*N+j));
        }    
        printf("\n");
    }
}
