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
    Red_Black_Node *nil;
    int size;
};
typedef struct tree Red_Black_Root;

Tree newTree() {
    Red_Black_Root *new_tree = calloc(1, sizeof(Red_Black_Root));
    new_tree->nil = calloc(1, sizeof(Red_Black_Node));
    paintBlack(new_tree->nil);
    new_tree->nil->value = INT_MAX;
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

void RBinsert(Tree t, Node n);

void insertTree(Tree t, int i) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *new_node = newNode(i);
    if (!red_black_tree->root) {
        red_black_tree->root = new_node;
        paintBlack(red_black_tree->root);
        red_black_tree->size++;
        return;
    }
    RBinsert(t, new_node);
    red_black_tree->size++;
}

void RBinsert(Tree t, Node n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *x = red_black_tree->root;
    Red_Black_Node *y = red_black_tree->nil;
    Red_Black_Node *z = n;

    printf("inserindo %d %p | %d %p\n", z->value, z, x->value, x);
    while (x != red_black_tree->nil) {
        y = x;
            printf("esquerda");
        if (z->value < x->value) {
            x = x->left;
        } else if (z->value > x->value) {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == red_black_tree->nil) {
        red_black_tree->root = z;
    } else if (z->value < x->value) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = red_black_tree->nil;
    z->right = red_black_tree->nil;
    paintRed(z);
    fixRBinsert(t, z);
}

void fixRBinsert(Tree t, Node n) {
    Red_Black_Root *rb_tree = t;
    Red_Black_Node *root = rb_tree->root;
    Red_Black_Node *z = n;
    Red_Black_Node *uncle_z = NULL;

    while ((z != root) && (isRed(z->parent))) {
        // CASO A: pai de z é filho a esquerda do avô de z
        if (z->parent == z->parent->parent->left) {
            if (z->parent->parent->right) {
                uncle_z = z->parent->parent->right;
            }

            // CASO 1A: o tio de z é vermelho, precisa recolorir
            if (uncle_z && isRed(uncle_z)) {
                paintRed(z->parent->parent);
                paintBlack(z->parent);
                paintBlack(uncle_z);
                z = z->parent->parent;

            } else {
                // CASO 2A: tio preto, z é filho a direita de seu pai, precisa rotacionar para a esquerda
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(t, z);
                }

                // CASO 3A: tio preto, z é filho a esquerda de seu pai, precisa rotacionar para a direita
                paintBlack(z->parent);
                paintRed(z->parent->parent);
                rotateRight(t, z->parent->parent);
            }

            // CASO B: o pai de z é o filho direito do avô de z
        } else if (z->parent && z->parent == z->parent->parent->right) {
            if (z->parent->parent->left) {
                uncle_z = z->parent->parent->left;
            }

            // CASO 1B: o tio de z é vermelho, precisa recolorir
            if (uncle_z && isRed(uncle_z)) {
                paintRed(z->parent->parent);
                paintBlack(z->parent);
                paintBlack(uncle_z);
                z = z->parent->parent;

            } else {
                // CASO 2B: tio preto, z é filho a esquerda de seu pai, precisa rotacionar para a direita
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(t, z);
                }

                // CASO 3B: z é filho a direita de seu pai, precisa rotacionar para a esquerda
                paintBlack(z->parent);
                paintRed(z->parent->parent);
                rotateLeft(t, z->parent->parent);
            }
        }
    }
    paintBlack(root);
}

void rotateLeft(Tree t, Node n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *node = n;                   // avô 2
    Red_Black_Node *right_child = node->right;  // pai (direita) 7

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
    Red_Black_Node *node = n;                 // recebo o AVÔ
    Red_Black_Node *left_child = node->left;  // pai

    node->left = left_child->right;  // esqueda do avô aponta para direita do pai
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

// Cases and algorithm of deletion: https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
void removeTree(Tree t, int i) {
    Red_Black_Root *tree = t;
    Red_Black_Node *rb_node = searchNode(tree, tree->root, i);
    Red_Black_Node *nil = tree->nil;

    if (!rb_node) {
        return;
    }

    Red_Black_Node *x = NULL;
    Red_Black_Node *y = rb_node;
    char y_original_color[10];
    strcpy(y_original_color, y->color);

    if (rb_node->left == nil) {
        x = rb_node->right;
        transplantRB(tree, rb_node, rb_node->right);
    } else if (rb_node->right == nil) {
        x = rb_node->left;
        transplantRB(tree, rb_node, rb_node->left);
    } else {
        y = getSmallestRight(rb_node->right);
        strcpy(y_original_color, y->color);
        x = y->right;

        if (y->parent == rb_node) {
            if (x) {
                x->parent = y;
            }
        } else {
            transplantRB(tree, y, y->right);
            y->right = rb_node->right;
            y->right->parent = y;
        }
        transplantRB(tree, rb_node, y);
        y->left = rb_node->left;
        y->left->parent = y;
        strcpy(y->color, rb_node->color);
    }
    if (!strcmp(y_original_color, "BLACK")) {
        fixRBdelete(tree, x);
    }
    tree->size--;
}

void transplantRB(Tree t, Node n, Node n2) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *u = n;
    Red_Black_Node *v = n2;

    if (!u->parent) {  // u é raiz
        red_black_tree->root = v;

    } else if (u == u->parent->left) {  // u é filho da esquerda
        u->parent->left = v;
    } else {  // u é filho da direita
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

// Cases and algorithm of deletion: https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
void fixRBdelete(Tree t, Node n) {
    Red_Black_Root *rb_tree = t;
    Red_Black_Node *rb_node = n;
    Red_Black_Node *root = rb_tree->root;
    Red_Black_Node *nil = rb_tree->nil;
    Red_Black_Node *w = NULL;

    while (root != rb_node && isBlack(rb_node)) {
        if (rb_node && rb_node == rb_node->parent->left) {
            w = rb_node->parent->right;
            if (!w->left) {
                w->left = nil;
            }
            if (!w->right) {
                w->right = nil;
            }

            // Caso 1A: irmão w é vermelho
            if (w && isRed(w)) {
                paintRed(rb_node->parent);
                paintBlack(w);
                rotateLeft(t, rb_node->parent);
                w = rb_node->parent->right;
            }

            // Caso 2A: Ambos os filhos do irmão w são pretos
            if ((isBlack(w->left) && isBlack(w->right))) {
                paintRed(w);
                rb_node = rb_node->parent;

                // Caso 3A: Filho direito do irmão é vermelho Caso Right right
            } else if ((w->right && isBlack(w->right))) {
                paintBlack(w->left);
                paintRed(w);
                rotateRight(t, w);
                w = rb_node->parent->right;
                rb_node = rb_node->parent;
            }

        } else if (rb_node && rb_node == rb_node->parent->right) {
            w = rb_node->parent->left;
            if (!w->left) {
                w->left = nil;
            }
            if (!w->right) {
                w->right = nil;
            }

            // Caso 1B: irmão w é vermelho
            if (w && isRed(w)) {
                paintRed(rb_node->parent);
                paintBlack(w);
                rotateRight(t, rb_node->parent);
                w = rb_node->parent->left;
            }

            // Caso 2B: Ambos os filhos do irmão w são pretos
            if ((isBlack(w->left) && isBlack(w->right))) {
                paintRed(w);
                rb_node = rb_node->parent;

                // Caso 3B: Filho esquerdo do irmão é vermelho caso Left left
            } else if ((w->left && isBlack(w->left))) {
                paintBlack(w->right);
                paintRed(w);
                rotateLeft(t, w);
                w = rb_node->parent->left;
                rb_node = rb_node->parent;
            }
        }
    }
}

Node getLargestLeft(Node n) {
    Red_Black_Node *node = n;
    while (node->right) {
        node = node->right;
    }
    return node;
}

Node getSmallestRight(Node n) {
    Red_Black_Node *node = n;
    while (node->left) {
        node = node->left;
    }
    return node;
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

    f(node->value, aux);
    traverseAux(node->left, f, aux);
    traverseAux(node->right, f, aux);
}

void levelOrder(Tree t) {
    Red_Black_Root *br_tree = t;
    int h = heightOfLevel(br_tree->root);
    for (int i = 0; i <= h; i++) {
        levelOrderAux(br_tree->root, i);
    }
}

void levelOrderAux(Node root, int level) {
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
        levelOrderAux(node->left, level - 1);
        levelOrderAux(node->right, level - 1);
    }
}

int heightOfLevel(Node n) {
    Red_Black_Node *node = n;
    if (!node) {
        return 0;
    }
    int left_height = heightOfLevel(node->left);
    int right_height = heightOfLevel(node->right);
    if (left_height > right_height) {
        return (left_height + 1);
    } else {
        return (right_height + 1);
    }
}

void printTREE(Tree t, char *nomeArq) {
    Red_Black_Root *tree = t;
    char node[] = "[fontname=\"Helvetica,Arial,sans-serif\" style=\"filled\"]";
    char edge[] = "[fontname=\"Helvetica,Arial,sans-serif\" color=\"black\"]";
    FILE *dotFile = fopen(nomeArq, "w");

    fprintf(dotFile, "digraph RB_Teste {\n");
    fprintf(dotFile, "\tnode %s\n", node);
    fprintf(dotFile, "\tedge %s\n\n", edge);
    fprintf(dotFile, "\t{\n");
    makeDotNodes(tree->root, dotFile);
    fprintf(dotFile, "\t}\n\n");
    makeDotEdges(tree->root, dotFile);
    fprintf(dotFile, "}\n");
    fclose(dotFile);
}

void makeDotNodes(Node n, FILE *dotFile) {
    Red_Black_Node *node = n;
    if (!node) {
        return;
    }

    if (node) {
        if (isBlack(node)) {
            fprintf(dotFile, "\t\tnode [fillcolor=\" black\" fontcolor=\" white\"] %d \n", node->value);
        } else if (isRed(node)) {
            fprintf(dotFile, "\t\tnode [fillcolor=\" red\" fontcolor=\" white\"] %d \n", node->value);
        }
    }

    makeDotNodes(node->left, dotFile);
    makeDotNodes(node->right, dotFile);
}

void makeDotEdges(Node n, FILE *dotFile) {
    Red_Black_Node *node = n;
    if (!node) {
        return;
    }

    if (node->left) {
        fprintf(dotFile, "\t%d -> %d \n", node->value, node->left->value);
    }
    if (node->right) {
        fprintf(dotFile, "\t%d -> %d \n", node->value, node->right->value);
    }

    makeDotEdges(node->left, dotFile);
    makeDotEdges(node->right, dotFile);
}

void freeTree(Tree t) {
    Red_Black_Root *red_black_tree = t;
    free(red_black_tree->nil);
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

void removeNils(Tree t, Node root) {
    Red_Black_Root *tree = t;
    Red_Black_Node *node = root;
    Red_Black_Node *nil = tree->nil;
    if (!node) {
        return;
    }
    if (node->left == nil) {
        node->left = NULL;
    }
    if (node->right == nil) {
        node->right = NULL;
    }
    removeNils(t, node->left);
    removeNils(t, node->right);
}