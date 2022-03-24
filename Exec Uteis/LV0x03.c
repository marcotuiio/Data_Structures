#include <stdio.h>
#define max 20

int main(){     
    int vetor[max];
    int i, j, aux;

    printf("Informe o valor para a posicao #1: ");
    scanf("%d", &vetor[0]);

    for(i=1; i<max; i++){
        printf("Informe o valor para a posicao #%d: ", i+1);
        scanf("%d", &vetor[i]);
        for(j=0; j<i; j++){
            if(vetor[i] < vetor[j]){
                aux = vetor[j];          
                vetor[j] = vetor[i];
                vetor[i] = aux;
            }
        }
    }

    printf("O vetor ordenado em ordem crescente:\n");
    for(i=0; i<max; i++){
        printf("%d ", vetor[i]);
    }

    return 0;
}