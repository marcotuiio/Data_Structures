#include "libs.h"

#ifndef Rb_TREE_H
#define Rb_TREE_H

typedef void (*ToDoNode) (InfoRb i, void *aux);
/*
    Processa a informacao i associada a um nó da arvore, cuja ancora
    é o ponto (x,y). O parâmetro aux aponta para conjunto de dados 
    (provavelmente um registro) que sao compartilhados entre as 
    sucessivas invocacoes a esta funcao.
*/

Rb createRb();
// Cria uma árvore vazia e retorna um ponteiro para ela

RbNode newNodeRb(InfoRb i, double x, double y);
// Insere a informação i, associada à âncora (x,y) na árvore t.
// Retorna um indicador do nó inserido.

void insertRb(Rb t, InfoRb i, double x, double y);
// Insere a informação i, associada à âncora (x,y) na árvore t.

RbNode removeTree(Rb t, RbNode n, double i);
// Remove o nó n da árvore t.

RbNode getNodeRb(Rb t, double x, double epsilon);
// Recebe uma árvore e um ponto (x,y) e retorna o nó que contém o ponto.

void traversePreOrder(Rb t, ToDoNode f, void *aux);
// Recebe uma árvore, uma função f definida previamente e um ponteiro auxiliar e 
// a percorre no percurso pre-ordem.

void killTree(Rb t);
// Recebe uma árvore e libera toda a memória alocada para ela.

#endif