#include <stdio.h>

int main(){
    int v[9], m[2];
    int i, j, maior;
    maior = 0;

    for(i=0; i<=9; i++){
        printf("Posicao #%d: ", i+1);
        scanf("%d", &v[i]);
    }
    for(i=0; i<=9; i++){
        if(v[i] > maior){
           maior = v[i];
        }
    }
    for(j=0; j<=2; j++){
        m[j] = maior;
    }

    for(j=0; j<=2; j++){
       for(i=0; i<=9; i++){
           if(v[i] < m[j]){
              m[j] = v[i];
           }
       }
    }

    for(j=0; j<=2; j++){
        printf("%d\n", m[j]);
    }

    return 0;
}