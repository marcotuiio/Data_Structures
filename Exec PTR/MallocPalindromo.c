#include <stdio.h>
#include <stdlib.h>

int verificaPalindromo(char teste[]);

void main(){
    char *palavra;

    palavra = malloc(sizeof(char));

    printf("Informe a frase para verificar PALINDROMO: ");
    scanf("%[^\n]", palavra);

    if(verificaPalindromo(palavra) == 1){
        printf("<<%s>> E um palindromo!!!", palavra);
    }else
        printf("<<%s>> NAO E um palindromo!!!", palavra);
    
}

int verificaPalindromo(char teste[]){  //tem um problema aqui pois deveria ser feito um parâmetro do tipo
    int i, j, size, cont = 0;            //char *teste e depois um teste=malloc(), mas não estava funcionando
    size = strlen(teste);
    j = size-1;

    for(i=0; i<size; i++){
        if(tolower(teste[i]) == tolower(teste[j])){  //comparando primeiro com último, segundo com penultimo
            cont++;
        }else{
            return (0);   //se algum caracter comparado for diferente já pode 
        }                 //encerrar pois com certeza não é um palindromo
        j--;
    }
    
    if(cont == size){
        return (1);
    }
}