#include <stdio.h>
int main(){
    int tipo;
    float produto, descf, descc, descn, valorf, valorc, valorn;

    printf("Digite 1 para FUNCIONARIO, 2 para CLIENTE CADASTRADO ou 3 para CLIENTE NORMAL: ");
    scanf("%d", &tipo);
    printf("Infome o valor do produto: ");
    scanf("%f", &produto);

    switch(tipo){
        case 1:
        descf = 17 * produto / 100;
        valorf = produto - descf;

        printf("O desconto foi de %.2f e o valor final de %.2f", descf, valorf);
        break;

        case 2:
        descc = 8 * produto / 100;
        valorc = produto - descc;

        printf("O desconto foi de %.2f e o valor final de %.2f", descc, valorc);
        break;

        case 3:
        printf("O produto nao tem desconto, valor final de %.2f", produto);
        break;

        default:
        printf("ERRO ERRO ERRO");
        break;
    }

    return 0;
}