#include "libs.h"
#include "avl_tree.h"

int main () {
    Tree t = newTree();
    void *aux = NULL;

    insertTree(t, getRoot(t), 10);
    insertTree(t, getRoot(t), 11); //colocar um valor maior logo depois ta quebrando
    insertTree(t, getRoot(t), 8);
    insertTree(t, getRoot(t), 13);
    insertTree(t, getRoot(t), 7);
    insertTree(t, getRoot(t), 16);
    insertTree(t, getRoot(t), 102);
    insertTree(t, getRoot(t), 102);
    insertTree(t, getRoot(t), 1);

    printf("\n");
    traversePreOrder(t, print, aux);
    printf("\n");
    printSize(t);

    return 0;
    
}