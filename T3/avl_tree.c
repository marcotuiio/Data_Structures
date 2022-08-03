#include "avl_tree.h"

struct node {
    Info value;
    struct node *left;
    struct node *right;
    int height;
};
typedef struct node Avl_Node;

struct tree {
    Avl_Node *root;
};
typedef struct tree Avl_Root;

Tree newTree() {
    Avl_Root *new_tree = calloc(1, sizeof(Avl_Root));
    new_tree->root = NULL;

    return new_tree;
}

Node newNode(Info i) {
    Avl_Node *new_node = calloc(1, sizeof(Avl_Node));
    new_node->value = i;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

Node insertTree(Tree t, Node n, Info i) {
    Avl_Root *avl_tree = t;
    Avl_Node *avl_node = n;
    Avl_Node *new_node = newNode(i);
    void *x;
    if (!avl_tree->root) {
        avl_tree->root = new_node;
        return;
    }

    if (i < avl_node->value) {
        new_node->left = insertTree(avl_tree, new_node->left, i);

    } else if (i > avl_node->value) {
        new_node->right = insertTree(avl_tree, new_node->right, i);

    } else {
        return avl_node;
    }

    new_node->height = max(height(new_node->left), height(new_node->right)) + 1;

    int balance = getBalance(new_node);

    if (balance > 1 && i < new_node->left->value) {
        return rotateRight(new_node);
    }

    if (balance < -1 && i > new_node->right->value) {
        return rotateLeft(new_node);
    }

    if (balance > 1 && i > new_node->left->value) {
        new_node->left = rotateLeft(new_node->left);
        return rotateRight(new_node);
    }

    if (balance < -1 && i < new_node->right->value) {
        new_node->right = rotateRight(new_node->right);
        return rotateLeft(new_node);
    }

    return new_node;
}

int height(Node n) {
    Avl_Node *avl_node = n;
    if (!avl_node) {
        return 0;
    }
    return avl_node->height;
}

double max(double a, double b) {
    return a > b ? a : b;  // se a > b, retorna a, senão retorna b
}

int getBalance(Node n) {
    Avl_Node *node = n;
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node rotateLeft(Node n) {
    Avl_Node *node = n;
    Avl_Node *aux1 = node->right;
    Avl_Node *aux2 = aux1->left;

    aux1->left = node;
    node->right = aux2;

    node->height = max(height(node->left), height(node->right)) + 1;
    aux1->height = max(height(aux1->left), height(aux1->right)) + 1;

    return aux1;
}

Node rotateRight(Node n) {
    Avl_Node *node = n;
    Avl_Node *aux1 = node->left;
    Avl_Node *aux2 = aux1->right;

    node->right = aux1;
    aux1->left = aux2;

    node->height = max(height(node->left), height(node->right)) + 1;
    aux1->height = max(height(aux1->left), height(aux1->right)) + 1;

    return node;
}

void traversePreOrder(Tree t, ToDoNode f, void *aux) {
    Avl_Root *avl_tree = t;
    traverseAux(avl_tree->root, f, aux);
}

void traverseAux(Node root, ToDoNode f, void *aux) {
    Avl_Node *node = root;
    if (!node) {
        return;
    }

    f(node->value, aux);
    traverseAux(node->left, f, aux);
    traverseAux(node->right, f, aux);
}
