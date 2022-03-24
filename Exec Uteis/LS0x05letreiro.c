#include <stdio.h>
#include <string.h>
#include <windows.h>
#define letreiro 20

void main(){
    char frase[20], aux[20];
    int i, j, tamanho;

    printf("Informe o conteudo para o letreiro: ");
    scanf("%[^\n]", frase);

    tamanho = strlen(frase);
    strcpy(aux, frase);

    printf("\n%s\n", frase);
    Sleep(1000);

    for(j=0; j<tamanho; j++){       
        for(i=0; i<tamanho; i++){
            frase[i] = frase[i+1];
        } 
        printf("%s\n", frase);
        Sleep(1000); 
    }

    for(i=0; i<tamanho; i++){
        frase[i] = aux[i];
        printf("%s\n", frase);
        Sleep(1000);
    }    

}
