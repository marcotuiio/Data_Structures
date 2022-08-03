#include "libs.h"

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef void (*ToDoNode) (int i, void *aux);
/*
    Processa a informacao i associada a um nó da arvore, cuja ancora
    é o ponto (x,y). O parâmetro aux aponta para conjunto de dados 
    (provavelmente um registro) que sao compartilhados entre as 
    sucessivas invocacoes a esta funcao.
*/

Tree newTree();
// Cria uma árvore vazia e retorna um ponteiro para ela

Node newNode(int i);
// Insere a informação i, associada à âncora (x,y) na árvore t.
// Retorna um indicador do nó inserido.

Node insertTree(Tree t, Node n, int i);

int height(Node n);
// Recebe um nó e retorna a altura desse nó

double max(int a, int b);
// Recebe dois valores e retorna o maior deles

int getBalance(Node n);
// Recebe um nó e retorna o valor da diferença entre a altura dos filhos

Node rotateLeft(Node n);
// Recebe um nó e rotaciona o nó para a esquerda

Node rotateRight(Node n);
// Recebe um nó e rotaciona o nó para a direita

void traversePreOrder(Tree t, ToDoNode f, void *aux);
// Recebe uma árvore, uma função f definida previamente e um ponteiro auxiliar.

void traverseAux(Node root, ToDoNode f, void *aux);
// Percorre recurssivamente no percurso pré-ordem a árvore e realizada a função
// f para cada nó da árvore.

void print(int i, void *aux);

Node getRoot(Tree t);

void printSize(Tree t);

#endif