#include "libs.h"

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef void (*ToDoNode) (int i, void *aux);

Tree newTree();
// Cria uma nova árvore vazia.

Node newNode(int i);
// Cria um novo nó com o valor i.

void insertTree(Tree t, int i);
Node insertAux(Tree t, Node n, int i);
// Insere o nó com o valor i na árvore t.

void fixRBinsert(Tree t, Node rt, Node n);
// Corrige a propriedade de cores da árvore após a inserção de n.

void rotateLeft(Tree t, Node n);
// Roda o nó n para a esquerda.

void rotateRight(Tree t, Node n);
// Roda o nó n para a direita.

bool isBlack(Node n);
// Retorna true se o nó n é preto.

void paintBlack(Node n);
// Pinta o nó n preto.

bool isRed(Node n);
// Retorna true se o nó n é vermelho.

void paintRed(Node n);
// Pinta o nó n vermelho.

Node searchNode(Tree t, Node n, int i);
// Busca o nó com o valor i na árvore t.

Node removeTree(Tree t, Node n, int i);
// Remove o nó com o valor i da árvore t.

void fixRBdelete(Tree t, Node rt, Node n);
// Corrige a propriedade de cores da árvore após a remoção de n.

Node getLargestLeft(Node n);
// Retorna o maior nó na subarvore esqueda

Node getSmallestRight(Node n);
// Retorna o menor nó na subarvore direita

Node getRoot(Tree t);
// Retorna o nó raiz da árvore t.

void traversePreOrder(Tree t, ToDoNode f, void *aux);
void traverseAux(Node root, ToDoNode f, void *aux);
// Percorre a árvore t em pré-ordem e aplica a função f a cada nó.

void levelOrder(Tree t);
void levelOrderAux(Node root, int level);
int heightOfLevel(Node n);
// Percorre a árvore t em nível e imprime o nível de cada nó.

void print(int i, void *aux);

void freeTree(Tree t);
void freeAux(Node n);
// Libera a memória alocada para a árvore t.

#endif