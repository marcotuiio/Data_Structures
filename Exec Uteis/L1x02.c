#include <stdio.h>
#include <string.h>

int main(){
    float maior, menor, altura, media, soma;
    int i, j, qntdH;
    char sexo[2];
    char aux[] = "F";
    soma = i = j = qntdH = 0;
    maior = -1;
    menor = 999;

    while(i < 5){
        printf("Informe a altura: ");
        scanf("%f", &altura);
        printf("Digite M para sexo masculino e F para sexo feminino: ");
        scanf("%s", sexo);

        if(altura < menor){
            menor = altura;
        }
        if(altura > maior){
            maior = altura;
        }

        if(strcmp(sexo, aux) == 0){
            soma = soma + altura;
            j = j + 1;
        }else{
            qntdH = qntdH + 1;
        } 
        i++;   
    }
    media = soma / j;

    printf("A media de alturas da mulheres foi de %.2f\n", media);
    printf("A maior altura do grupo foi %.2f\n", maior); 
    printf("A menor altura do grupo foi %.2f\n", menor); 
    printf("A quantidade de homens no grupo foi %d\n", qntdH);

    return 0;
}