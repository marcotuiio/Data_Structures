#ifndef FILA_CIRC_H
#define FILA_CIRC_H

#include <stdbool.h>

/*
 * Uma fila  ́e uma sequência de itens (Sequencia<<Item>> a partir da qual
 * podem-se eliminar itens numa extremidade (chamado in ́ıcio da fila e na
 * qual podem-se inserir itens na outra extremidade (final da fila). Ou seja, a
 * inserção e remoção de elementos numa fila segue a disciplina FIFO (first
 * in, first out). Uma fila sem elementos  ́e denominada fila vazia.
*/

typedef void* Fila_Circular;
typedef void* Item;

Fila_Circular criaFila(int max_size);
// *Retorna Sequencia<<Item>>. Isto  ́e, cria uma fila vazia.

bool fila_vazia(Fila_Circular q);
// * Retorna Sequencia.vazia(f). Isto ́e, retorna verdadeiro se
// f está vazia; falso, caso contrário.

bool fila_cheia(Fila_Circular q);
// * Retorna Sequencia.cheia(f). Isto ́e, retorna verdadeiro se
// f está cheia; falso, caso contrário.

void destroi_fila(Fila_Circular q);
//libera elementos para evitar vazamentos de memória

bool enfila_circ(Fila_Circular q, Item x);
//adiciona elementos no rabo fila circular

Item getElement(Fila_Circular q, int n);
// recebe a fila e um determinado indice e
// retorna o valor naquele determinado indice

int getSize(Fila_Circular q);
// recebe uma fila e retorna a quantidade de 
// valores que está armazenando

Item desenfila_circ(Fila_Circular q);
// * para executar, fila não pode estar vazia
// * Retorna Sequencia.reti(f). Isto  ́e, retira e retorna o
// primeiro elemento da fila.

void removeTudo(Fila_Circular q);
// * remove todos os elementos da cabeça, até que a fila esteja vazia

void freeValue(Fila_Circular q);
// * libera a memória do vetor da fila

#endif