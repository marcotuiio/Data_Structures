#include "libs.h"
#include "red_black_tree.h"

int main () {
    Tree t = newTree();

    int a[17] = {20, 12, 23, 3, 5, 99, 10, 90, 1, 100, 81, 8, 2, 1, 4, 95, 104};
    for (int i = 0; i < 17; i++) {
        insertTree(t, a[i]);
    }

    printf("\n");
    traversePreOrder(t, print, NULL);
    printf("\n");
    levelOrder(t);

    // printf("\t\nREMOVIDO\n");
    // removeTree(t, getRoot(t), 8);
    // levelOrder(t);

    freeTree(t);

    return 0;
}