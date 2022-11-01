#include "avl_tree.h"

struct node {
    InfoAvl value;
    struct node *left;
    struct node *right;
    double x, y;
    int height;
};
typedef struct node Avl_Node;

struct tree {
    Avl_Node *root;
    int size;
};
typedef struct tree Avl_Root;

// Funções auxiliares para AVL

AvlNode insertTree(Avl t, AvlNode n, InfoAvl i, double x, double y);
AvlNode newNodeAvl(InfoAvl i, double x, double y);
int height(AvlNode n);
int max(int a, int b);
int getBalance(AvlNode n);
AvlNode rotateLeft(AvlNode y);
AvlNode rotateRight(AvlNode y);
AvlNode getLargestLeft(AvlNode n);
AvlNode getSmallestRight(AvlNode n);
AvlNode searchNode(AvlNode n, double x, double epsilon);
void traverseAux(AvlNode root, ToDoNode f, void *aux);
void freeAux(AvlNode root);

// FIM

Avl createAvl() {
    Avl_Root *new_tree = calloc(1, sizeof(Avl_Root));
    new_tree->root = NULL;
    new_tree->size = 0;

    return new_tree;
}

AvlNode newNodeAvl(InfoAvl i, double x, double y) {
    Avl_Node *new_node = calloc(1, sizeof(Avl_Node));
    new_node->value = i;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    new_node->x = x;
    new_node->y = y;

    return new_node;
}

void insertAVL(Avl t, InfoAvl i, double x, double y) {
    Avl_Root *avl_tree = t;
    insertTree(avl_tree, avl_tree->root, i, x, y);
}

AvlNode insertTree(Avl t, AvlNode n, InfoAvl i, double x, double y) {
    Avl_Root *avl_tree = t;
    Avl_Node *new_node = n;

    if (!new_node) {
        new_node = newNodeAvl(i, x, y);
        if (!avl_tree->root) {
            avl_tree->root = new_node;
        }
        if (new_node) {
            avl_tree->size++;
            return new_node;
        }
    }

    if (x < new_node->x) { // menores a esquerda
        new_node->left = insertTree(avl_tree, new_node->left, i, x, y);

    } else if (x > new_node->x) { // maiores a direita
        new_node->right = insertTree(avl_tree, new_node->right, i, x, y);

    } else { // repetidos não são inseridos
        return new_node;
    }

    new_node->height = max(height(new_node->left), height(new_node->right)) + 1;

    int balance = getBalance(new_node);

    if (balance > 1 && x < new_node->left->x) { // desbalanceada para a esquerda
        return rotateRight(new_node); 
    }

    if (balance < -1 && x > new_node->right->x) { // desbalanceada para a direita
        return rotateLeft(new_node);
    }

    if (balance > 1 && x > new_node->left->x) { // desbalanceada para a esquerda e a direita
        new_node->left = rotateLeft(new_node->left);
        return rotateRight(new_node);
    }

    if (balance < -1 && x < new_node->right->x) { // desbalanceada para a direita e a esquerda
        new_node->right = rotateRight(new_node->right);
        return rotateLeft(new_node);
    }

    return new_node;
}

int height(AvlNode n) {
    Avl_Node *avl_node = n;
    if (!avl_node) {
        return 0;
    }
    return max(height(avl_node->left), height(avl_node->right)) + 1;
}

int max(int a, int b) {
    return (a > b) ? a : b;  // se a > b, retorna a, senão retorna b
}

int getBalance(AvlNode n) {
    Avl_Node *node = n;
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AvlNode rotateLeft(AvlNode n) {
    Avl_Node *node = n; // a; 
    Avl_Node *aux1 = node->right; // b; 
    Avl_Node *aux2 = aux1->left; // null; 

    aux1->left = node; // esquerda de b é a; 
    node->right = aux2; // direita de a é null
    // note que o filho direiro de b continua o mesmo que antes de rotacionar;
    // observar imagens para compreender melhor:  
    // www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm#:~:text=A%20left%20rotation%20is%20performed,The%20tree%20is%20now%20balanced.

    node->height = height(node);
    aux1->height = height(aux1);

    return aux1;
}

AvlNode rotateRight(AvlNode n) {
    Avl_Node *node = n; // c
    Avl_Node *aux1 = node->left; // b
    Avl_Node *aux2 = aux1->right; // null

    aux1->right = node; // direita de b é c
    node->left = aux2; // esquerda de c é null
    // note que o filho esquerdo de b continua o mesmo que antes de rotacionar;
    // observar imagens para compreender melhor:  
    // www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm#:~:text=A%20left%20rotation%20is%20performed,The%20tree%20is%20now%20balanced.

    node->height = height(node);
    aux1->height = height(aux1);
    
    return aux1;
}

AvlNode removeTree(Avl t, AvlNode n, double x) {
    Avl_Root *avl_tree = t;
    Avl_Node *avl_node = n;

    if (!avl_node) {
        return avl_node;
    }

    if (x < avl_node->x) {
        avl_node->left = removeTree(avl_tree, avl_node->left, x);

    } else if (x > avl_node->x) {
        avl_node->right = removeTree(avl_tree, avl_node->right, x);

    } else if (x == avl_node->x) {
        Avl_Node *aux = NULL;
        if (!avl_node->left && !avl_node->right) {
            free(avl_node->value);
            free(avl_node);
            avl_tree->size--;
            return NULL;

        } else if (!avl_node->left) {  // somente direita
            aux = avl_node->right;
            free(avl_node->value);
            free(avl_node);
            avl_tree->size--;
            return aux;

        } else if (!avl_node->right) {  // somente esquerda
            aux = avl_node->left;
            free(avl_node->value);
            free(avl_node);
            avl_tree->size--;
            return aux;
        
        } else if (avl_node->left && avl_node->right) {  // tem dois filhos
            aux = getLargestLeft(avl_node->left);
            avl_node->value = aux->value;
            avl_node->x = aux->x;
            avl_node->left = removeTree(avl_tree, avl_node->left, aux->x);
        }
    }
    
    avl_node->height = height(avl_node);

    int balance = getBalance(avl_node);

    if (balance > 1 && x < avl_node->left->x) {
        return rotateRight(avl_node);
    }

    if (balance < -1 && x > avl_node->right->x) {
        return rotateLeft(avl_node);
    }

    if (balance > 1 && x > avl_node->left->x) {
        avl_node->left = rotateLeft(avl_node->left);
        return rotateRight(avl_node);
    }

    if (balance < -1 && x < avl_node->right->x) {
        avl_node->right = rotateRight(avl_node->right);
        return rotateLeft(avl_node);
    }

    return avl_node;
}

AvlNode getLargestLeft(AvlNode n) {
    Avl_Node *node = n;
    while (node->right) {
        node = node->right;
    }
    return node;
}

AvlNode getSmallestRight(AvlNode n) {
    Avl_Node *node = n;
    while (node->left) {
        node = node->left;
    }
    return node;
}

AvlNode getNodeAvl(Avl t, double x, double epsilon) {
    Avl_Root *avl_tree = t;
    AvlNode my_node = searchNode(avl_tree->root, x, epsilon);
    return (my_node);
}

AvlNode searchNode(AvlNode n, double x, double epsilon) {
    Avl_Node *node = n;
    if (!node) {
        return NULL;
    } 
    if (fabs(node->x - x) <= epsilon) {
        return node;
    } 
    
    if (x < node->x) {
        return searchNode(node->left, x, epsilon);
    } else if (x > node->x) {
        return searchNode(node->right, x, epsilon);
    } 
    return NULL;
}

void traversePreOrder(Avl t, ToDoNode f, void *aux) {
    Avl_Root *avl_tree = t;
    traverseAux(avl_tree->root, f, aux);
}

void traverseAux(AvlNode root, ToDoNode f, void *aux) {
    Avl_Node *node = root;
    if (!node) {
        return;
    }

    f(node->value, aux);
    traverseAux(node->left, f, aux);
    traverseAux(node->right, f, aux);
}

void killTree(Avl t) {
    Avl_Root *avl_tree = t;
    freeAux(avl_tree->root);
    free(avl_tree);
}

void freeAux(AvlNode root) {
    Avl_Node *avl_node = root;

    if (!avl_node) {
        return;
    }
    free(avl_node->value);
    
    freeAux(avl_node->left);
    freeAux(avl_node->right);
    if (avl_node) {
        free(avl_node);
    }
}

