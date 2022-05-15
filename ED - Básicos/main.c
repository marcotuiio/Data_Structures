#include "libs.h"
#include "tree.h"

void main() {
    Tree n1 = createNode(10);
    Tree n2 = createNode(11);
    Tree n3 = createNode(12);
    Tree n4 = createNode(13);
    Tree n5 = createNode(14);

    setLeft(n1, n2);
    setRight(n1, n3);
    setLeft(n3, n4);
    setRight(n3, n5);
    printf("\nfirst\n");
    printTree(n1);

    removeNode(n3);
    printf("\nafter remotion\n");
    printTree(n1);

    printf("\nfree\n");
    freeTree(n1);
}