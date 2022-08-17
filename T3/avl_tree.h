#include "libs.h"

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef void (*ToDoNode) (Info i, void *aux);
/*
    Processa a informacao i associada a um nó da arvore, cuja ancora
    é o ponto (x,y). O parâmetro aux aponta para conjunto de dados 
    (provavelmente um registro) que sao compartilhados entre as 
    sucessivas invocacoes a esta funcao.
*/

Tree newTree();
// Cria uma árvore vazia e retorna um ponteiro para ela

Node newNode(Info i, double x);
// Insere a informação i, associada à âncora (x,y) na árvore t.
// Retorna um indicador do nó inserido.

Node getRoot(Tree t);
// Retorna o nó raiz da árvore t.

Node insertTree(Tree t, Node n, Info i, double x);
// Insere a informação i, associada à âncora (x,y) na árvore t.

int height(Node n);
// Recebe um nó e retorna a altura desse nó

int max(int a, int b);
// Recebe dois valores e retorna o maior deles

int getBalance(Node n);
// Recebe um nó e retorna o valor da diferença entre a altura dos filhos

Node rotateLeft(Node n);
// Recebe um nó e rotaciona o nó para a esquerda

Node rotateRight(Node n);
// Recebe um nó e rotaciona o nó para a direita

Node removeTree(Tree t, Node n, double i);
// Remove o nó n da árvore t.

Node getLargestLeft(Node n);
// Recebe uma subarvore esquerda e retorna o maior valor associado
// a essa subarvore

Node getSmallestRight(Node n);
// Recebe uma subarvore direita e retorna o menor valor associado
// a essa subarvore

Node getNode(Tree t, double x, double epsilon);
Node searchNode(Node n, double x, double epsilon);
// Recebe uma árvore e um ponto (x,y) e retorna o nó que contém o ponto.

void traversePreOrder(Tree t, Node root, ToDoNode f, void *aux);
// Recebe uma árvore, uma função f definida previamente e um ponteiro auxiliar e 
// a percorre no percurso pre-ordem.

void freeTree(Tree t);
void freeAux(Node root);
// Recebe uma árvore e libera toda a memória alocada para ela.

#endif