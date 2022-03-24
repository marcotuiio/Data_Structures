#include <stdio.h>

int converteChar(int x);

void main(){
    char hexa[10];
    int i, q, r, cont;
    cont = 9;

    printf("Escreva um numero decimal: ");
    scanf("%d", &q);
    
        while(q > 16){
            r = q % 16;
            q = q / 16;
            hexa[cont] = converteChar(r);         
            cont = cont - 1;
        }
        hexa[cont] = converteChar(q);

        for(i=cont; i<10; i++){
            printf("%c", hexa[i]);
        } 
}

int converteChar(int x){
    char aux[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    return (aux[x]);
}