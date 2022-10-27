#include "queue.h"

typedef struct NodeQueue {
    InfoNode value;
    struct NodeQueue *next;
} NodeQueue;

typedef struct StQueue {
    NodeQueue *head;
    NodeQueue *tail;
} StQueue;

void *createQueue() {
    StQueue *queue = calloc(1, sizeof(StQueue));
    return queue;
}

bool enfila(Queue q, InfoNode n) {
    // crio uma nova celula
    StQueue *queue = q;
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

bool isEmpty(Queue q) {
    StQueue *queue = q;
    return !queue->head;
}

InfoNode desenfila(Queue q) {
    // conferir se a fila está ou não vazia
    StQueue *queue = q;
    if (!queue->head) {
        return NULL;
    }
    // salvo o começo da fila
    NodeQueue *tmp = queue->head;
    // salvo o valor a ser removido
    InfoNode result = tmp->value;
    // removo o valor
    queue->head = queue->head->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    free(tmp);
    return result;
}

void printFila(Queue q) {
    StQueue *queue = q;
    InfoNode info;
    printf("\n");
    while ((info = desenfila(queue))) {
        printf("info = %p\n", info);
    }
}
