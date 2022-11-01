#include "Rb_tree.h"
#include "infos.h"

struct node {
    InfoRb value;
    struct node *left;
    struct node *right;
    double x, y;
    int height;
};
typedef struct node Rb_Node;

struct tree {
    Rb_Node *root;
    int size;
};
typedef struct tree Rb_Root;

// Funções auxiliares para Rb

RbNode insertTree(Rb t, RbNode n, InfoRb i, double x, double y);
RbNode newNodeRb(InfoRb i, double x, double y);
int height(RbNode n);
int max(int a, int b);
int getBalance(RbNode n);
RbNode rotateLeft(RbNode y);
RbNode rotateRight(RbNode y);
RbNode getLargestLeft(RbNode n);
RbNode getSmallestRight(RbNode n);
RbNode searchNode(RbNode n, double x, double epsilon);
void traverseAux(RbNode root, ToDoNode f, void *aux);
void freeAux(RbNode root);

// FIM

Rb createRb() {
    Rb_Root *new_tree = calloc(1, sizeof(Rb_Root));
    new_tree->root = NULL;
    new_tree->size = 0;

    return new_tree;
}

RbNode newNodeRb(InfoRb i, double x, double y) {
    Rb_Node *new_node = calloc(1, sizeof(Rb_Node));
    new_node->value = i;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    new_node->x = x;
    new_node->y = y;

    return new_node;
}

void insertRb(Rb t, InfoRb i, double x, double y) {
    Rb_Root *Rb_tree = t;
    insertTree(Rb_tree, Rb_tree->root, i, x, y);
}

RbNode insertTree(Rb t, RbNode n, InfoRb i, double x, double y) {
    Rb_Root *Rb_tree = t;
    Rb_Node *new_node = n;

    if (!new_node) {
        new_node = newNodeRb(i, x, y);
        if (!Rb_tree->root) {
            Rb_tree->root = new_node;
        }
        if (new_node) {
            Rb_tree->size++;
            return new_node;
        }
    }

    if (x < new_node->x ) { // menores a esquerda
        new_node->left = insertTree(Rb_tree, new_node->left, i, x, y);

    } else if (x > new_node->x) { // maiores a direita
        new_node->right = insertTree(Rb_tree, new_node->right, i, x, y);
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

int height(RbNode n) {
    Rb_Node *Rb_node = n;
    if (!Rb_node) {
        return 0;
    }
    return max(height(Rb_node->left), height(Rb_node->right)) + 1;
}

int max(int a, int b) {
    return (a > b) ? a : b;  // se a > b, retorna a, senão retorna b
}

int getBalance(RbNode n) {
    Rb_Node *node = n;
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

RbNode rotateLeft(RbNode n) {
    Rb_Node *node = n; // a; 
    Rb_Node *aux1 = node->right; // b; 
    Rb_Node *aux2 = aux1->left; // null; 

    aux1->left = node; // esquerda de b é a; 
    node->right = aux2; // direita de a é null
    // note que o filho direiro de b continua o mesmo que antes de rotacionar;
    // observar imagens para compreender melhor:  
    // www.tutorialspoint.com/data_structures_algorithms/Rb_tree_algorithm.htm#:~:text=A%20left%20rotation%20is%20performed,The%20tree%20is%20now%20balanced.

    node->height = height(node);
    aux1->height = height(aux1);

    return aux1;
}

RbNode rotateRight(RbNode n) {
    Rb_Node *node = n; // c
    Rb_Node *aux1 = node->left; // b
    Rb_Node *aux2 = aux1->right; // null

    aux1->right = node; // direita de b é c
    node->left = aux2; // esquerda de c é null
    // note que o filho esquerdo de b continua o mesmo que antes de rotacionar;
    // observar imagens para compreender melhor:  
    // www.tutorialspoint.com/data_structures_algorithms/Rb_tree_algorithm.htm#:~:text=A%20left%20rotation%20is%20performed,The%20tree%20is%20now%20balanced.

    node->height = height(node);
    aux1->height = height(aux1);
    
    return aux1;
}

RbNode removeTree(Rb t, RbNode n, double x) {
    Rb_Root *Rb_tree = t;
    Rb_Node *Rb_node = n;

    if (!Rb_node) {
        return Rb_node;
    }

    if (x < Rb_node->x) {
        Rb_node->left = removeTree(Rb_tree, Rb_node->left, x);

    } else if (x > Rb_node->x) {
        Rb_node->right = removeTree(Rb_tree, Rb_node->right, x);

    } else if (x == Rb_node->x) {
        Rb_Node *aux = NULL;
        if (!Rb_node->left && !Rb_node->right) {
            free(Rb_node->value);
            free(Rb_node);
            Rb_tree->size--;
            return NULL;

        } else if (!Rb_node->left) {  // somente direita
            aux = Rb_node->right;
            free(Rb_node->value);
            free(Rb_node);
            Rb_tree->size--;
            return aux;

        } else if (!Rb_node->right) {  // somente esquerda
            aux = Rb_node->left;
            free(Rb_node->value);
            free(Rb_node);
            Rb_tree->size--;
            return aux;
        
        } else if (Rb_node->left && Rb_node->right) {  // tem dois filhos
            aux = getLargestLeft(Rb_node->left);
            Rb_node->value = aux->value;
            Rb_node->x = aux->x;
            Rb_node->left = removeTree(Rb_tree, Rb_node->left, aux->x);
        }
    }
    
    Rb_node->height = height(Rb_node);

    int balance = getBalance(Rb_node);

    if (balance > 1 && x < Rb_node->left->x) {
        return rotateRight(Rb_node);
    }

    if (balance < -1 && x > Rb_node->right->x) {
        return rotateLeft(Rb_node);
    }

    if (balance > 1 && x > Rb_node->left->x) {
        Rb_node->left = rotateLeft(Rb_node->left);
        return rotateRight(Rb_node);
    }

    if (balance < -1 && x < Rb_node->right->x) {
        Rb_node->right = rotateRight(Rb_node->right);
        return rotateLeft(Rb_node);
    }

    return Rb_node;
}

RbNode getLargestLeft(RbNode n) {
    Rb_Node *node = n;
    while (node->right) {
        node = node->right;
    }
    return node;
}

RbNode getSmallestRight(RbNode n) {
    Rb_Node *node = n;
    while (node->left) {
        node = node->left;
    }
    return node;
}

RbNode getNodeRb(Rb t, double x, double epsilon) {
    Rb_Root *Rb_tree = t;
    RbNode my_node = searchNode(Rb_tree->root, x, epsilon);
    return (my_node);
}

RbNode searchNode(RbNode n, double x, double epsilon) {
    Rb_Node *node = n;
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

void traversePreOrder(Rb t, ToDoNode f, void *aux) {
    Rb_Root *Rb_tree = t;
    traverseAux(Rb_tree->root, f, aux);
}

void traverseAux(RbNode root, ToDoNode f, void *aux) {
    Rb_Node *node = root;
    if (!node) {
        return;
    }

    f(node->value, aux);
    traverseAux(node->left, f, aux);
    traverseAux(node->right, f, aux);
}

void killTree(Rb t) {
    Rb_Root *Rb_tree = t;
    printf("Tamanho da árvore: %d\n", Rb_tree->size);
    freeAux(Rb_tree->root);
    free(Rb_tree);
}

void freeAux(RbNode root) {
    Rb_Node *Rb_node = root;

    if (!Rb_node) {
        return;
    }
    freeRbInfo(Rb_node->value);
    
    freeAux(Rb_node->left);
    freeAux(Rb_node->right);
    if (Rb_node) {
        free(Rb_node);
    }
}

