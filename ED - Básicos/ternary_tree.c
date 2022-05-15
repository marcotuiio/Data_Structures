#include "tree.h"

struct nd {
    Info value;
    struct nd *left;
    struct nd *right;
    struct nd *center;
    struct nd *prev;
};
typedef struct nd tree_node;

Tree createNode(Info value) {
    tree_node *new_node = calloc(1, sizeof(tree_node));
    if (new_node != NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->center = NULL;
        new_node->prev = NULL;
        new_node->value = value;
    }
    return new_node;
}

void setLeft(Tree root, Tree toLeft) {
    tree_node *my_root = root;
    tree_node *my_child = toLeft;

    my_child->prev = my_root;
    my_root->left = my_child;
}

void setRight(Tree root, Tree toRight) {
    tree_node *my_root = root;
    tree_node *my_child = toRight;

    my_child->prev = my_root;
    my_root->right = my_child;
}

void setCenter(Tree root, Tree toCenter) {
    tree_node *my_root = root;
    tree_node *my_child = toCenter;

    my_child->prev = my_root;
    my_root->center = my_child;
}

Tree getLeft(Tree root) {
    tree_node *my_node = root;

    return my_node->left;
}

Tree getRight(Tree root) {
    tree_node *my_node = root;

    return my_node->right;
}

Tree getCenter(Tree root) {
    tree_node *my_node = root;

    return my_node->center;
}

Info getInfo(Tree root) {
    tree_node *my_node = root;

    return my_node->value;
}

void removeNode(Tree node) {
    tree_node *toRemove = node;

    if (toRemove->left == NULL && toRemove->right == NULL && toRemove->center == NULL) {  // é uma folha
        if (toRemove == toRemove->prev->right) {
            toRemove->prev->right = NULL;

        } else if (toRemove == toRemove->prev->left) {
            toRemove->prev->left = NULL;

        } else if (toRemove == toRemove == toRemove->center) {
            toRemove->prev->center = NULL;
        }

    } else if (toRemove->left == NULL && toRemove->center == NULL && toRemove->right != NULL) {  // só tem o filho da direita
        if (toRemove->prev->right == toRemove) {
            toRemove->prev->right = toRemove->right;

        } else if (toRemove->prev->left == toRemove) {
            toRemove->prev->left == toRemove->right;

        } else if(toRemove == toRemove ==toRemove->center) {
            toRemove->prev->center = toRemove->right;
        }

    } else if (toRemove->left != NULL && toRemove->center == NULL && toRemove->right == NULL) {  // só tem o filho da esquerda
        if (toRemove->prev->right == toRemove) {
            toRemove->prev->right = toRemove->left;

        } else if (toRemove->prev->left == toRemove) {
            toRemove->prev->left == toRemove->left;

        } else if(toRemove == toRemove ==toRemove->center) {
            toRemove->prev->center = toRemove->left;
        }

    } else if (toRemove->left == NULL && toRemove->center != NULL && toRemove->right == NULL) {  // só tem o filho do centro
        if (toRemove->prev->right == toRemove) {
            toRemove->prev->right = toRemove->center;

        } else if (toRemove->prev->left == toRemove) {
            toRemove->prev->left == toRemove->center;

        } else if(toRemove == toRemove ==toRemove->center) {
            toRemove->prev->center = toRemove->center;
        }

    } else if (toRemove->left != NULL && toRemove->right != NULL) {  // tem os dois filhos
        tree_node *aux = getLeft(toRemove);
        tree_node *aux2 = NULL;
        printf("aux1 %d\n", getInfo(aux));
        while (aux2 != NULL) {
            aux2 = getRight(aux);
        }
        printf("aux2 %d\n", getInfo(aux));
        if (toRemove->prev->right == toRemove) {
            toRemove->prev->right = aux2;

        } else if (toRemove->prev->left == toRemove) {
            toRemove->prev->left = aux2;
        }
        aux2->right = toRemove->right;
        aux2->left = toRemove->left;
    }

    free(toRemove);
}

void printTree(Tree root) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    printf("value = %d\n", my_root->value);
    printf("\nleft -- ");
    printTree(my_root->left);
    printf("\nright -- ");
    printTree(my_root->right);
    printf("\ndone\n");
}

void freeTree(Tree root) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        printf("TREE HAS BEEN FREED\n");
        return;
    }

    printf("value = %d\n", my_root->value);
    freeTree(my_root->left);
    freeTree(my_root->right);
    free(my_root);
}
