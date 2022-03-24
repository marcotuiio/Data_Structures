#include <stdio.h>

int main(){
    int R[10], S[10], X[10], Z[20];
    int i, j, cont = 0;

    for(i=0; i<10; i++){
        printf("Defina valor para o vetor R: ");
        scanf("%d", &R[i]);
    }
    for(i=0; i<10; i++){
        printf("Defina valor para o vetor S: ");
        scanf("%d", &S[i]);
    }

    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(R[i] == S[j]){
                X[cont] = R[i];
                cont++;
            }
        }
    }

    cont = 0;
    for(i=0; i<10; i++){
        Z[cont] = R[i];
        cont++;
        Z[cont] = S[i];
        cont++;
    }

    printf("Vetor Z\n"); 
    for(i=0; i<20; i++){
        printf("%d  ", Z[i]);
    }

    printf("\nVetor X\n"); 
    for(i=0; i<10; i++){
        printf("%d  ", X[i]);
    }

    return 0;
}