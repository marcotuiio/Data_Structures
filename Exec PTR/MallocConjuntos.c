#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *leString();
void selectionSort(char* num, int tam);
void imprimeVetor(char* Uni, int cont);
char* menos(char* vet1, char* vet2);

int main() {
    char *A, *B, *Inter;
    int achei, cont;
    A = leString();
    B = leString();

    if (strlen(A) < strlen(B))
	    Inter = malloc(sizeof(char) * strlen(A));  //alocando memória para conjunto Intersecção
    else                                           //de acordo com o tamanho de A ou B
	    Inter = malloc(sizeof(char) * strlen(B));
    
    cont = 0;

    //intersec
    for(int i=0; i<strlen(A); i++) {
        for(int j=0; j<strlen(B); j++) {
            if (A[i] == B[j]) {
                Inter[cont] = A[i];
                cont++;
            }
        }
    }
    puts("Interseccao");
    selectionSort(Inter, cont);
    imprimeVetor(Inter, cont);
    free(Inter);

    //Uniao
    char* Uni = malloc(strlen(A) + strlen(B));
    int cont2 = 0;
    for (int i=0; i<strlen(A); i++) {
        Uni[cont2] = A[i];     //copiando todos os elementos de A no conjunto União
        cont2++;
    }

    for(int i=0; i<strlen(B); i++){  //percorro todo conjunto B
	achei = 0;
	for(int j=0; j<strlen(A); j++){  //percorro todo conjunto A, por ele é igual, no momento, a união.
		if (Uni[j] == B[i]){	     //se ja houver aquele elemento na união, eu vou pro próximo
            achei=1;
			break;
		}
	}
        if (!achei){           //se entrou aqui, aquele elemento de B ainda não foi colocado em União
	 	    Uni[cont2] = B[i];   
        	cont2++;
	    }
    }
    Uni[cont2] = '\0';   //colocando \0 no final do conjunto União, pois é uma string
    puts("\n\nUniao");
    imprimeVetor(Uni, cont2);

    //Menos a-b
    puts("\n\nA-B");
    char* Sub = menos(A, B);
    imprimeVetor(Sub, strlen(Sub));

    puts("\n\nB-A");
    char* Sub2 = menos(B, A);
    imprimeVetor(Sub2, strlen(Sub2));
    return 0;
}

char* leString() {
    char *palavra = malloc(sizeof(char) * 20);
    fflush(stdin);
    puts("Insira os elementos: ");
    fgets(palavra, 20, stdin);
    palavra[strlen(palavra) - 1] = '\0';
    return palavra;
}

void selectionSort(char* num, int tam) {
    int i, j, min;
    char aux;
    for (i = 0; i < (tam - 1); i++) {
        min = i;
        for (j = (i + 1); j < tam; j++) {
            if (num[j] < num[min])
                min = j;
        }
        if (num[i] != num[min]) {
            aux = num[i];
            num[i] = num[min];
            num[min] = aux;
        }
    }
}

void imprimeVetor(char* Uni, int cont) {
    int cont2 = cont;
    for (int i = 0; i < cont2; i++) {
        do {
            if (Uni[i] == Uni[i + 1]) {
                for (int j = 1; j < cont2; j++) {
                    Uni[i + j] = Uni[i + j + 1];
                    if (j == cont2 - 1) {
                        Uni[j] = '\0';
                        cont2--;
                    }
                }
            }
        } while (Uni[i] == Uni[i + 1]);
    }
    if (cont2 == 1) {
        printf("{ %c }", Uni[0]);
    } else {
        printf("{");
        for (int i = 0; i < cont2; i++) {
            if (i == cont2 - 1) {
                printf(" %c ", Uni[i]);
            } else {
                printf(" %c ,", Uni[i]);
            }
        }
        printf("}");
    }
}

char* menos(char* vet1, char* vet2) {
    int tam1 = strlen(vet1);
    int tam2 = strlen(vet2);
    int cont = 0;
    int cont2 = 0;
    char* Sub = malloc(tam1 + tam2);
    for (int i = 0; i < tam1; i++) {
        for (int j = 0; j < tam2; j++) {
            if (vet1[i] == vet2[j]) {
                cont++;
            }
        }
        if (cont == 0) {
            Sub[cont2] = vet1[i];
            cont2++;
        }
        cont = 0;
    }
    if (cont2 == 0) {
        Sub[0] = ' ';
        Sub[1] = '\0';
    } else {
        Sub[cont2] = '\0';
    }

    return Sub;
}

