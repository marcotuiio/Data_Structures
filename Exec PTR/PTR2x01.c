#include <stdio.h>

void main(){

    float vet[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float *f;
    int i;
    char *nome = "Algoritmos";
    char *p3;
    f = vet;

    for(i = 0 ; i <= 4 ; i++){
        printf("\ni = %d\n",i);   //só imprime o valor de i             
        printf("vet[%d] = %.1f\n",i, vet[i]);   //indica o indice do vetor e seu respectivo valor
    // printf("*(vet + i) = %f\n", vet[i]);  imprime o terceiro elemento de vet, *(vet) aponta para a o inicio
        printf("*(f + %d) = %.1f\n",i, *(f+i));  //indica as seguintes posições apontadas por f e seus valores
        printf("&vet[%d] = %p\n",i, &vet[i]);   //indica o endereço de memória do vetor com respectivo indice i
        printf("(f + %d) = %p\n",i, f+i);     //indica o endereço de memória que f e os próximos f+i apontam  
    }                                         //%p é para imprimir endereços de memória
    
    p3 = nome;   //p3 apontada para nome, que é um vetor de char
    printf("\n%c \n", *p3); //imprimindo nome[0]
    printf("%s ", p3); //imprimindo todo o vetor apontado por p3
}