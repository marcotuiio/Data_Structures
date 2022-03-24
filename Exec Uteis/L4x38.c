#include <stdio.h>
#include <math.h>

int main(){
    int x, aux, div, pot, fat;
    float exp, teste;
    fat = 1;
    exp = 0;
    div = 0;
    pot = 0;

    printf("Informe um valor de X para calcular e^x: ");
    scanf("%d", &x);

    //enquanto((pow(x,pot)/fat) >= 0.0001)
    for(pot=0; pot<12; pot++){
        if(div > 1){
            for(aux=div; aux>1; aux--){ 
                fat = fat * aux;
            }
        exp = (float)(pow(x, pot)) / fat + exp;   
        }else{
            exp = (float)(pow(x, pot)) / 1 + exp;
        }
       div++; 
       fat = 1;
    }
    
    teste = expf(x);
    
    printf("A funcao exponecial de x: %.2f\n", teste);
    printf("O valor de e^x pela soma de 20 termos foi: %.2f", exp);

    return 0;
}