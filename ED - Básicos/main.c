#include "libs.h"
#include "red_black_tree.h"

int main () {
    Tree t = newTree();

    int a[17] = {20, 12, 23, 3, 5, 99, 10, 90, 1, 100, 81, 8, 2, 1, 4, 95, 104};
    for (int i = 0; i < 17; i++) {
        insertTree(t, a[i]);
    }

    // printf("\n");
    // traversePreOrder(t, print, NULL);
    // printf("\n");
    // levelOrder(t);

    printf("\n\tREMOVIDO\n");
    removeTree(t, getRoot(t), 99);
    levelOrder(t);

    // REMOVER 20 OK no raiz, preto com dois filhos pretos 
    // REMOVER 10 OK no preto com dois filhos
    // REMOVER 99 ERRO no vermelho com dois filhos
    // REMOVER 81 OK no vermelho com irmao vermelho
    // REMOVER 4 OK no vermelho folha
    // REMOVER 23 ERRO no preto com unico filho a direita
    // REMOVER 95 ERRO no preto folha (a esquerda)

    freeTree(t);

    return 0;
}