#include <stdio.h>
#include <stdlib.h>

struct cel{
       int conteudo;
       struct cel *prox;
};
typedef struct cel celula;

void InsereFim(celula **ini, int i);
void InsereInicio(celula **ini, int v);
void EscreveLista(celula *lista);
int RemoveCelula(celula **ini, int i);
void InserirElemento(celula **ini, int v);
void LiberarLista(celula **p);
void CopiarVetorParaLista(celula **ini);
celula *CopiaLista(celula **lista);
int comparaListas(celula *uma, celula *outra);
void trocarPosicao(celula **ini);
celula *procuraElemento(celula **ini, int valor);
int menu(void);

void main(){
    celula *inicio;
    celula *copia;
    int valor;
    int i;
    int op;
    int resp;

    inicio = NULL;
    op = 0;

    while (op != 9){
       op=menu();
       switch (op){

            case 1:
                printf("\nEntre com o conteudo: ");
                scanf ("%d", &valor);
                if (inicio == NULL)
                    InsereInicio(&inicio, valor);
                else
                    InserirElemento(&inicio, valor);
                break;

            case 2:
                printf("\nEntre com o conteudo: ");
                scanf ("%d", &valor);
                resp = RemoveCelula(&inicio, valor);
                if (resp==1)
                    printf("\nConteudo REMOVIDO!!");
                else
                    if (resp==0)
                        printf("\nConteudo não encontrado!!");
                break;

            case 3:
                printf("\n===== LISTA =====");
                EscreveLista(inicio);
                break;

            case 4:
                printf("\n===== Liberar Lista =====");
                LiberarLista(&inicio);
                break;

            case 5:  // Copiar Vetor para Lista
		        CopiarVetorParaLista(&inicio);
                EscreveLista(inicio);
                break;

            case 6:  // Copiar Lista
		        copia = CopiaLista(&inicio);
		        EscreveLista(copia);
                break;

            case 7:  // Comparar Lista
                if(comparaListas(inicio, copia) == 1){
                   printf("\nSAO Iguais!!\n");
                }else 
                    printf("\nNAO sao Iguais!!\n"); 

                EscreveLista(inicio);
                EscreveLista(copia);    
                break;

            case 8:  //  Inverter posições
                printf("\nLISTA ANTES DA TROCA: ");
                EscreveLista(inicio);

                trocarPosicao(&inicio);
                printf("\nLISTA DEPOIS DA TROCA: ");
                EscreveLista(inicio);
                break;        

            case 9:  // Sair
                break;

            default:
                printf("\nOPÇÃO INCORRETA!!!");
                break;
        }

    }

    return;
}

int menu(void){
    int op;
    printf("\n==========================");
    printf("\n(1) - Inserir");
    printf("\n(2) - Remover");
    printf("\n(3) - Listar");
    printf("\n(4) - Remover todos elementos da Lista");
    printf("\n(5) - Copiar Vetor para Lista");
    printf("\n(6) - Copiar Lista");
    printf("\n(7) - Comparar Listas");
    printf("\n(8) - Inverter Posicao");
    printf("\n(9) - Sair");
        printf("\n>> ");
        scanf("%d", &op);
    return op;
}


celula *CopiaLista(celula **lista) {
    celula *saida = malloc(sizeof(celula));
    saida = NULL;
    celula *aux = *lista;
    InsereInicio(&saida, aux->conteudo);
    while (aux != NULL) {
        aux = aux->prox;
        if (aux == NULL)
            break;
	InsereFim(&saida, aux->conteudo);
    }
    return saida;
}

void CopiarVetorParaLista(celula **ini){
	int vetor[10]={10,2,3,14,22,9,6,55,5,25};
	int i;
	for (i=0;i<10;i++){
        if (*ini==NULL)
            InsereInicio(ini, vetor[i]);
        else
            InserirElemento(ini, vetor[i]);
	}
}

void LiberarLista(celula **p){
	celula *aux;
	while (*p != NULL){
		aux=*p;
		*p=aux->prox;
		free(aux);
	}
}

void InserirElemento(celula **ini, int v){
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
       if (anterior==NULL)
            InsereInicio(ini,v);
        else{ 
            aux->prox=anterior->prox;
            anterior->prox=aux;
            }
    }else{    
        p->prox=aux;
    }

    return ;
}

void InsereInicio(celula **ini, int v){
    celula *aux;
    aux= (celula*)malloc (sizeof (celula));
    aux->conteudo = v;
    aux->prox=NULL;

    if (*ini != NULL)
        aux->prox = *ini;

    *ini = aux;

    return ;
}

void InsereFim(celula **ini, int i){
    celula *aux, *fim;

    aux= (celula*)malloc (sizeof (celula));
    aux->conteudo = i;

    fim=*ini;
    if (fim==NULL)
        InsereInicio(ini, i);
    else{
      while (fim->prox!=NULL)
        fim=fim->prox;

        aux->prox=NULL;
        fim->prox=aux;
    }
   return ;
}

void EscreveLista(celula *lista){
    celula *aux;
    aux = lista;
    if(aux == NULL){
        printf("\n Lista Vazia!!");
        return ;
    }else
        printf("\nElementos da lista: ");
        while (aux != NULL){
            printf(">>%d ", (aux->conteudo));
            aux = aux->prox;
        }
}

int RemoveCelula(celula **ini,int i){
    if(*ini == NULL){
        printf("\nA lista esta vazia");
        return -1;
    }else{  
        celula *aux, *anterior=NULL;
        aux = *ini;
        while((aux->conteudo != i) && (aux->prox !=NULL)){
                anterior = aux;
                aux = aux->prox;
        }
        if (aux->conteudo == i){
            if (aux==*ini)
                *ini=(*ini)->prox;
            else
                anterior->prox = aux->prox;

            free(aux);
            return 1;
        }
    }
    return 0;
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

void trocarPosicao(celula **ini){
    int valM, valN;
    celula *antM, *antN, *M, *N, *proxN, *proxM;

    printf("\n\nInforme o valor de M: ");
    scanf("%d", &valM);
    printf("Informe o valor de N: ");
    scanf("%d", &valN); 

    antM = procuraElemento(ini, valM);
    antN = procuraElemento(ini, valN);

    if(antM == NULL){
        M = *ini;
    }else
        M = antM->prox; //o próximo ao anterior de M é o proprio M
        
        N = antN->prox; //o próximo ao anterior de N é o proprio N
        proxN = N->prox; //próximo de N 
        proxM = M->prox; //próximo de M

        if(antN == M && proxM == N){ //são elementos vizinhos
            antM->prox = N; //próximo do anterior de M aponta para N
            M->prox = proxN; //próximo de M aponta pro próximo de N
            N->prox = M; //próximo de N aponta para M

        }else{
            if(M == *ini){
                *ini = N;
            }else
                antM->prox = N; //anterior de M agora aponta para N e não M

            antN->prox = M; //anterior de N agora aponta para M e não N

            M->prox = proxN; //ao invés de apontar pro próximo de M, aponta pro próximo de N
            N->prox = proxM; //ao invés de apontar pro próximo de N, aponta pro próximo de M 
        }      
}

celula *procuraElemento(celula **ini, int valor){
    celula *aux;
    celula *anterior = NULL;
    aux = *ini;

    while(aux->conteudo != valor){ 
        anterior = aux;
        aux = aux->prox;
    }
  
    return(anterior);
}



