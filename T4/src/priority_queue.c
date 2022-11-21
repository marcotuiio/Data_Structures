#include "priority_queue.h"
#include "infos.h"

typedef struct QueueNode {
    PQInfo data;
    Chave key;
    struct QueueNode *next;
    int priority;
} QueueNode;

typedef struct PriorityQueue {
    QueueNode* head;
    QueueNode* tail;
    int size;
    int (*compare)(void*, void*);
} PriorityQueue;

PQueue createPQ(int size, ComparaChavesPQ comp) {
    PriorityQueue* new_pq = calloc(1, sizeof(PriorityQueue));
    new_pq->size = size;
    new_pq->compare = comp;
    return new_pq;
}

bool isEmptyPQ(PQueue pq) {
    PriorityQueue* my_pq = pq;
    return !my_pq->head; // se a cabeça for nula, a fila está vazia retorna TRUE
}

void insertPQ(PQueue pq, Chave ch, PQInfo info, int prio) {
    if (existsPQ(pq, ch)) {
        return;  // se a chave já existe, não insere
    }
    PriorityQueue *my_pq = pq;
    QueueNode *new_node = calloc(1, sizeof(QueueNode));
    new_node->data = info;
    new_node->key = ch;
    new_node->priority = prio;

    if (isEmptyPQ(my_pq)) {
        // se a fila estiver vazia, cabeça e cauda apontam para o novo nó
        my_pq->head = new_node;
        my_pq->tail = new_node;
        return;
    
    } else {
        my_pq->tail->next = new_node;
        my_pq->tail = new_node;

        QueueNode *aux = my_pq->head;
        if (aux->priority < new_node->priority) {  // prioridade da cabeça é menor que a do novo nó 
            my_pq->head = new_node;  // novo nó passa a ser a cabeça
            new_node->next = aux;  // o antigo nó passa a ser o próximo do novo nó
            return;
        }

        // senão, percorrer a fila comparando quem tem maior prioridade até achar a posição correta
        while (aux->next && aux->next->priority >= new_node->priority) {
            aux = aux->next;
        }
        // encontrou posição com prioridade de acordo
        if (aux->next) { // se não for o último nó
            new_node->next = aux->next; // o próximo do novo nó é o próximo do aux
        }
        aux->next = new_node; // o próximo do aux é o novo nó
    }
}

bool existsPQ(PQueue pq, Chave ch) {
    PriorityQueue *my_pq = pq;
    QueueNode *aux = my_pq->head;
    while (aux) {
        if (my_pq->compare(aux->key, ch) == 1) {  // se a chave do nó for igual a chave procurada
            return true;  // retorna true se a chave já existe
        }
        aux = aux->next;
    }
    return false;
}

int priorityPQ(PQueue pq, Chave ch) {
    PriorityQueue *my_pq = pq;
    QueueNode *aux = my_pq->head;
    while (aux) {
        if (my_pq->compare(aux->key, ch) == 1) {  // se a chave do nó for igual a chave procurada
            return aux->priority;  // retorna a prioridade
        }
        aux = aux->next;
    }
    return -1;
}

PQInfo removeMaximumPQ(PQueue pq) {
    if (isEmptyPQ(pq)) {
        return NULL;  // se a fila estiver vazia, retorna NULL
    }
    PriorityQueue *my_pq = pq;
    QueueNode *aux = my_pq->head;
    PQInfo info = aux->data;
    aux = my_pq->head->next;
    free(aux);
    // printf("Removido: %d\n", *(Node *)info);
    return info;
}

PQInfo getMaximumPQ(PQueue pq) {
    PriorityQueue *my_pq = pq;
    return my_pq->head->data;
}

void fixQueuePrio(PQueue pq) {
    PriorityQueue *my_pq = pq;
    QueueNode *aux = my_pq->head;
    QueueNode *aux2 = aux->next;
    while (aux2) {
        if (aux->priority < aux2->priority) {  // se a prioridade do nó for menor que a do próximo nó
            aux->next = aux2->next;  // o próximo do nó é o próximo do próximo nó
            aux2->next = my_pq->head;  // o próximo do nó com prioridade maior é a cabeça
            my_pq->head = aux2;  // o nó com prioridade maior passa a ser a cabeça
            aux2 = aux->next;  // o aux2 passa a ser o próximo do aux
        } else {
            aux = aux->next;  // se a prioridade do nó for maior que a do próximo nó, o aux passa a ser o próximo nó
            aux2 = aux2->next;  // o aux2 passa a ser o próximo do aux
        }
    }
}

void increasePrioPQ(PQueue pq, Chave ch, int dp) {
    PriorityQueue *my_pq = pq;
    QueueNode *aux = my_pq->head;
    while (aux) {  
        if (my_pq->compare(aux->key, ch) == 1) {  // se a chave do nó for igual a chave procurada
            aux->priority += dp;  // aumenta a prioridade
            return;
        }
        aux = aux->next;
    }
    fixQueuePrio(my_pq);  // como alterou prioridade, arrumar a fila
}

void setPrioPQ(PQueue pq, Chave ch, int prio) {
    PriorityQueue *my_pq = pq;
    QueueNode *aux = my_pq->head;
    while (aux) {  
        if (my_pq->compare(aux->key, ch) == 1) {  // se a chave do nó for igual a chave procurada
            aux->priority = prio;  // altera a prioridade
            return;
        }
        aux = aux->next;
    }
    fixQueuePrio(my_pq);  // como alterou prioridade, arrumar a fila
}