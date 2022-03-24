#include <stdio.h>
#include <string.h>

int main(){
    char palavra[40], j;
    int i=0;
    int cont=0;

    printf("Informe um caracter para avaliar sua presenca: ");
    scanf("%c", &j);
    printf("Informe uma palavra: ");
    scanf("%s", palavra);
    
    while(palavra[i] != '\0'){
        if(palavra[i] == j){
            cont++;
        }
        i++;
    }

    printf("O tamanho da string pelo LACO: %d\n", i);
    printf("O tamanho da string pela FUNCAO: %ld\n", strlen(palavra));
    printf("O caracter %c apareceu %d vez(es) na string", j, cont);

    return 0;
}
