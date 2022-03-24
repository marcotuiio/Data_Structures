#include <stdio.h>

int escreveVetor(int v[], int qntd);
int trocaValores(int *p, int *q);

void main(){
    int vet[30], i;
    int *p, *q;

    FILE * num;
    num=fopen("PTRVet1x07.txt", "r");
    
    for(i=0; i<30; i++){
        fscanf(num, "%d", &vet[i]);
    }
    fclose(num);

    p = &vet;
    q = &vet[29];
    escreveVetor(vet, 30);
    printf("\n");

    while(p<q){
        if(*p == 0){
            while(*q == 0){
                q--;
            }
            trocaValores(p, q);
        }
        p++;
    }
    escreveVetor(vet, 30);
}

int escreveVetor(int v[], int qntd){
    int i;
    for(i=0; i<qntd; i++){
        printf("%d  ", v[i]);
    }
}

int trocaValores(int *p, int *q){
    *p = *q;
    *q = 0;
}
//jogar zeros pro final
