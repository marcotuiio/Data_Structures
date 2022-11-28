#include "libs.h"

#ifndef __PRIOQ_H
#define __PRIOQ_H

/*
  Uma fila de prioridades é uma coleção de itens aos quais é associada uma prioridade,
  de forma que os elementos de maior prioridade sao "servidos" antes que os de menor
  prioridade.
  A prioridade é um número inteiro de forma que, quanto maior o numero, maior a prioridade.
  O critério de desempate para itens de mesma prioridade não é definido.
  A cada item da fila é associada uma chave de busca unica, ou seja, uma fila nao
  armazena 2 itens com a mesma chave.
  As operações de inserção, remoção e busca possuem complexidade O(log n).
  Uma fila de prioridades sem itens é denominada fila de prioridades vazia.
*/

/*
  Retorna -1, se ch1 < ch2; +1, se ch1 > ch2; 0, caso contrário.
*/
typedef int (*ComparaChavesPQ)(Chave ch1, Chave ch2);

/*
  Retorna uma fila de prioridades vazia capaz de armazenar, pelo menos, "size" elementos.
  A função "comp" compara duas chaves de busca conforme descrito acima.
*/
PQueue createPQ(int size, ComparaChavesPQ comp);

/*
  Retorna verdadeiro se a fila pq está vazia.
*/
bool isEmptyPQ(PQueue pq);

/*
  Insere na fila pq a informação "info", de chave "ch" com prioridade "prio".
  A chave "ch" não deve previamente existir em pq.
*/
void insertPQ(PQueue pq, Chave ch, PQInfo info, int prio);

/*
  Retorna verdadeiro se a chave "ch" existe na fila pq.
*/
bool existsPQ(PQueue pq, Chave ch);

/*
  Retorna a prioridade da informacao armazenada em pq sob a chave "ch".
  Um item com a chave "ch" deve existir em "pq".
*/
int priorityPQ(PQueue pq, Chave ch);

/*
  Retira e retorna o elemento de maior prioridade da fila "pq".
  Retorna NULL se a fila estiver vazia.
*/
PQInfo removeMaximumPQ(PQueue pq);

/*
  Retorna (sem retirar) o elemento de maior prioridade em "pq".
  Retorna NULL, se fila estiver vazia.
*/
PQInfo getMaximumPQ(PQueue pq);

/*
  Modifica a prioridade do item de chave "ch" em "dp" unidades.
  Se dp < 0, diminui a prioridade; dp > 0, aumenta prioridade.
  Item com chave "ch" deve existir em "pq".
*/
void increasePrioPQ(PQueue pq, Chave ch, int dp);

/*
  Modifica a prioridade do item de chave "ch" para "prio".
  Se dp < 0, diminui a prioridade; dp > 0, aumenta prioridade.
  Item com chave "ch" deve existir em "pq".
*/
void setPrioPQ(PQueue pq, Chave ch, int prio);


/*
  Libera memória
*/
void killPQ(PQueue pq);

#endif