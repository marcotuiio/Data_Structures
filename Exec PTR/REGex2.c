#include <stdio.h>
#include <string.h>

struct reg{
    float nota[3];
    char nome[20];
    float media;
};
typedef struct reg Ficha;

void ordena(Ficha alu[]);
void escreve(Ficha alu[]);

void main(){
    Ficha aluno[5];
    int i, j, cont = 0;
    float mediaTurma = 0;

    for(i=0; i<5; i++){
        aluno[i].media = 0;
    }

    for(i=0; i<5; i++){
        printf("Informe o nome do aluno: ");
        scanf("%s", aluno[i].nome);
        for(j=0; j<3; j++){
            printf("Informe a nota %d: ", j+1);
            scanf("%f", &aluno[i].nota[j]);
            aluno[i].media = aluno[i].media + aluno[i].nota[j];
        }
        aluno[i].media = aluno[i].media / 3;
        mediaTurma = mediaTurma + aluno[i].media;
    }
    mediaTurma = mediaTurma / 5;

    for(i=0; i<5; i++){
        if(aluno[i].media > mediaTurma){  
            cont++;
        }
    }

    ordena(aluno);
    escreve(aluno);

    printf("\nMEDIA DA TURMA === %.2f\n", mediaTurma);
    printf("%d alunos acima da media", cont);
    
}

void ordena(Ficha alu[]){
    int i, j;
    Ficha aux;
    for(i=0; i<5; i++){
        for(j=0; j<4-i; j++){
            if(strcmp(alu[j].nome, alu[j+1].nome) > 0){
                aux = alu[j];
                alu[j] = alu[j+1];
                alu[j+1] = aux;
            }
        }
    }
}

void escreve(Ficha alu[]){
    int i;
    for(i=0; i<5; i++){
        printf("\nNome = %s\n", alu[i].nome);
        printf("Media = %.2f\n", alu[i].media);
        printf("\n");
    }
}
