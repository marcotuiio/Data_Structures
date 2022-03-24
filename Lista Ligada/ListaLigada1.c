#include <stdio.h>
#include <stdlib.h>

struct cel{
    int conteudo;
    struct cel *prox;
};
typedef struct cel celula;

void escreveLista(celula *i);
void insereInicio(celula **inicio, int val);
void insereFinal(celula *fim, int val);
void insereMeio(celula *aux);
void removeCelula(celula **p);
celula *copiaLista(celula **lista);
void CopiarVetorParaLista(celula **ini);
void inserirElemento(celula **ini, int v);
void liberarLista(celula **p);
int comparaListas(celula *uma, celula *outra);

void main(){
    celula *inicio;
    celula *aux;
    celula *teste;
    int val, socorro;

    inicio = NULL;
    aux = malloc(sizeof(celula));
    aux -> conteudo = 10;
    inicio = aux;
    aux -> prox = NULL;

    escreveLista(inicio);
    printf("\nInforme o primeiro elemento: ");
    scanf("%d", &val);
    insereInicio(&inicio, val);
    escreveLista(inicio);

    printf("\nInforme o primeiro elemento: ");
    scanf("%d", &val);
    insereInicio(&inicio, val);
    escreveLista(inicio);

    printf("\nInforme o ultimo elemento: ");
    scanf("%d", &val);  
    insereFinal(inicio, val);
    escreveLista(inicio);

    insereMeio(inicio);
    escreveLista(inicio);

    removeCelula(&inicio);

    printf("\nLISTA ORIGINAL: ");
    escreveLista(inicio);

    printf("\n");

    copiaLista(&inicio);     

    CopiarVetorParaLista(&teste);
    escreveLista(teste);
    escreveLista(inicio);
    socorro = comparaListas(inicio, teste);

    if(socorro == 1){
        printf("\nSAO Iguais!!\n");
    }else 
        printf("\nNAO sao Iguais!!\n");  
}

void escreveLista(celula *i){
    printf("\n");
    while(i != NULL){
        printf("%d ", i -> conteudo);
        i = i -> prox;
    }   
}

void insereInicio(celula **inicio, int val){
    celula *aux;
    aux = malloc(sizeof(celula));

    aux -> conteudo = val;
    aux -> prox = *inicio;
    *inicio = aux;
}

void insereFinal(celula *fim, int val){
    celula *aux;
    while(fim -> prox != NULL){
        fim = fim -> prox;
    }
    aux = malloc(sizeof(celula));

    aux -> conteudo = val;
    aux -> prox = NULL;
    fim -> prox = aux;
}

void insereMeio(celula *aux){
    int j, posi;
    celula *novo;

    printf("\nInforme a posicao que deseja inserir um elemento: ");
    scanf("%d", &posi);

    j = 1;
    while(j < posi-1){ //posi é a posição onde será inserido
        aux = aux -> prox;
        j++;
    }
    novo = malloc(sizeof(celula));

    printf("Informe o valor desse elemento: ");
    scanf("%d", &novo -> conteudo); 
    novo -> conteudo = novo -> conteudo;
    novo -> prox = aux -> prox;
    aux -> prox = novo;
}

void removeCelula(celula **p){
    celula *aux, *anterior=NULL;
    aux = *p;
    int i;
    printf("\nInforme o conteudo que deseja remover: ");
    scanf("%d", &i);

    while((aux->conteudo != i) && (aux->prox !=NULL)){       
            anterior = aux;
            aux = aux->prox;
    }
        if(aux->conteudo==i){     
            if (aux==*p)
                *p=(*p)->prox;
            else
                anterior->prox = aux->prox;

        free(aux);
        return;      
        }else
            printf("Conteudo NAO encontrado\n"); 
}

celula *copiaLista(celula **lista){
    celula *saida = malloc(sizeof(celula));
    saida = NULL;
    celula *aux = *lista;

    insereInicio(&saida, aux->conteudo);
    while(aux != NULL){
        aux = aux -> prox;
        if(aux == NULL){
            break;
        }
        insereFinal(saida, aux -> conteudo);
    }
    printf("\nLISTA COPIA: ");
    escreveLista(saida);
}

void CopiarVetorParaLista(celula **ini){
	int vetor[10]={10,2,3,14,22,9,6,55,5,25};
	int i;
	for (i=0; i<10; i++){
        if (*ini == NULL){
            insereInicio(ini, vetor[i]);
        }else
            inserirElemento(ini, vetor[i]);
	}
}

void inserirElemento(celula **ini, int v){
    celula *aux, *p;
    celula  *anterior=NULL;
    aux= (celula*)malloc (sizeof (celula));
    aux->conteudo = v;
    aux->prox = NULL;

    p = *ini;
    while ((p->conteudo > v) && (p->prox!=NULL)){
       anterior = p;
       p = p->prox;
    }

    if (p->conteudo<=v){
       if (anterior==NULL){
            insereInicio(ini,v);
        }else{
            aux->prox=anterior->prox;
            anterior->prox=aux;
        }
    }else{
        p->prox=aux;
    }
    return ;
}

void liberarLista(celula **p){
	celula *aux;
	while (*p!=NULL){
		aux=*p;
		*p=aux->prox;
		free(aux);
	}
}

int comparaListas(celula *uma, celula *outra){
    int cont1, cont2, achei;
    cont1 = achei = 0;
    celula *atual1 = uma;
    celula *atual2 = outra;

    while(atual1 != NULL){
        celula *atual2 = outra;
        cont2 = 0;
        while(atual2 != NULL){
            if(atual1 -> conteudo == atual2 -> conteudo){
                achei++;
            }
            cont2++;
            atual2 = atual2 -> prox;            
        }
        cont1++;
        atual1 = atual1 -> prox;
    }
    if((cont1 == cont2) && (achei == cont1)){
        return (1);
    }else
        return (0);
}