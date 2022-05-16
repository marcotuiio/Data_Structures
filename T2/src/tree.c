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

Tree createTree(Info value, double x, double y) {
    tree_node *new_tree = calloc(1, sizeof(tree_node));
    if (new_tree != NULL) {
        new_tree->left = NULL;
        new_tree->right = NULL;
        new_tree->center = NULL;
        new_tree->prev = NULL;
        new_tree->value = value;
        new_tree->x = x;
        new_tree->y = y;
        new_tree->removed = false;
    }
    return new_tree;
}

void insert(Tree node, double x, double y, Info i) {
    tree_node *my_node = node;

    // Caso base de árvore vazia
    if(my_node->value == NULL) {
        my_node = createTree(i, x, y);
    }

    // Se o x é menor que o x da raiz, 
    // inserir a esquerda
    if (x < getXT(my_node)) {
        insert(my_node->left, x, y, i);

    // Se o x é maior igual que o do nó porém o y é menor,
    // inserir no meio
    } else if (x >= getXT(my_node) && y < getYT(my_node)) {
        insert(my_node->center, x, y, i);

    // Se o x é maior igual que o do nó e o y também é maior igual que o do nó, 
    // inserir a direita
    } else if (x >= getXT(my_node) && y >= getYT(my_node)) {
        insert(my_node->right, x, y, i);
    }
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

void setInfo(Tree root, Info i, double x, double y) {
    tree_node *my_node = root;
    my_node->value = i;
    my_node->x = x;
    my_node->y = y;   
}

Info getInfo(Tree root) {
    tree_node *my_node = root;

    return my_node->value;
}

Info searchTree(Tree root, double x, double y) {
    tree_node *my_node = root;

    if (my_node == NULL) {
        return NULL;
    }

    if (x < getXT(my_node)) {
        return searchTree(my_node->left, x, y);

    } else if (x >= getXT(my_node) && y < getYT(my_node)) {
        return searchTree(my_node->center, x, y);

    } else if (x >= getXT(my_node) && y >= getYT(my_node)) {
        return searchTree(my_node->right, x, y);
    }
}

double getXT(Tree root) {
    tree_node *my_node = root;

    return my_node->x;
}

double getYT(Tree root) {
    tree_node *my_node = root;

    return my_node->y;
}

bool removeNode(Tree node) {
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
        toRemove->removed = true;
    }
    
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
    printf("\ncenter -- ");
    printTree(my_root->center);
    printf("\ndone\n");
}

void percursoProfundidadeAux(Tree root, char* buffer, int depth) {
    tree_node *my_root = root;

    if (my_root) {
        // Percorrendo a sub-arvore da esquerda
        percursoProfundidadeAux(my_root->left, buffer, depth);

        buffer[depth] = getXT(my_root);
        if(getCenter(my_root) == NULL && getRight(my_root) == NULL && getLeft(my_root) == NULL) {
            buffer[depth+1] = '\0';
            printf("%s\n", buffer);
        }

        // Percorrendo a sub-arvore central
        percursoProfundidadeAux(my_root->center, buffer, depth+1);

        // Percorrendo a sub-arvore da direita
        percursoProfundidadeAux(my_root->right, buffer, depth);
    }
}

void percursoProfundidade(Tree root) {
    char buffer[200];
    percursoProfundidadeAux(root, buffer, 0);
}

void freeTree(Tree root) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        printf("TREE HAS BEEN FREED\n");
        return;
    }

    free(my_root->value);
    freeTree(my_root->left);
    freeTree(my_root->right);
    freeTree(my_root->center);
    free(my_root);
}
