#include "tree.h"

struct nd {
    Info value;
    struct nd *left;
    struct nd *right;
    struct nd *center;
    struct nd *prev;
    double x, y;
    bool removed;
};
typedef struct nd tree_node;

struct rt {
    tree_node *root;
    int num_remov;
};
typedef struct rt tree_root;

Tree createTree() {
    tree_root *new_tree = calloc(1, sizeof(tree_root));
    new_tree->root = NULL;
    new_tree->num_remov = 0;

    return new_tree;
}

Node createNode(Info value, double x, double y) {
    tree_node *new_node = calloc(1, sizeof(tree_node));
    if (new_node != NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->center = NULL;
        new_node->prev = NULL;
        new_node->value = value;
        new_node->x = x;
        new_node->y = y;
        new_node->removed = false;
    }
    return new_node;
}

void insert(Tree root, Node *node, double x, double y, Info i) {
    tree_root *my_root = root;
    tree_node *my_node = *node;

    // Caso base: árvore vazia
    if (my_node->value == NULL) {
        my_node = createNode(i, x, y);
        if(my_root->root == NULL) {
            my_root->root = my_node;
        }
        return;
    }

    // Caso base 2: tentando inserir o mesmo elemento
    if (my_node->x == x && my_node->y == y) {
        return;
    }

    // Se o x é menor que o x da raiz,
    // inserir a esquerda
    if (x < my_node->x) {
        return insert(root, &(my_node->left), x, y, i);

        // Se o x é maior igual que o do nó porém o y é menor,
        // inserir no meio
    } else if (x >= my_node->x && y < my_node->y) {
        return insert(root, &(my_node->center), x, y, i);

        // Se o x é maior igual que o do nó e o y também é maior igual que o do nó,
        // inserir a direita
    } else if (x >= my_node->x && y >= my_node->y) {
        return insert(root, &(my_node->right), x, y, i);
    }
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
}

bool removeNode(Node node) {
    tree_node *toRemove = node;

    if (searchTree(toRemove, getXT(toRemove), getYT(toRemove)) == NULL) {
        printf("ELEMENTO INEXISTENTE\n");
    }

    if (toRemove->center && toRemove->left && toRemove->right) {
        if (toRemove->prev->center == toRemove) {
            toRemove->prev->center == NULL;

        } else if (toRemove->prev->left == NULL) {
            toRemove->prev->left == NULL;

        } else if (toRemove->prev->right == NULL) {
            toRemove->prev->right == NULL;
        }
        free(toRemove);
        return true;

    } else {
        marcaRemovido(toRemove);
    }
}

void marcaRemovido(Node node) {
    tree_node *toRemove = node;
    
    toRemove->removed = true;
}

void printTree(Tree root) {
    tree_root *aux_root = root;
    tree_node *my_root = aux_root->root;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    printf("value = %d\n", my_root->value);
    printf("\nleft -- ");
    printTree(my_root->left);
    printf("\nright -- ");
    printTree(my_root->right);
    printf("\ncenter -- ");
    printTree(my_root->center);
    printf("\ndone\n");
}

void percursoProfundidadeAux(Node root, char *buffer, int depth) {
    tree_node *my_root = root;

    if (my_root) {
        // Percorrendo a sub-arvore da esquerda
        percursoProfundidadeAux(my_root->left, buffer, depth);

        buffer[depth] = getXT(my_root);
        if (getCenter(my_root) == NULL && getRight(my_root) == NULL && getLeft(my_root) == NULL) {
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

void freeTree(Tree root) {
    tree_root *aux_root = root;
    tree_node *my_root = aux_root->root;

    if (my_root == NULL) {
        printf("TREE HAS BEEN FREED\n");
        return;
    }

    free(my_root->value);
    freeTree(my_root->left);
    freeTree(my_root->right);
    freeTree(my_root->center);
    free(my_root);
    free(aux_root);
}
