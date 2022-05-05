#include "libs.h"

#ifndef TREE_H
#define TREE_H

Tree createNode(Info value);

void setLeft(Tree root, Tree toLeft);

void setRight(Tree root, Tree toRight);

void printTree(Tree root);

#endif