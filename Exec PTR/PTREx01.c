#include <stdio.h>
#define n 25

int escreveVetor(int *(p));
int ordenaPtr(int *(p));

void main(){
    int i, j, aux, A[n];
    int *p;

    FILE * arq;
    arq=fopen("PTREx01.txt", "r");

    p = A;
    for(i=0; i<n; i++){
        fscanf(arq, "%d", p+i);
    } 
    fclose(arq);

    printf("Vetor A normal:  ");
    escreveVetor(p);

    printf("Vetor A ordenado:  ");
    ordenaPtr(p);
    escreveVetor(p);

}

int escreveVetor(int *(p)){
    int i;
    for(i=0; i<n; i++){
        printf("%d  ", *(p+i));
    }
    printf("\n");
}

int ordenaPtr(int *(p)){
    int i, j, aux;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-1; j++){
            if(*(p+j) > *(p+j+1)){
                aux = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = aux;
            }
        }
    }
}