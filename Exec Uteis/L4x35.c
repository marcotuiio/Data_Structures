#include <stdio.h>

int main(){
    int n, fat, div, aux;
    float soma;
    soma = 0;
    fat = 1;
    div = 0;

    for(n=100; n>=80; n--){
        if(div > 1){
            for(aux=div; aux>=2; aux--){
                fat = fat * aux;
            }
            soma = (n/fat) + soma;
        }else{
            soma = n + soma;
        }
        div++;
        fat = 1;
    }

    printf("A soma aproximada dos 20 primeiros termos da serie == %.f", soma);

    return 0;
}