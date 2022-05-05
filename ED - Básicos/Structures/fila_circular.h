#ifndef FILA_CIRCULAR_H
#define FILA_CIRCULAR_H

//Fila é uma estrutura de dados que funciona como um vetor circular, nesse caso os valores
//são alocados dinamicamente

struct queue{
    int *values;
    int head, tail, num_entries, size;
};
typedef struct queue fila_circ;

void init_circ(fila_circ *q, int max_size);
//cria uma fila e inicializa começo, fim e valores que possui como vazios

bool fila_vazia(fila_circ *q);
//confere para o caso da fila estar vazia para realizar
//próximas operações

bool fila_cheia(fila_circ *q);
//confere se a fila está cheia, logo se é possível realizar
//operações

bool enfila_circ(fila_circ *q, int x);
//adiciona elementos no rabo fila circular

int desenfila_circ(fila_circ *q);
//remove elementos na cabeça da fila circular

void printFila_circ(fila_circ *q);
//remove os elementos da cabeça e exibi o valor deles

#endif