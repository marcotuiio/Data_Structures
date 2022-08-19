#include "libs.h"
#include "red_black_tree.h"

int main () {
    Tree t = newTree();

    int a[15] = {20, 12, 23, 3, 5, 9, 10, 90, 19, 100, 81, 8, 2, 1, 4};
    for (int i = 0; i < 15; i++) {
        insertTree(t, a[i]);
    }

    printf("\n");
    traversePreOrder(t, print, NULL);
    printf("\n");
    levelOrder(t);

    freeTree(t);

    return 0;
}