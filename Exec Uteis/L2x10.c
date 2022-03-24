#include <stdio.h>

int main(){
    int canal, nPessoas, c4, c5, c7, c12, aux;
    float pc4, pc5, pc7, pc12;
    c4 = c5 = c7 = c12 = 0;

    while(canal != 0){
        do{
            printf("Insira o canal: ");
            scanf("%d", &canal);
        }while(canal == -1);
            printf("Informe a quantidade de pessoas assistindo: ");
            scanf("%d", &aux);

        if(canal == 4){            
            c4 = c4 + aux;
        }else if(canal == 5){
            c5 = c5 + aux;
        }else if(canal == 7){
            c7 = c7 + aux;
        }else if(canal == 12){
            c12 = c12 + aux;
        }else{
            printf("CANAL INVALIDO\n");
        }
    }
    nPessoas = c4+ c5 + c7 + c12;
    pc4 = (float)c4 * 100 / nPessoas;
    pc5 = (float)c5 * 100 / nPessoas;
    pc7 = (float)c7 * 100 / nPessoas;
    pc12 = (float)c12 * 100 / nPessoas;

    printf("O percentual de audiencia do canal 4: %.f %\n", pc4);
    printf("O percentual de audiencia do canal 5: %.f %\n", pc5);
    printf("O percentual de audiencia do canal 7: %.f %\n", pc7);
    printf("O percentual de audiencia do canal 12: %.f %", pc12);

    return 0;
}