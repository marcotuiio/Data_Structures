#include <stdio.h>
#define n 20

int compara(int x[]);

void main(){
    int vetor[n], i;

    for(i=0; i<n; i++){
        printf("Valor para a posicao #%d: ", i+1);
        scanf("%d", &vetor[i]);
    }
    printf("O maior elemento foi: %d", compara(vetor));
}

int compara(int x[]){
    int i;
    int maior = x[0];
    for(i=1; i<n; i++){
        if(x[i] > maior){
            maior = x[i];
        }
    }
    return (maior);
}