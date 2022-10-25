#include "queue.h"

#define QUEUE_EMPTY INT_MIN

typedef struct NodeQueue {
    int value;
    struct NodeQueue *next;
} NodeQueue;

typedef struct Queue {
    NodeQueue *head;
    NodeQueue *tail;
} Queue;

void *createQueue() {
    Queue *queue = calloc(1, sizeof(Queue));
    return queue;
}

bool enfila(void *q, int n) {
    // crio uma nova celula
    Queue *queue = q;
    NodeQueue *novaCelula = calloc(1, sizeof(NodeQueue));
    if (!novaCelula) {
        return false;
    }
    novaCelula->value = n;
    novaCelula->next = NULL;
    // se existe um rabo, ligo esse rabo na nova celula
    if (queue->tail) {
        queue->tail->next = novaCelula;
    }
    queue->tail = novaCelula;
    // conferir se o começo da fila ainda faz sentido
    if (!queue->head) {
        queue->head = novaCelula;
    }
    return true;
}

bool isEmpty(void *q) {
    Queue *queue = q;
    return !queue->head;
}

int desenfila(void *q) {
    // conferir se a fila está ou não vazia
    Queue *queue = q;
    if (!queue->head) {
        return QUEUE_EMPTY;
    }
    // salvo o começo da fila
    NodeQueue *tmp = queue->head;
    // salvo o valor a ser removido
    int result = tmp->value;
    // removo o valor
    queue->head = queue->head->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    free(tmp);
    return result;
}

void printFila(void *q) {
    Queue *queue = q;
    int info;
    printf("\n");
    while ((info = desenfila(queue)) != QUEUE_EMPTY) {
        printf("info = %d\n", info);
    }
}
