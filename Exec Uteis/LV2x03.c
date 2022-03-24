#include <stdio.h>

int main(){
    int a[10], b[10];
    int i, j, fat, aux;
    fat = 1;
    j = 0;

    for(i=0; i<=9; i++){
        printf("Vetor A - Posicao #%d: ", i+1);
        scanf("%d", &a[i]);
    }

    for(i=0; i<=9; i++){
        if(a[i] > 1){
            for(aux=a[i]; aux<=2; aux--){
                fat = aux * fat;
            }
            b[j] = fat;
        }else{
            b[j] = a[i];
        }
        j++;
    }

    for(j=0; j<=9; j++){
        printf("Vetor B - Posicao #%d: %d\n", j+1, b[j]);
    }

    return 0;
}