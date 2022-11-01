#include "libs.h"

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef void (*ToDoNode) (InfoAvl i, void *aux);
/*
    Processa a informacao i associada a um nó da arvore, cuja ancora
    é o ponto (x,y). O parâmetro aux aponta para conjunto de dados 
    (provavelmente um registro) que sao compartilhados entre as 
    sucessivas invocacoes a esta funcao.
*/

Avl createAvl();
// Cria uma árvore vazia e retorna um ponteiro para ela

AvlNode newNodeAvl(InfoAvl i, double x, double y);
// Insere a informação i, associada à âncora (x,y) na árvore t.
// Retorna um indicador do nó inserido.

void insertAVL(Avl t, InfoAvl i, double x, double y);
// Insere a informação i, associada à âncora (x,y) na árvore t.

AvlNode removeTree(Avl t, AvlNode n, double i);
// Remove o nó n da árvore t.

AvlNode getNodeAvl(Avl t, double x, double epsilon);
// Recebe uma árvore e um ponto (x,y) e retorna o nó que contém o ponto.

void traversePreOrder(Avl t, ToDoNode f, void *aux);
// Recebe uma árvore, uma função f definida previamente e um ponteiro auxiliar e 
// a percorre no percurso pre-ordem.

void killTree(Avl t);
// Recebe uma árvore e libera toda a memória alocada para ela.

#endif