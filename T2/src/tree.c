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
};
typedef struct rt tree_root;

Tree createTree() {
    tree_root *new_tree = calloc(1, sizeof(tree_root));
    new_tree->root = NULL;
    new_tree->size = 0;

    return new_tree;
}

Node createNode(Info value, double x, double y, int ctrl) {
    printf("Creating new node\n");
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
    printf("Insertion\n");
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
        printf("da esquerda\n");
        my_node->left = insertTree(root, my_node->left, x, y, i, ctrl);

        // Se o x é maior igual que o do nó porém o y é menor,
        // inserir no meio
    } else if (x >= (my_node->x) && y < (my_node->y)) {
        printf("do meio\n");
        my_node->center = insertTree(root, my_node->center, x, y, i, ctrl);

        // Se o x é maior igual que o do nó e o y também é maior igual que o do nó,
        // inserir a direita
    } else if (x >= (my_node->x) && y >= (my_node->y)) {
        printf("da direita\n");
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

void setInfo(Node root, Info i, double x, double y) {
    tree_node *my_node = root;
    my_node->value = i;
    my_node->x = x;
    my_node->y = y;
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

    if (searchTree(my_node, my_node->x, my_node->y) == NULL) {
        printf("ELEMENTO INEXISTENTE\n");
        return NULL;
    }

    // se o elemento a remover for a raiz, resolvo de cara
    if (my_node == my_root->root) {
        marcaRemovido(root, my_node);
        return NULL;
    }

    if (x < my_node->x) {
        my_node->left = removeNode(my_root, my_node->left, x, y);
    
    } else if (x >= my_node->x && y < my_node->y) {
        my_node->center = removeNode(my_root, my_node->center, x, y);

    } else if (x >= my_node->x && y >= my_node->y) {
        my_node->right = removeNode(my_root, my_node->right, x, y);

        // senão marca removido e organiza depois
    } else {
        // !!!!! implementar limiar e fator degradação !!!!!!
        marcaRemovido(root, node);
    }
    return my_node;
}

bool marcaRemovido(Tree root, Node node) {
    tree_root *my_root = root;
    tree_node *toRemove = node;

    if (toRemove != NULL) {
        // implementar limiar
        my_root->size--;
        toRemove->removed = true;
        return true;
    }
    return false;
}

void fixTree(Tree root) {
    tree_root *my_root = root;
    tree_node *my_node = my_root->root;

    Node valid[15];
    int ult = -1;

    while (my_node) {
        if (my_node->removed) {
            ult++;
            valid[ult] = my_node;
        }

        if (my_node->left) {
            my_node = my_node->left;
        } else if (my_node->center) {
            my_node = my_node->center;
        } else if (my_node->right) {
            my_node = my_node->right;
        } else {
            break;
        }

        if (ult >= 14) {
            reinsert(root, valid, ult);
            ult = -1;
        }
    }

    if (ult >= 0) {
        reinsert(root, valid, ult);
    }
}

void reinsert(Tree root, Node valid[15], int ult) {
    // Node ndMeio = no' que esta' na metade do vetor;
    // insereXyyT(t, getX(ndMeio), getY(ndMeio), getInfo(ndMeio);
    // Invoca recursivamente reinsere na metade esquerda de nos validos;
    // Invoca recursivamente reinsere na metade direito do vetor
}

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
    tree_node *my_root = root;
    int ctrl;

    if (my_root == NULL) {
        return;
    }
    ctrl = getCtrl(my_root);
    if (ctrl == 1) {
        freeCirc(my_root->value);
    } else if (ctrl == 2) {
        freeRect(my_root->value);
    } else if (ctrl == 3) {
        freeLine(my_root->value);
    } else if (ctrl == 4) {
        freeTxt(my_root->value);
    }
    freeTree(my_root->left);
    freeTree(my_root->center);
    freeTree(my_root->right);
}
