#include "/mnt/c/Users/marco/OneDrive/Área de Trabalho/UEL/Data_Structures/1UTIL/libs.h"

#ifndef QUEUE_H
#define QUEUE_H

//Filas são estruturas de dados alocadas dinamicamente na qual 
//sempre que adiciono um elemento ele passa a ser o último da fila
//(ordem de chegada) e caso deseja remover um elemento, removerei 
//o primeiro que foi adicionado e assim por diante

void *createQueue();
// Cria uma fila vazia

bool enfila(void *q, int n);
//crio uma nov celula e adiciona elemento n a fila

bool isEmpty(void *q);
//verifica se a fila está vazia

int desenfila(void *q);
//removo o elemento

void printFila(void *q); 

#endif