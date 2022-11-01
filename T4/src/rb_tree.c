#include "rb_tree.h"

struct node {
    InfoRb value;
    double x, y;
    struct node *parent;
    struct node *left;
    struct node *right;
    char color[10];
};
typedef struct node Red_Black_Node;

struct tree {
    Red_Black_Node *root;
    Red_Black_Node *nil;
    double epislon;
    int size;
};
typedef struct tree Red_Black_Root;

/* Versão da Special Red Black totalmente de acordo com o Cormen, utilizando nó NIL sentinela */

// ---> HEADERS DE FUNÇÕES EXTRAS

RbNode newNode(InfoRb i, double x, double y);
void RBinsert(Rb t, RbNode n);
void fixRBinsert(Rb t, RbNode n);
RbNode rotateLeft(Rb t, RbNode n);
RbNode rotateRight(Rb t, RbNode n);
bool isBlack(RbNode n);
void paintBlack(RbNode n);
bool isRed(RbNode n);
void paintRed(RbNode n);
RbNode searchNode(Rb t, RbNode n, double xa, double ya);
void transplantRB(Rb t, RbNode n, RbNode n2);
void fixRBdelete(Rb t, RbNode n);
RbNode getLargestLeft(RbNode n, RbNode nil);
RbNode getSmallestRight(RbNode n, RbNode nil);
void traverseAux(RbNode root, RbNode nil, FvisitaNo f, void *aux);
void levelOrderAux(RbNode root, RbNode nil, int level);
int heightOfLevel(RbNode n, RbNode nil);
void traverseSim(RbNode root, RbNode nil, FvisitaNo f, void *aux);
void freeAux(RbNode n, RbNode nil);

// FIM <---

Rb createRB(double epsilon) {
    Red_Black_Root *new_tree = calloc(1, sizeof(Red_Black_Root));

    new_tree->nil = calloc(1, sizeof(Red_Black_Node));
    paintBlack(new_tree->nil);
    new_tree->nil->value = NULL;

    new_tree->epislon = epsilon;
    new_tree->root = new_tree->nil;
    new_tree->size = 0;

    return new_tree;
}

RbNode newNode(InfoRb i, double x, double y) {
    Red_Black_Node *new_node = calloc(1, sizeof(Red_Black_Node));
    new_node->value = i;
    new_node->x = x;
    new_node->y = y;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

RbNode insertRB(Rb t, double x, double y, InfoRb info) {
    Red_Black_Node *new_node = newNode(info, x, y);
    RBinsert(t, new_node);

    return new_node;
}

void RBinsert(Rb t, RbNode n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *nil = red_black_tree->nil;
    Red_Black_Node *x1 = red_black_tree->root;
    Red_Black_Node *y1 = nil;
    Red_Black_Node *z = n;
    // Insert em arv binaria de busca padrao

    while (x1 != nil) {
        y1 = x1;
        if ((z->x < x1->x) || (z->x == x1->x && z->y < x1->y)) {
            x1 = x1->left;
        } else {
            x1 = x1->right;
        }
    }
    z->parent = y1;
    if (y1 == nil) {
        red_black_tree->root = z;
    } else if ((z->x < y1->x) || (z->x == y1->x && z->y < y1->y)) {
        y1->left = z;
    } else {
        y1->right = z;
    }
    z->left = nil;
    z->right = nil;
    red_black_tree->size++;
    paintRed(z);
    fixRBinsert(t, z);
}

void fixRBinsert(Rb t, RbNode n) {
    Red_Black_Root *rb_tree = t;
    Red_Black_Node *z = n;
    Red_Black_Node *y = NULL;

    while (z->parent && isRed(z->parent)) {
        // CASO A: pai de z é filho a esquerda do avô de z
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;

            // CASO 1A: o tio de z é vermelho, precisa recolorir
            if (y && isRed(y)) {
                paintBlack(z->parent);
                paintBlack(y);
                paintRed(z->parent->parent);
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
        } else {
            if (z->parent == z->parent->parent->right) {
                y = z->parent->parent->left;

                // CASO 1B: o tio de z é vermelho, precisa recolorir
                if (y && isRed(y)) {
                    paintBlack(z->parent);
                    paintBlack(y);
                    paintRed(z->parent->parent);
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
    }
    paintBlack(rb_tree->root);
}

RbNode rotateLeft(Rb t, RbNode n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *nil = red_black_tree->nil;
    Red_Black_Node *node = n;         // avô 2
    Red_Black_Node *y = node->right;  // pai (direita)

    node->right = y->left;
    if (y->left != nil) {
        y->left->parent = node;
    }
    y->parent = node->parent;

    if (node->parent == nil) {
        red_black_tree->root = y;

    } else if ((node == node->parent->left)) {
        node->parent->left = y;

    } else {
        node->parent->right = y;
    }

    y->left = node;
    node->parent = y;
    return y;
}

RbNode rotateRight(Rb t, RbNode n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *nil = red_black_tree->nil;
    Red_Black_Node *node = n;        // recebo o AVÔ
    Red_Black_Node *y = node->left;  // pai

    node->left = y->right;  // esqueda do avô aponta para direita do pai
    if (y->right != nil) {
        y->right->parent = node;
    }
    y->parent = node->parent;

    if (node->parent == nil) {
        red_black_tree->root = y;

    } else if ((node == node->parent->right)) {
        node->parent->right = y;

    } else {
        node->parent->left = y;
    }

    y->right = node;
    node->parent = y;
    return y;
}

bool isBlack(RbNode n) {
    Red_Black_Node *node = n;
    if (n) {
        if (!strcmp(node->color, "BLACK")) {
            return true;
        }
    }
    return false;
}

void paintBlack(RbNode n) {
    Red_Black_Node *node = n;
    if (n) {
        strcpy(node->color, "BLACK");
    }
}

bool isRed(RbNode n) {
    Red_Black_Node *node = n;
    if (n) {
        if (!strcmp(node->color, "RED")) {
            return true;
        }
        return false;
    }
    return false;
}

void paintRed(RbNode n) {
    Red_Black_Node *node = n;
    if (node && node->value) {
        strcpy(node->color, "RED");
    }
}

InfoRb getInfoRB(Rb t, RbNode n, double xa, double ya) {
    Red_Black_Node *node = n;
    return node->value;
}

RbNode getNodeRB(Rb t, double xa, double ya) {
    Red_Black_Root *tree = t;
    Red_Black_Node *node = searchNode(t, tree->root, xa, ya);
    return node;
}

RbNode searchNode(Rb t, RbNode n, double xa, double ya) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *new_node = n;
    if (new_node == red_black_tree->nil) {
        return NULL;
    }

    if (fabs(new_node->x - xa) <= red_black_tree->epislon && fabs(new_node->y - ya) <= red_black_tree->epislon) {
        return new_node;
    }

    if ((xa < new_node->x) || (xa == new_node->x && ya < new_node->y)) {
        return searchNode(t, new_node->left, xa, ya);

    } else {
        return searchNode(t, new_node->right, xa, ya);
    }
}


InfoRb removeRB(Rb t, double xa, double ya) {
    Red_Black_Root *tree = t;
    Red_Black_Node *rb_node = getNodeRB(tree, xa, ya);
    Red_Black_Node *nil = tree->nil;

    if (!rb_node) {
        printf("\nNODE x = %lf y = %lf NOT FOUND\n", xa, ya);
        return NULL;
    }

    if (fabs(rb_node->x - xa) <= tree->epislon && fabs(rb_node->y - ya) <= tree->epislon) {
        InfoRb info = rb_node->value;
        Red_Black_Node *x = nil;
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
            y = getSmallestRight(rb_node->right, nil);
            strcpy(y_original_color, y->color);
            x = y->right;

            if (y->parent == rb_node) {
                if (x != nil) {
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
            if (x != nil) {
                fixRBdelete(tree, x);
            }
        }

        tree->size--;
        return info;
    }
    return NULL;  // ERRO!
}

void transplantRB(Rb t, RbNode n, RbNode n2) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *nil = red_black_tree->nil;
    Red_Black_Node *u = n;
    Red_Black_Node *v = n2;

    if (u->parent == nil) {  // u é raiz
        red_black_tree->root = v;

    } else if (u == u->parent->left) {  // u é filho da esquerda
        u->parent->left = v;
    } else {  // u é filho da direita
        u->parent->right = v;
    }
    if (v != nil) {
        v->parent = u->parent;
    }
}

void fixRBdelete(Rb t, RbNode n) {
    Red_Black_Root *rb_tree = t;
    Red_Black_Node *rb_node = n;
    Red_Black_Node *root = rb_tree->root;
    Red_Black_Node *nil = rb_tree->nil;
    Red_Black_Node *w = nil;

    while (rb_node != root && isBlack(rb_node)) {
        if (rb_node == rb_node->parent->left) {
            w = rb_node->parent->right;

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
                rb_node = rb_node->parent;

                // Caso 3A: Filho direito do irmão é vermelho Caso Right right
            } else if (isBlack(w->right)) {
                paintBlack(w->left);
                paintRed(w);
                rotateRight(t, w);
                w = rb_node->parent->right;
            }
            strcpy(w->color, rb_node->parent->color);
            paintBlack(rb_node->parent);
            paintBlack(w->right);
            rotateLeft(t, rb_node->parent);
            rb_node = root;

        } else {
            if (rb_node == rb_node->parent->right) {
                w = rb_node->parent->left;

                // Caso 1B: irmão w é vermelho
                if (isRed(w)) {
                    paintRed(rb_node->parent);
                    paintBlack(w);
                    rotateRight(t, rb_node->parent);
                    w = rb_node->parent->left;
                    rb_node = rb_node->parent;
                }

                // Caso 2B: Ambos os filhos do irmão w são pretos
                if ((isBlack(w->left) && isBlack(w->right))) {
                    paintRed(w);
                    rb_node = rb_node->parent;

                    // Caso 3B: Filho esquerdo do irmão é vermelho caso Left left
                } else if (w->left && isBlack(w->left)) {
                    paintBlack(w->right);
                    paintRed(w);
                    rotateLeft(t, w);
                    w = rb_node->parent->left;
                }
                strcpy(w->color, rb_node->parent->color);
                paintBlack(rb_node->parent);
                paintBlack(w->left);
                rotateRight(t, rb_node->parent);
                rb_node = root;
            }
        }
    }
    paintBlack(rb_node);
}

RbNode getLargestLeft(RbNode n, RbNode nil) {
    Red_Black_Node *node = n;
    while (node->right != nil) {
        node = node->right;
    }
    return node;
}

RbNode getSmallestRight(RbNode n, RbNode nil) {
    Red_Black_Node *node = n;
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

void percursoProfundidade(Rb t, FvisitaNo f, void *aux) {
    Red_Black_Root *rb_tree = t;
    traverseAux(rb_tree->root, rb_tree->nil, f, aux);
}

void traverseAux(RbNode root, RbNode nil, FvisitaNo f, void *aux) {
    Red_Black_Node *node = root;
    if (node == nil) {
        return;
    }

    f(node->value, aux);
    traverseAux(node->left, nil, f, aux);
    traverseAux(node->right, nil, f, aux);
}

void percursoLargura(Rb t, FvisitaNo f, void *aux) {
    Red_Black_Root *rb_tree = t;
    int h = heightOfLevel(rb_tree->root, rb_tree->nil);
    printf("\n\tTamanho da árvore: %d\n\n", rb_tree->size);
    for (int i = 0; i <= h; i++) {
        levelOrderAux(rb_tree->root, rb_tree->nil, i);
    }
}

void levelOrderAux(RbNode root, RbNode nil, int level) {
    Red_Black_Node *node = root;
    if (node == nil) {
        return;
    }

    if (level == 1) {
        if (node->parent != nil && node->parent->value) {
            printf("\n\n\n\t%.2lf %.2lf %s\n", node->parent->x, node->parent->y, node->parent->color);
            printf("\t      |\n");
        }

        printf("\t%.2lf %.2lf %s\n", node->x, node->y, node->color);
        printf("\t /");
        printf("\t    \\\n");

        if (node->left != nil && node->left->value) {
            printf("%.2lf %.2lf %s", node->left->x, node->left->y, node->left->color);
        }
        if (node->right != nil && node->right->value) {
            printf("  %.2lf %.2lf %s", node->right->x, node->right->y, node->right->color);
        }

    } else if (level > 1) {
        levelOrderAux(node->left, nil, level - 1);
        levelOrderAux(node->right, nil, level - 1);
    }
}

int heightOfLevel(RbNode n, RbNode nil) {
    Red_Black_Node *node = n;
    if (node == nil) {
        return 0;
    }

    int left_height = heightOfLevel(node->left, nil);
    int right_height = heightOfLevel(node->right, nil);
    if (left_height > right_height) {
        return (left_height + 1);
    } else {
        return (right_height + 1);
    }
}

void killRB(Rb t) {
    Red_Black_Root *red_black_tree = t;
    freeAux(red_black_tree->root, red_black_tree->nil);
    free(red_black_tree->nil);
    free(red_black_tree);
}

void freeAux(RbNode root, RbNode nil) {
    Red_Black_Node *node = root;
    if (node == nil) {
        return;
    }

    free(node->value);
    freeAux(node->left, nil);
    freeAux(node->right, nil);
    if (node) {
        free(node);
    }
}
