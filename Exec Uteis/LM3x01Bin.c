#include <stdio.h>

int main (){
    int i, decimal, aux, binario[10];

    printf("Escreva um numero para converter em binario: "); 
    scanf("%d", &decimal); 

    while(decimal != 0){
        aux = decimal;
        for(i=9; i>=0; i--){
            if(decimal % 2 == 0){
                binario[i] = 0;
                decimal = decimal / 2;
            }else{ 
                binario[i] = 1;
                decimal = decimal / 2;
            }        
        }

        printf("o equivalente em binario do numero %d: ", aux);
        for(i=0; i<=9; i++){
            printf("%d", binario[i]);
        }
        printf("\nEscreva um numero para converter em binario: "); 
        scanf("%d", &decimal);
    }    

    return 0;
}