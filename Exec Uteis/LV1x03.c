#include <stdio.h>

int main(){
    int a[4];
    int b[4];
    int c[10];
    int i, j, k;

    for(i=0; i<=4; i++){
        printf("VETOR A - Escreva o valor para a posicao #%d: ", i+1);
        scanf("%d", &a[i]);
    }
        for(j=0; j<=4; j++){
            printf("VETOR B - Escreva o valor para a posicao #%d: ", j+1);
            scanf("%d", &b[j]);
        } 
                
           k = j = 0;
           for(i=0; i<=4; i++){               
               c[k] = a[i];
               k++;
               c[k] = b[j];
               k++;
               j++;
           }

               for(k=0; k<=9; k++){
                   printf("%d\n", c[k]);
               }

    return 0;
}