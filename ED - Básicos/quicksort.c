#include <stdio.h>
#include <stdlib.h>

void quicksort (int *arr, int left, int right);
void printarr(int *arr, int size);

void main () {
    int array[] = {13, 99, 10, 13, 1, 4, 8, 44, 51, 69, 3, 21};
    int i = sizeof(array) / sizeof(array[0]);
    printf("Size = %d\n", i);
    
    printf("\nUnsorted array: \n");
    printarr(array, i);

    quicksort(array, 0, i-1);
    printf("\nSorted array: \n");
    printarr(array, i);
}

// arr => vetor a ser ordenado
// low => index do começo
// high => index do final
void quicksort (int *arr, int left, int right) {
    int i, j, x, y;

    i = left;
    j = right;
    x = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < x && i < right) {
            i++;
        }
        while (arr[j] > x && j > left) {
            j--;
        }
        if (i <= j) {
            y = arr[i];
            arr[i] = arr[j];
            arr[j] = y;
            i++;
            j--;
        }
    }

    if (j > left) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}

void printarr(int *arr, int size){
    int i;
    for (i = 0; i < size; i++){
        printf("- %d ", arr[i]);
    }
    printf("-");
}