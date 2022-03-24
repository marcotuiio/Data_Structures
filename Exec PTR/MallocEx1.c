#include <stdio.h>
#include <stdlib.h>

void main(){
    int *v, n, i;
    char *nome;

    printf("Informe o tamanho do vetor: ");
    scanf("%d", &n);

    v = malloc(n * sizeof(int));
    nome = malloc(sizeof(char));

    printf("Infome nome: ");
    scanf("%s", nome);

    printf("MOME == %s\n", nome);
    free(nome);

    for(i=0; i<n; i++){
        printf("V[%d] = ", i+1);
        scanf("%d", &v[i]);
    }
    
    printf("\n");
    for(i=0; i<n; i++){
        printf("%d ", *(v+i));
    }

}
/*
    int *p, *q;

    p = malloc(sizeof(int));   //p aponta e reserva memória com mesma qntd de bytes do tipo int 
    *p = 123;                  //conteúdo apontado por p recebe 123  
    q = malloc(sizeof(int));   //q aponta e reserva memória com mesma qntd de bytes do tipo int
    *q = *p;                   //conteúdo apontado por q recebe o mesmo conteúdo apontado por p, q=123
    q = p;                     //q aponta para onde aponta p
    free (p);                  //liberando a porção de memória apontada por p
    free (q);                  //liberando a porção de memória apontada por q
    q = NULL;                  //prática positiva, faz com que q não aponte para nada
*/