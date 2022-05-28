#include "tree.h"

#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "text.h"

struct nd {
    Info value;
    struct nd *left;
    struct nd *right;
    struct nd *center;
    double x, y;
    int crtl;
    bool removed;
};
typedef struct nd tree_node;

struct rt {
    tree_node *root;
    int size;
    int qntdRemoved;
    double LIMIAR;
};
typedef struct rt tree_root;

Tree createTree() {
    tree_root *new_tree = calloc(1, sizeof(tree_root));
    new_tree->root = NULL;
    new_tree->size = 0;
    new_tree->qntdRemoved = 0;
    new_tree->LIMIAR = 0.33;

    return new_tree;
}

Node createNode(Info value, double x, double y, int ctrl) {
    // printf("Creating new node\n");
    tree_node *new_node = calloc(1, sizeof(tree_node));
    if (new_node != NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->center = NULL;
        new_node->value = value;
        new_node->x = x;
        new_node->y = y;
        new_node->crtl = ctrl;
        new_node->removed = false;
    }
    return new_node;
}

Node insertTree(Tree root, Node node, double x, double y, Info i, int ctrl) {
    // printf("Insertion\n");
    tree_root *my_root = root;
    tree_node *my_node = node;

    // Caso base: árvore vazia
    if (my_node == NULL) {
        my_node = createNode(i, x, y, ctrl);
        if (my_root->root == NULL) {
            my_root->root = my_node;
        }
        if (my_node) {
            my_root->size++;
            // printf("size %d\n", my_root->size);
            return my_node;
        }
    }

    // Se o x é menor que o x da raiz,
    // inserir a esquerda
    if (x < (my_node->x)) {
        my_node->left = insertTree(root, my_node->left, x, y, i, ctrl);

        // Se o x é maior igual que o do nó porém o y é menor,
        // inserir no meio
    } else if (x >= (my_node->x) && y < (my_node->y)) {
        my_node->center = insertTree(root, my_node->center, x, y, i, ctrl);

        // Se o x é maior igual que o do nó e o y também é maior igual que o do nó,
        // inserir a direita
    } else if (x >= (my_node->x) && y >= (my_node->y)) {
        my_node->right = insertTree(root, my_node->right, x, y, i, ctrl);
    }
    return my_node;
}

Node getLeft(Node root) {
    tree_node *my_node = root;

    return my_node->left;
}

Node getRight(Node root) {
    tree_node *my_node = root;

    return my_node->right;
}

Node getCenter(Node root) {
    tree_node *my_node = root;

    return my_node->center;
}

double getTX(Node root) {
    tree_node *my_node = root;

    return my_node->x;
}

double getTY(Node root) {
    tree_node *my_node = root;

    return my_node->y;
}

int getCtrl(Node root) {
    tree_node *my_node = root;

    return my_node->crtl;
}

Node getRoot(Tree tree) {
    tree_root *my_tree = tree;

    return my_tree->root;
}

int getSize(Tree tree) {
    tree_root *my_tree = tree;

    return my_tree->size;
}

Info getInfo(Node root) {
    tree_node *my_node = root;

    return my_node->value;
}

Info searchTree(Node root, double x, double y) {
    tree_node *my_node = root;

    if (my_node == NULL) {
        return NULL;
    }

    if (my_node->x == x && my_node->y == y) {
        return my_node->value;
    }

    if (x < my_node->x) {
        return searchTree(my_node->left, x, y);

    } else if (x >= my_node->x && y < my_node->y) {
        return searchTree(my_node->center, x, y);

    } else if (x >= my_node->x && y >= my_node->y) {
        return searchTree(my_node->right, x, y);
    }
    return (my_node->value);
}

Node removeNode(Tree root, Node node, double x, double y) {
    tree_root *my_root = root;
    tree_node *my_node = node;

    if (my_node == NULL) {
        return NULL;
    }

    if (x < my_node->x) {
        my_node->left = removeNode(my_root, my_node->left, x, y);

    } else if (x >= my_node->x && y < my_node->y) {
        my_node->center = removeNode(my_root, my_node->center, x, y);

    } else if (x >= my_node->x && y > my_node->y) {
        my_node->right = removeNode(my_root, my_node->right, x, y);

    // Chegamos no nó que queremos remover
    } else if (x == my_node->x && y == my_node->y) {

        // // Tem um filho ou é uma folha
        // if (!(my_node->left) && !(my_node->center) && (my_node->right)) { // isso
        //     if (!(my_node->left) && (my_node->center) && !(my_node->right)) { // OUUUU isso
        //         if ((my_node->left) && !(my_node->center) && !(my_node->right)) { // OUUUUUUU isso
        //             tree_node *aux = NULL;

        //             if (my_node->left) { // filho a esquerda
        //                 aux = my_node->left;

        //             } else if (my_node->center) { // filho central
        //                 aux = my_node->center;

        //             } else if (my_node->right) { // filho a direita
        //                 aux = my_node->right;
        //             }

        //             if (!aux) {  // se não tem filho, apenas remove o nó
        //                 free(my_node->value);
        //                 free(my_node);
        //                 return aux;

        //             } else if (!my_node->left && !my_node->center) { // se não tem filho a esquerda nem no meio
        //                 tree_node *aux2 = my_node->right;
        //                 free(my_node->value);
        //                 free(my_node);
        //                 return aux2;

        //             } else if (!my_node->right && !my_node->center) { // se não tem filho a direita nem no meio
        //                 tree_node *aux2 = my_node->left;
        //                 free(my_node->value);
        //                 free(my_node);
        //                 return aux2;

        //             } else if (!my_node->right && !my_node->left) { // se não tem filho a esquerda nem a direita
        //                 tree_node *aux2 = my_node->center;
        //                 free(my_node->value);
        //                 free(my_node);
        //                 return aux2;

        //             } else {
        //                 marcaRemovido(root, my_node);
        //                 printf("Removing node\n");
        //                 return my_node;
        //             }
        //         }
        //     }
        // }

        marcaRemovido(root, my_node);
        printf("Removing node\n");
    }
    return my_node;
}

bool getRemovedStatus(Node root) {
    tree_node *my_node = root;

    if (my_node->removed) {
        // printf("TRUE %p\n", my_node);
    }
    return my_node->removed;
}

void marcaRemovido(Tree root, Node node) {
    tree_root *my_root = root;
    tree_node *toRemove = node;

    if (toRemove != NULL) {
        toRemove->removed = true;
        // printf("elemento removido %p\n", toRemove);
        my_root->qntdRemoved++;
        if (calcFD(my_root)) {
            // fix tree
            printf("NEED TO FIX TREE");
        }
    }
}

bool calcFD(Tree root) {
    tree_root *my_root = root;

    double fd = my_root->qntdRemoved / my_root->size;

    if (fd >= my_root->LIMIAR) {  // precisa refazer a arvore
        return true;
    }
    return false;
}

// void fixTree(Tree root) {
//     tree_root *my_root = root;
//     tree_node *my_node = my_root->root;

//     Node valid[15];
//     int ult = -1;

//     while (my_node) {
//         if (my_node->removed) {
//             ult++;
//             valid[ult] = my_node;
//         }

//         if (my_node->left) {
//             my_node = my_node->left;
//         } else if (my_node->center) {
//             my_node = my_node->center;
//         } else if (my_node->right) {
//             my_node = my_node->right;
//         } else {
//             break;
//         }

//         if (ult >= 14) {
//             reinsert(root, valid, ult);
//             ult = -1;
//         }
//     }

//     if (ult >= 0) {
//         reinsert(root, valid, ult);
//     }
// }

// void reinsert(Tree root, Node valid[15], int ult) {
//     // Node ndMeio = no' que esta' na metade do vetor;
//     // insereXyyT(t, getX(ndMeio), getY(ndMeio), getInfo(ndMeio);
//     // Invoca recursivamente reinsere na metade esquerda de nos validos;
//     // Invoca recursivamente reinsere na metade direito do vetor
// }

void printTree(Node root) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    printf("value = %p\n", my_root->value);
    printf("\nleft -- ");
    printTree(my_root->left);
    printf("\ncenter -- ");
    printTree(my_root->center);
    printf("\nright -- ");
    printTree(my_root->right);
    printf("\ndone\n");
}

void percursoProfundidadeAux(Node root, char *buffer, int depth) {
    tree_node *my_root = root;

    if (my_root) {
        // Percorrendo a sub-arvore da esquerda
        percursoProfundidadeAux(my_root->left, buffer, depth);

        buffer[depth] = my_root->x;
        if (my_root->center == NULL && my_root->right == NULL && my_root->left == NULL) {
            buffer[depth + 1] = '\0';
            printf("%s\n", buffer);
        }

        // Percorrendo a sub-arvore central
        percursoProfundidadeAux(my_root->center, buffer, depth + 1);

        // Percorrendo a sub-arvore da direita
        percursoProfundidadeAux(my_root->right, buffer, depth);
    }
}

void percursoProfundidade(Tree root) {
    tree_root *aux_root = root;
    tree_node *my_root = aux_root->root;

    char buffer[200];
    percursoProfundidadeAux(my_root, buffer, 0);
}

void printLevelOrder(Node root) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    int maxLevel = height(my_root);
    int i;
    for (i = 1; i <= maxLevel; i++) {
        printGivenLevel(my_root, i);
    }
}

void printGivenLevel(Node root, int level) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%p ", my_root->value);
    } else if (level > 1) {
        printGivenLevel(my_root->left, level - 1);
        printGivenLevel(my_root->center, level - 1);
        printGivenLevel(my_root->right, level - 1);
    }
}

int height(Node root) {
    tree_node *my_root = root;

    if (root == NULL) {
        return 0;
    }

    int lheight = height(my_root->left);
    int rheight = height(my_root->right);

    if (lheight > rheight) {
        return (lheight + 1);
    } else {
        return (rheight + 1);
    }
}

void quicksort(double *arr, int left, int right) {
    double x, y;
    int i, j;

    i = left;
    j = right;
    x = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < x && i < right) {
            i++;
        }
        while (arr[j] > x && j > left) {
            j--;
        }
        if (i <= j) {
            y = arr[i];
            arr[i] = arr[j];
            arr[j] = y;
            i++;
            j--;
        }
    }

    if (j > left) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}

void freeTree(Node root) {
    tree_node *my_node = root;
    int ctrl;

    if (my_node == NULL) {
        return;
    }
    ctrl = getCtrl(my_node);
    if (ctrl == 1) {
        freeCirc(my_node->value);
    } else if (ctrl == 2) {
        freeRect(my_node->value);
    } else if (ctrl == 3) {
        freeLine(my_node->value);
    } else if (ctrl == 4) {
        freeTxt(my_node->value);
    }
    freeTree(my_node->left);
    freeTree(my_node->center);
    freeTree(my_node->right);
    if (my_node) {
        free(my_node);
    }
}
