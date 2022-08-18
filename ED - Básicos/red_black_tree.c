#include "red_black_tree.h"

struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
    char color[10];
};
typedef struct node Red_Black_Node;

struct tree {
    Red_Black_Node *root;
    int size;
};
typedef struct tree Red_Black_Root;

Tree newTree() {
    Red_Black_Root *new_tree = calloc(1, sizeof(Red_Black_Root));
    new_tree->root = NULL;
    new_tree->size = 0;

    return new_tree;
}

Node newNode(int i) {
    Red_Black_Node *new_node = calloc(1, sizeof(Red_Black_Node));
    new_node->value = i;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    strcpy(new_node->color, "RED");

    return new_node;
}

void insertTree(Tree t, int i) {
    Red_Black_Root *red_black_tree = t;
    insertAux(t, red_black_tree->root, i);
    Red_Black_Node *new_node = searchNode(t, red_black_tree->root, i);
    fixTree(t, red_black_tree->root, new_node);
}

Node insertAux(Tree t, Node n, int i) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *new_node = n;

    if (!new_node) {
        new_node = newNode(i);
        if (!red_black_tree->root) {
            red_black_tree->root = new_node;
            paintBlack(red_black_tree->root);
        }
        if (new_node) {
            red_black_tree->size++;
            return new_node;
        } else {
            printf("ERROR: YOU ARE OUT OF MEMORY\n");
            return NULL;
        }
    }

    if (i < new_node->value) {
        new_node->left = insertAux(red_black_tree, new_node->left, i);
        new_node->left->parent = new_node;

    } else if (i > new_node->value) {
        new_node->right = insertAux(red_black_tree, new_node->right, i);
        new_node->right->parent = new_node;
    }
    return new_node;
}

void fixTree(Tree t, Node rt, Node n) {
    // Red_Black_Root *red_black_tree = t;
    Red_Black_Node *root = rt;
    Red_Black_Node *new = n;
    Red_Black_Node *parent_new = NULL;
    Red_Black_Node *grandpa_new = NULL;

    while ((new != root) && (!isBlack(new)) && (isRed(new->parent))) {
        parent_new = new->parent;
        grandpa_new = new->parent->parent;

        // CASO A: pai de new é filho a esquerda do avô de new
        if (parent_new == grandpa_new->left) {
            Red_Black_Node *uncle_new = grandpa_new->right;

            // CASO 1A: o tio de new é vermelho, precisa recolorir
            if (uncle_new && isRed(uncle_new)) {
                paintRed(grandpa_new);
                paintBlack(parent_new);
                paintBlack(uncle_new);
                new = grandpa_new;

            } else {
                // CASO 2A: tio preto, new é filho a direita de seu pai, precisa rotacionar para a esquerda
                if (new == parent_new->right) {
                    rotateLeft(t, parent_new); 
                    new = parent_new;
                    parent_new = new->parent;
                }

                // CASO 3A: new é filho a esquerda de seu pai, precisa rotacionar para a direita
                char cor_aux[10];
                rotateRight(t, grandpa_new);
                strcpy(cor_aux, parent_new->color);
                strcpy(parent_new->color, grandpa_new->color);
                strcpy(grandpa_new->color, cor_aux);
                new = parent_new;
            }

            // CASO B: o pai de new é o filho direito do avô de new
        } else {
            Red_Black_Node *uncle_new = grandpa_new->left;

            // CASO 1B: o tio de new é vermelho, precisa recolorir
            if (uncle_new && isRed(uncle_new)) {
                paintRed(grandpa_new);
                paintBlack(parent_new);
                paintBlack(uncle_new);
                new = grandpa_new;

            } else {
                // CASO 2B: new é filho a esquerda de seu pai, precisa rotacionar para a direita
                if (new == parent_new->left) {
                    rotateRight(t, parent_new);
                    new = parent_new;
                    parent_new = new->parent;
                }

                // CASO 3B: new é filho a direita de seu pai, precisa rotacionar para a esquerda
                char cor_aux[10];
                rotateLeft(t, grandpa_new);
                strcpy(cor_aux, parent_new->color);
                strcpy(parent_new->color, grandpa_new->color);
                strcpy(grandpa_new->color, cor_aux);
                new = parent_new;
            }
        }
    }
    paintBlack(root);
}

void rotateLeft(Tree t, Node n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *node = n;
    Red_Black_Node *right_child = node->right;

    node->right = right_child->left;
    if (node->right) {
        node->right->parent = node;
    }
    right_child->parent = node->parent;

    if (!node->parent) {
        red_black_tree->root = right_child;

    } else if ((node == node->parent->left)) {
        node->parent->left = right_child;

    } else {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;
}

void rotateRight(Tree t, Node n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *node = n;
    Red_Black_Node *left_child = node->left;
    Red_Black_Node *aux2 = left_child->right;

    node->left = aux2;
    if (node->left) {
        node->left->parent = node;
    }
    left_child->parent = node->parent;
    if (!node->parent) {
        red_black_tree->root = left_child;

    } else if ((node == node->parent->left)) {
        node->parent->left = left_child;

    } else {
        node->parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;
}

bool isBlack(Node n) {
    Red_Black_Node *node = n;
    if (!strcmp(node->color, "BLACK")) {
        return true;
    }
    return false;
}

void paintBlack(Node n) {
    Red_Black_Node *node = n;
    strcpy(node->color, "BLACK");
}

bool isRed(Node n) {
    Red_Black_Node *node = n;
    if (!strcmp(node->color, "RED")) {
        return true;
    }
    return false;
}

void paintRed(Node n) {
    Red_Black_Node *node = n;
    strcpy(node->color, "RED");
}

Node searchNode(Tree t, Node n, int i) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *new_node = n;
    if (!new_node) {
        return NULL;
    }
    if (i == new_node->value) {
        return new_node;
    }
    if (i < new_node->value) {
        return searchNode(red_black_tree, new_node->left, i);
    } else {
        return searchNode(red_black_tree, new_node->right, i);
    }
}

Node getRoot(Tree t) {
    Red_Black_Root *red_black_tree = t;
    return red_black_tree->root;
}

void traversePreOrder(Tree t, ToDoNode f, void *aux) {
    Red_Black_Root *br_tree = t;
    traverseAux(br_tree->root, f, aux);
}

void traverseAux(Node root, ToDoNode f, void *aux) {
    Red_Black_Node *node = root;
    if (!node) {
        return;
    }

    traverseAux(node->left, f, aux);
    f(node->value, aux);
    traverseAux(node->right, f, aux);
}

void levelOrder(Tree t, ToDoNode f, void *aux) {
    Red_Black_Root *br_tree = t;
    int h = height(br_tree->root);
    for (int i = 0; i <= h; i++) {
        levelOrderAux(br_tree->root, f, i);
    }
}

void levelOrderAux(Node root, ToDoNode f, int level) {
    Red_Black_Node *node = root;
    if (!node) {
        return;
    }
    if (level == 1) {
        printf("\n%d %s\n", node->value, node->color);
        if (node->left) {
            printf("L=%d\n", node->left->value);
        }
        if (node->right) {
            printf("R=%d\n", node->right->value);
        }
        if (node->parent) {
            printf("P=%d\n", node->parent->value);
        }
    } else if (level > 1) {
        levelOrderAux(node->left, f, level - 1);
        levelOrderAux(node->right, f, level - 1);
    }
}

int height(Node n) {
    Red_Black_Node *node = n;
    if (!node) {
        return 0;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);
    if (left_height > right_height) {
        return (left_height + 1);
    } else {
        return (right_height + 1);
    }
}

void print(int i, void *aux) {
    printf("%d ", i);
}

void freeTree(Tree t) {
    Red_Black_Root *red_black_tree = t;
    freeAux(red_black_tree->root);
    free(red_black_tree);
}

void freeAux(Node root) {
    Red_Black_Node *node = root;
    if (!node) {
        return;
    }

    freeAux(node->left);
    freeAux(node->right);
    if (node) {
        free(node);
    }
}