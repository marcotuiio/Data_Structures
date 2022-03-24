#include <stdio.h>
#define T 12

void escreveMatriz(int *p);
void leMatriz(int *p, FILE *arq);

void main(){
    int A[T][T]; 
    int i, j, m, n, soma, maior, contador, lin, col;
    int *p;
    float media;
    contador = soma = 0;

    FILE * matriz;
    matriz=fopen("LMx07.txt", "r");

    p = A[0];
    leMatriz(p, matriz);
    escreveMatriz(p);

    maior = A[0][1];

    m = 1;  //marca linha de inicio 
    n = 10; //marca linha de final
    i = 0;  //linha de interesse
    while(i < 5 || (i > 6 && i < T)){
        for(j=m; j<n; j++){
            soma = soma + *(p+i*T+j);
            contador++;
            if(*(p+i*T+j) > maior){
                maior = *(p+i*T+j);
                lin = i;
                col = j;
            }
        }
        i++;
        if(i < 5){
            m++;
            n--;
        }else if(i > 6 && i < T){
                m--;
                n++;
        }else if(i == 5 || i == 6){
                i = 7;
        }
    }

    media = (float) soma / contador;

    printf("A media na area azul foi = %.2f\n", media);
    printf("O maior elemento da area azul = %d[%d][%d]\n", maior, lin+1, col+1);

}

void leMatriz(int *p, FILE *arq){
    int i, j;
    for(i=0; i<T; i++){
        for(j=0; j<T; j++){
            fscanf(arq, "%d", p+i*T+j);
        }
    }    
}

void escreveMatriz(int *p){
    int i, j;
    for(i=0; i<T; i++){
        for(j=0; j<T; j++){
            printf("%d ", *(p+i*T+j));
        }
        printf("\n");
    }
}

