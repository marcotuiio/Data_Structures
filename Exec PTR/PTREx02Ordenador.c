#include <stdio.h>
#define size 18

int escreveVetor(int *(p), int tam);
int ordenaPtr(int *(p));
void leArquivo(int *p, FILE *arq);

void main(){
    int i, j, k, A[size], B[size], C[2*size];
    int *p, *q, *r;

    FILE * vets;
    vets=fopen("PTREx02.txt", "r");

    p = A;
    leArquivo(p, vets);
    q = B;
    leArquivo(q, vets);

    fclose(vets);

    printf("Vetor A:  ");
    escreveVetor(p, size);
    printf("Vetor B:  ");
    escreveVetor(q, size);

    ordenaPtr(p);
    ordenaPtr(q);

    printf("Vetor A ordenado:  ");
    escreveVetor(p, size);
    printf("Vetor B ordenado:  ");
    escreveVetor(q, size);

    i = j = 0;
    for(k=0; k<2*size; k++){
        if(i<size && j<size){
            if(*(p+i) <= *(q+j)){
                C[k] = *(p+i);
                i++;
            }else{
                C[k] = *(q+j);
                j++;
            }
        }else if(i<size){
                C[k] = *(p+i);
                i++;
        }else if(j<size){
                C[k] = *(q+j);
                j++;
        }
    } 

    r = C;
    printf("Vetor C ordenado:  ");
    escreveVetor(r, 2*size);

}

void leArquivo(int *p, FILE *arq){
    int i;
    for(i=0; i<size; i++){
        fscanf(arq, "%d", p+i);
    } 
}

int escreveVetor(int *(p), int tam){
    int i;
    for(i=0; i<tam; i++){
        printf("%d  ", *(p+i));
    }
    printf("\n");
}

int ordenaPtr(int *(p)){
    int i, j, aux;
    for(i=0; i<size-1; i++){
        for(j=0; j<size-1; j++){
            if(*(p+j) > *(p+j+1)){
                aux = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = aux;
            }
        }
    }
}