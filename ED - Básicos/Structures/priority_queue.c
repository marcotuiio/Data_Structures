#include "priority_queue.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (n == 1) {
        printf("Single element in the heap");
    
    } else { // find the largest among root, left child and right child
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest]) {
            largest = l;
        }
        if (r < n && arr[r] > arr[largest]) {
            largest = r;
        }
        // swap and continue heapifying if root is not largest
        if (largest != i) {
            swap(&arr[i], &arr[largest]);
            heapify(arr, n, largest);
        }
    }
}

void insert(int *arr, int newNum, int *n) {
    if (*n == 0) {
        arr[0] = newNum;
        *n = *n + 1;
    } else {
        arr[*n] = newNum;
        *n = *n + 1;
        for (int i = *n / 2 - 1; i >= 0; i--) {
            heapify(arr, *n, i);
        }
    }
}

void deleteRoot(int *arr, int num, int *n) {
    int i;
    for (i = 0; i < *n; i++) {
        if (num == arr[i]) {
            break;
        }
    }

    swap(&arr[i], &arr[*n - 1]);
    *n = *n - 1;
    for (int i = *n / 2 - 1; i >= 0; i--) {
        heapify(arr, *n, i);
    }
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}