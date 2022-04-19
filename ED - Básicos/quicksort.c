#include <stdio.h>

void swap (int *a, int *b);
int partition (int arr[], int low, int high);
void quicksort (int arr[], int low, int high);
void printarr(int arr[], int size);

void main () {
    int array[] = {13, 99, 10, 13, 1, 4, 8, 44, 51, 69, 3, 21};
    int n = sizeof(array) / sizeof(array[0]);
    quicksort(array, 0, n-1);
    printf("\nSorted array: \n");
    printarr(array, n);
}

void swap (int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Posiciona o pivot na posição correta, ou seja, pega o ultimo elemento
// e o coloca em uma posição ordenada de modo que todos as sua esquerda 
// sejam menores e todos a sua direita sejam maiores
int partition (int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return (i + 1);
}

// arr => vetor a ser ordenado
// low => index do começo
// high => index do final
void quicksort (int arr[], int low, int high){
    if (low < high) {
        int partIndex = partition(arr, low, high);

        // RECURSIVIDADE
        quicksort(arr, low, partIndex-1);   
        quicksort(arr, partIndex+1, high);
    }
}

void printarr(int arr[], int size){
    int i;
    for (i = 0; i < size; i++){
        printf("- %d ", arr[i]);
    }
    printf("-");
}