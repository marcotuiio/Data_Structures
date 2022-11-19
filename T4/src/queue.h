#include "libs.h"

#ifndef QUEUE_H
#define QUEUE_H

// Filas são estruturas de dados alocadas dinamicamente na qual
// sempre que adiciono um elemento ele passa a ser o último da fila
//(ordem de chegada) e caso deseja remover um elemento, removerei
// o primeiro que foi adicionado e assim por diante

void *createQueue();
// Cria uma fila vazia

bool enfila(Queue q, Node n);
// crio uma nov celula e adiciona elemento n a fila

Node desenfila(Queue q);
// removo o elemento

bool isEmpty(Queue q);
// verifica se a fila está vazia

void printFila(Queue q);

#endif