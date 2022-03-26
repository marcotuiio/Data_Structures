#ifndef FILA_CIRC_H
#define FILA_CIRC_H

//Fila é uma estrutura de dados que funciona como um vetor circular, nesse caso os valores
//são alocados dinamicamente

typedef void* Fila_Circular;
typedef void* Item;

Fila_Circular criaFila(int max_size);
//cria uma fila e inicializa começo, fim e valores que possui como vazios.
//Recebe o parametro de tamanho máximo na sua criação

bool fila_vazia(Fila_Circular q);
//confere para o caso da fila estar vazia para realizar
//próximas operações

bool fila_cheia(Fila_Circular q);
//confere se a fila está cheia, logo se é possível realizar
//operações

void destroi_fila(Fila_Circular q);
//libera elementos para evitar vazamentos de memória

bool enfila_circ(Fila_Circular q, Item x);
//adiciona elementos no rabo fila circular

Item desenfila_circ(Fila_Circular q);
//remove elementos na cabeça da fila circular

void printFila_circ(Fila_Circular q);
//remove os elementos da cabeça e exibi o valor deles

#endif