#include "libs.h"
#include "red_black_tree.h"

int main () {
    Tree t = newTree();

    int a[7] = {47, 8, 12, 3, 5, 9, 10};
    for (int i = 0; i < 7; i++) {
        insertTree(t, a[i]);
    }

    printf("\n");
    traversePreOrder(t, print, NULL);
    printf("\n");
    levelOrder(t, print, NULL);

    freeTree(t);

    return 0;
}