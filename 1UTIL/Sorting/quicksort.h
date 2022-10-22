#ifndef QUICKSORT_H
#define QUICKSORT_H

// Método de ordenação muito eficiente, quicksort funciona
// selecionando um pivot estratégico e ordena, recursivamente, 
// a direita e a esquerda desse elemento até que todo o conjunto
// esteja devidamente organizado.
// Tem complexidade, na prática, de n(log(n)), é muito rapido
// e pode ordenar grandes sequências em pouco tempo

void quicksort (int *arr, int left, int right);
// Recebe um vetor de informações, a posição do primeiro elemento
// e a posição do ultimo elemento

void printarr(int *arr, int size);
// função básica que recebe um vetor e o tamanho do mesmo,
// exibindo seus valores

#endif