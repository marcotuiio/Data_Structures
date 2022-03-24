#include <stdio.h>
#include <math.h>

int main(){
    int x, div, exp;
    float aux, soma;
    div = 1;
    soma = 0;

    printf("Informe um valor para X: ");
    scanf("%d", &x);

    for(exp=25; exp>=1; exp--){
        aux = (pow(x, exp)) / (float) div;
        div++; 

        if(exp % 2 == 0){
            soma = soma - aux;
        }else
            soma = soma + aux;
    }

    printf("A soma da sequencia foi: %.f", soma);

    return 0;
}