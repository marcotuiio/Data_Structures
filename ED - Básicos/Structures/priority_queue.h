# include "libs.h"

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

void swap(int *a, int *b);
// realiza a troca de a com b

void heapify(int *arr, int n, int i);
// organiza o heap

void insert(int *arr, int newNum, int *n);
// insere o elelmento newNum no heap

void deleteRoot(int *arr, int num, int *n);
// deleta o elemento num do heap

void printArray(int *arr, int n);
// imprime o heap

#endif