#include "libs.h"

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef void (*ToDoNode) (int i, void *aux);

Tree newTree();
Node newNode(int i);
void insertTree(Tree t, int i);
Node insertAux(Tree t, Node n, int i);
void fixTree(Tree t, Node rt, Node n);
void rotateLeft(Tree t, Node n);
void rotateRight(Tree t, Node n);
bool isBlack(Node n);
void paintBlack(Node n);
bool isRed(Node n);
void paintRed(Node n);
Node searchNode(Tree t, Node n, int i);
Node getRoot(Tree t);
void traversePreOrder(Tree t, ToDoNode f, void *aux);
void traverseAux(Node root, ToDoNode f, void *aux);
void levelOrder(Tree t, ToDoNode f, void *aux);
void levelOrderAux(Node root, ToDoNode f, int level);
int height(Node n);
void print(int i, void *aux);
void freeTree(Tree t);
void freeAux(Node n);

#endif