#include <stdio.h>

int main(){
    int nota[10];
    int i, soma, contador;
    float media;
    soma = 0;
    contador = 0;
    
    for(i=0; i<=9; i++){
        printf("Informe a nota do aluno #%d: ", i+1);
        scanf("%d", &nota[i]);
        soma = soma + nota[i]; 
    }
    media = soma / 10.0;
     
        for(i=0; i<=9; i++){
            if(nota[i] > media){
            contador = contador + 1; 
            } 
        }

    printf("A media foi: %.2f\n", media);
    printf("Qntd de notas acima da media: %d", contador);

    return 0;
}