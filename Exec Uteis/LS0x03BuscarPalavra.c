#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define qntdLinhasTexto 51

bool testar(int test[], int size);

int main(){
    int i, j, rep, tPa;
    char text[1500], palavra[40];
    int aux = 0;
    int cont = 0;

    printf("Informe uma palavra para contagem: ");
    scanf("%s", palavra);
    tPa = strlen(palavra);   //obtendo o tamanho da palavra digitada para evitar uso de 'while != \0'
    int test[tPa];    //declarando uma variável vetor para testes do mesmo tamanho da palavra

    FILE * fp;
    fp=fopen("LS0x03Hino.txt", "rt");

    for(rep=1; rep<qntdLinhasTexto; rep++){     //como meu txt tem 50 linhas, eu percorro linha por linha
        fgets(text, 150, fp);   //cada linha é uma string e serão lidos no máximo 150 caracteres por linha 

        for(i=0; i<strlen(text) - tPa; i++){
            if(tolower(text[i]) == tolower(palavra[0])){   //tolower é uma função que transforma
                for(int k=0; k<tPa; k++){                  //os caracteres todos em minúsculo
                    test[k] = 0;     //inicializando o vetor de testes
                }
                aux = i;
            
            for(j=0; j<tPa; j++){          //caso as iniciais comparadas forem iguais, o próximo passo
                if(tolower(palavra[j]) == tolower(text[aux])){    //é comparar o resto das palavras 
                    test[j] = 1;    //para cada caractere igual, o vetor de testes é preenchido com 1
                    aux++;
                }
            }
            if(testar(test, tPa))
                cont++;
            
            }  
        }
    }

    fclose(fp);

    printf("A palavra %s repetiu %d vez(es)", palavra, cont);

    return 0;
}

bool testar(int test[], int size){    //função booleana que só retorna verdadeiro ou falso
    for(int i=0; i<size; i++){         
        if(test[i] != 1){    //ela confere nosso vetor de testes e se algum valor for diferente de 1
            return false;    //significa que as palavras comparadas não foram idênticas e retorna falso
        }
    }
    return true;       //se não houve nada diferente de 1, retorna verdadeiro e o 
}                      //contador de repetição recebe +1