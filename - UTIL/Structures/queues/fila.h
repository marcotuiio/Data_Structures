#ifndef FILA_H
#define FILA_H

//Filas são estruturas de dados alocadas dinamicamente na qual 
//sempre que adiciono um elemento ele passa a ser o último da fila
//(ordem de chegada) e caso deseja remover um elemento, removerei 
//o primeiro que foi adicionado e assim por diante

struct nodeF{
    int value;
    struct nodeF *next;
};
typedef struct nodeF celulaF;

struct control{
    celulaF *head;
    celulaF *tail;
};
typedef struct control fila;

void init(fila *minhafila);
//inicializa ponteiros de começo e final da fila com nulos

bool enfila(fila *minhafila, int n);
//crio uma nov celula e adiciona elemento n a fila

int desenfila(fila *minhafila);
//removo o elemento

void printFila(fila *minhafila); 

#endif