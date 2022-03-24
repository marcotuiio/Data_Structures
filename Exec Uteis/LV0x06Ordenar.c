#include <stdio.h>
#define n 10

int Ordena(int v[], int qntd);
int escreveVetor(int v[], int qntd);

void main(){
    int X[n], menor[3], i;

    for(i=0; i<n; i++){
        printf("VetorX #%d: ", i+1);
        scanf("%d", &X[i]);
    }
    Ordena(X, n);
    printf("Vetor ordenado: \n");
    escreveVetor(X, n);
}

int Ordena(int v[], int qntd){
    int i, j, aux;
    for(i=0; i<(qntd-1); i++){
        for(j=0; j<(qntd-1); j++){
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
    return (v);
}

int escreveVetor(int v[], int qntd){
    int i;
    for(i=0; i<qntd; i++){
        printf("%d  ", v[i]);
    }
}

