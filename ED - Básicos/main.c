#include "libs.h"
#include "avl_tree.h"

int main () {
    Tree t = newTree();
    void *aux = NULL;

    insertTree(t, getRoot(t), 10);
    insertTree(t, getRoot(t), 11);
    insertTree(t, getRoot(t), 8);
    insertTree(t, getRoot(t), 14);
    insertTree(t, getRoot(t), 7);
    insertTree(t, getRoot(t), 16);
    insertTree(t, getRoot(t), 12);
    insertTree(t, getRoot(t), 102);
    insertTree(t, getRoot(t), 105);
    insertTree(t, getRoot(t), 1);

    printf("\n");
    traversePreOrder(t, print, aux);
    printf("\n");
    removeNode(t, getRoot(t), 10);
    traversePreOrder(t, print, aux);
    printf("\n");

    freeTree(getRoot(t));
    free(t);
    
    return 0;
}