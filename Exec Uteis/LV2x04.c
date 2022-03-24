#include <stdio.h>

int main(){
    int a[9];
    int i, aux, aux2, aux3;
    aux3=aux2=aux=0;

    for(i=0; i<=9; i++){
        printf("Vetor A - Posicao #%d: ", i+1);
        scanf("%d", &a[i]);
    }

    aux3 = a[9];
    aux2 = a[0];
    a[0] = aux3;
    a[9] = aux2;

    for(i=1; i<=4; i++){           
        aux = a[i];                   
        a[i] = a[9-i];              
        a[9-i] = aux;                       
    }                                 

    for(i=0; i<=9; i++){
        printf("Novo A - Posicao #%d: %d\n", i+1, a[i]);
    } 

    return 0;
}