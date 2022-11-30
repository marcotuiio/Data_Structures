#include "priority_queue.h"

#include "infos.h"

// Priority queue using a binary heap

typedef struct PQ {
    int size;
    int maxsize;
    PQInfo *elements;
    int (*compare)(Chave, Chave);
} PQ;

typedef struct PQNode {
    PQInfo info;
    Chave chave;
    int prioridade;
} PQNode;

PQueue createPQ(int size, ComparaChavesPQ comp) {
    PQ *pq = calloc(1, sizeof(PQ));
    pq->size = 0;
    pq->maxsize = size;
    pq->elements = calloc(size, sizeof(PQNode));
    pq->compare = comp;
    return pq;
}

bool isEmptyPQ(PQueue pq) {
    PQ *p = pq;
    return p->size == 0;
}

void insertPQ(PQueue pq, Chave ch, PQInfo info, int prio) {
    PQ *p = pq;
    PQNode *node = calloc(1, sizeof(PQNode));
    node->info = info;
    node->chave = ch;
    node->prioridade = prio;
    p->elements[p->size] = node;
    p->size++;

    int i = p->size - 1;
    PQNode *aux1 = p->elements[(i - 1) / 2];                      // pai
    PQNode *aux2 = p->elements[i];                                // filho
    while (i > 0 && (aux1->prioridade - aux2->prioridade) < 0) {  // enquanto prio do pai for menor que do filho
        PQInfo aux = p->elements[i];
        p->elements[i] = p->elements[(i - 1) / 2];
        p->elements[(i - 1) / 2] = aux;
        i = (i - 1) / 2;
        aux1 = p->elements[(i - 1) / 2];
        aux2 = p->elements[i];
    }
}

Chave getChavePQ(void *n, int i) {
    PQNode *node = n;
    return node->chave;
}

bool existsPQ(PQueue pq, Chave ch) {
    PQ *p = pq;
    for (int i = 0; i < p->size; i++) {
        PQNode *node = p->elements[i];
        if (p->compare(node->chave, ch) == 1) {
            return true;
        }
    }
    return false;
}

int priorityPQ(PQueue pq, Chave ch) {
    PQ *p = pq;
    for (int i = 0; i < p->size; i++) {
        PQNode *node = p->elements[i];
        if (p->compare(node, ch) == 1) {
            return node->prioridade;
        }
    }
    return -1;
}

PQInfo removeMaximumPQ(PQueue pq) {
    PQ *p = pq;
    PQNode *node = p->elements[0];
    PQInfo info = node->info;
    p->elements[0] = p->elements[p->size - 1];
    p->size--;
    int i = 0;
    PQNode *aux1 = p->elements[i];
    PQNode *aux2 = p->elements[2 * i + 1];
    PQNode *aux3 = p->elements[2 * i + 2];
    while ((2 * i + 1 < p->size) && ((aux1->prioridade - aux2->prioridade) < 0 || (aux1->prioridade - aux3->prioridade) < 0)) {
        if (aux2->prioridade > aux3->prioridade) {
            PQInfo aux = p->elements[i];
            p->elements[i] = p->elements[2 * i + 1];
            p->elements[2 * i + 1] = aux;
            i = 2 * i + 1;
        } else {
            PQInfo aux = p->elements[i];
            p->elements[i] = p->elements[2 * i + 2];
            p->elements[2 * i + 2] = aux;
            i = 2 * i + 2;
        }
        aux1 = p->elements[i];
        aux2 = p->elements[2 * i + 1];
        aux3 = p->elements[2 * i + 2];
    }
    free(node);
    return info;
}

PQInfo getMaximumPQ(PQueue pq) {
    PQ *p = pq;
    PQNode *node = p->elements[0];
    return node->info;
}

void increasePrioPQ(PQueue pq, Chave ch, int dp) {
    PQ *p = pq;
    for (int i = 0; i < p->size; i++) {
        PQNode *node = p->elements[i];
        if (p->compare(node->chave, ch) == 1) {
            node->prioridade += dp;
            int j = i;
            PQNode *aux1 = p->elements[(j - 1) / 2];
            PQNode *aux2 = p->elements[j];
            while (j > 0 && (aux1->prioridade - aux2->prioridade) < 0) {
                PQInfo aux = p->elements[j];
                p->elements[j] = p->elements[(j - 1) / 2];
                p->elements[(j - 1) / 2] = aux;
                j = (j - 1) / 2;
                aux1 = p->elements[(j - 1) / 2];
                aux2 = p->elements[j];
            }
        }
    }
}

void setPrioPQ(PQueue pq, Chave ch, int prio) {
    PQ *p = pq;
    for (int i = 0; i < p->size; i++) {
        PQNode *node = p->elements[i];
        if (p->compare(node->chave, ch) == 1) {
            node->prioridade = prio;
            int j = i;
            PQNode *aux1 = p->elements[(j - 1) / 2];
            PQNode *aux2 = p->elements[j];
            while (j > 0 && (aux1->prioridade - aux2->prioridade) < 0) {
                PQInfo aux = p->elements[j];
                p->elements[j] = p->elements[(j - 1) / 2];
                p->elements[(j - 1) / 2] = aux;
                j = (j - 1) / 2;
                aux1 = p->elements[(j - 1) / 2];
                aux2 = p->elements[j];
            }
        }
    }
}

void killPQ(PQueue pq) {
    PQ *p = pq;
    for (int i = 0; i < p->size; i++) {
        free(p->elements[i]);
    }
    free(p->elements);
    free(p);
}