#include "list.h"
#include "shapes.h"
#include "srb_tree.h"

struct node {
    Info value;
    double x, y;
    double mbbX1, mbbX2, mbbY1, mbbY2;      // minimum bounding box da figura
    double SmbbX1, SmbbX2, SmbbY1, SmbbY2;  // minimum bounding box da subárvore
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

Node newNode(Node nil, Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2);
void RBinsert(SRBTree t, Node n);
void fixRBinsert(SRBTree t, Node n);
Node rotateLeft(SRBTree t, Node n);
Node rotateRight(SRBTree t, Node n);
bool isBlack(Node n);
void paintBlack(Node n);
bool isRed(Node n);
void paintRed(Node n);
void getMBBSub(Node n, Node nil, double *x1, double *y1, double *x2, double *y2);
void uniteMBB(double x11, double y11, double x12, double y12, double x21, double y21, double x22, double y22, double *xr1, double *yr1, double *xr2, double *yr2);
void fixTreeMBB(SRBTree t, Node n);
void rectangleOverlaps(Node n, Node nil, double x, double y, double w, double h, Lista resultado);
void mbbFullyInside(Node n, Node nil, double x, double y, double w, double h, Lista resultado);
Node searchNode(SRBTree t, Node n, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);
void transplantRB(SRBTree t, Node n, Node n2);
void fixRBdelete(SRBTree t, Node n);
Node getLargestLeft(Node n, Node nil);
Node getSmallestRight(Node n, Node nil);
void makeDotNodes(Node n, Node nil, FILE *dotFile);
void makeDotEdges(Node n, Node nil, FILE *dotFile);
void traverseAux(Node root, Node nil, FvisitaNo f, void *aux);
void levelOrderAux(Node root, Node nil, int level);
int heightOfLevel(Node n, Node nil);
void mbbFullyInside(Node n, Node nil, double x, double y, double w, double h, Lista resultado);
void traverseSim(Node root, Node nil, FvisitaNo f, void *aux);
void freeAux(Node n, Node nil);

// FIM <---

SRBTree createSRB(double epsilon) {
    Red_Black_Root *new_tree = calloc(1, sizeof(Red_Black_Root));

    new_tree->nil = calloc(1, sizeof(Red_Black_Node));
    paintBlack(new_tree->nil);
    new_tree->nil->value = NULL;

    new_tree->epislon = epsilon;
    new_tree->root = new_tree->nil;
    new_tree->size = 0;

    return new_tree;
}

Node newNode(Node nil, Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2) {
    Red_Black_Node *new_node = calloc(1, sizeof(Red_Black_Node));
    new_node->value = i;
    new_node->x = x;
    new_node->y = y;
    new_node->mbbX1 = mbbX1;
    new_node->mbbX2 = mbbX2;
    new_node->mbbY1 = mbbY1;
    new_node->mbbY2 = mbbY2;
    new_node->SmbbX1 = mbbX1;
    new_node->SmbbY1 = mbbY1;
    new_node->SmbbX2 = mbbX2;
    new_node->SmbbY2 = mbbY2;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Node insertSRB(SRBTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info) {
    Red_Black_Root *tree = t;

    Red_Black_Node *new_node = newNode(tree->nil, info, x, y, mbbX1, mbbY1, mbbX2, mbbY2);
    RBinsert(t, new_node);

    fixTreeMBB(t, new_node);
    return new_node;
}

void RBinsert(SRBTree t, Node n) {
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
    // printf("z = %p x = %p y = %p \n", z, x1, y1);
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

Node insertBBSRB(SRBTree t, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info) {
    return insertSRB(t, mbbX1, mbbY1, mbbX1, mbbY1, mbbX2, mbbY2, info);
}

void fixRBinsert(SRBTree t, Node n) {
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

Node rotateLeft(SRBTree t, Node n) {
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

Node rotateRight(SRBTree t, Node n) {
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

bool isBlack(Node n) {
    Red_Black_Node *node = n;
    if (n) {
        if (!strcmp(node->color, "BLACK")) {
            return true;
        }
    }
    return false;
}

void paintBlack(Node n) {
    Red_Black_Node *node = n;
    if (n) {
        strcpy(node->color, "BLACK");
    }
}

bool isRed(Node n) {
    Red_Black_Node *node = n;
    if (n) {
        if (!strcmp(node->color, "RED")) {
            return true;
        }
        return false;
    }
    return false;
}

void paintRed(Node n) {
    Red_Black_Node *node = n;
    if (node && node->value) {
        strcpy(node->color, "RED");
    }
}

void getMBBSub(Node n, Node nil, double *x1, double *y1, double *x2, double *y2) {
    Red_Black_Node *node = n;

    if (node->left == nil && node->right == nil) {
        *x1 = node->mbbX1;
        *y1 = node->mbbY1;
        *x2 = node->mbbX2;
        *y2 = node->mbbY2;
    } else {
        *x1 = node->SmbbX1;
        *y1 = node->SmbbY1;
        *x2 = node->SmbbX2;
        *y2 = node->SmbbY2;
    }
}

void uniteMBB(double x11, double y11, double x12, double y12, double x21, double y21, double x22, double y22, double *xr1, double *yr1, double *xr2, double *yr2) {
    *xr1 = x11 < x21 ? x11 : x21;
    *yr1 = y11 < y21 ? y11 : y21;
    *xr2 = x12 > x22 ? x12 : x22;
    *yr2 = y12 > y22 ? y12 : y22;
}

void fixTreeMBB(SRBTree t, Node n) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *node = n;
    Red_Black_Node *nil = red_black_tree->nil;

    while (node != nil) {
        if (node->left != nil) {
            getMBBSub(node->left, nil, &node->SmbbX1, &node->SmbbY1, &node->SmbbX2, &node->SmbbY2);
        } else {
            getMBBSub(node, nil, &node->SmbbX1, &node->SmbbY1, &node->SmbbX2, &node->SmbbY2);
        }

        if (node->right != nil) {
            getMBBSub(node->right, nil, &node->SmbbX1, &node->SmbbY1, &node->SmbbX2, &node->SmbbY2);
        } else {
            getMBBSub(node, nil, &node->SmbbX1, &node->SmbbY1, &node->SmbbX2, &node->SmbbY2);
        }

        uniteMBB(node->mbbX1, node->mbbY1, node->mbbX2, node->mbbY2, node->SmbbX1, node->SmbbY1, node->SmbbX2, node->SmbbY2, &node->SmbbX1, &node->SmbbY1, &node->SmbbX2, &node->SmbbY2);
        node = node->parent;
    }
}

void getBBPartSRB(SRBTree t, double x, double y, double w, double h, Lista resultado) {  // MBB do node e retangulo tem alguma intersecção
    Red_Black_Root *tree = t;
    rectangleOverlaps(tree->root, tree->nil, x, y, w, h, resultado);
}

void rectangleOverlaps(Node n, Node nil, double x, double y, double w, double h, Lista resultado) {
    Red_Black_Node *node = n;
    double l1x = node->mbbX1;
    double l1y = node->mbbY1;
    double r1x = node->mbbX2;
    double r1y = node->mbbY2;
    double l2x = x;
    double l2y = y;
    double r2x = x + w;
    double r2y = y + h;
    int i = 0;

    if (node == nil) {
        return;
    }

    if (l1x == r1x || l1y == r1y || r2x == l2x || l2y == r2y) {
        i++;
    }
    if (l1x > r2x || l2x > r1x) {
        i++;
    }
    if (r1y > l2y || r2y > l1y) {
        i++;
    }
    if (i == 0) {
        insereFim(resultado, node);
    }

    rectangleOverlaps(node->left, nil, x, y, w, h, resultado);
    rectangleOverlaps(node->right, nil, x, y, w, h, resultado);
}

void getBBSRB(SRBTree t, double x, double y, double w, double h, Lista resultado) {  // MBB completamente dentro do retangulo
    Red_Black_Root *red_black_tree = t;
    mbbFullyInside(red_black_tree->root, red_black_tree->nil, x, y, w, h, resultado);
}

void mbbFullyInside(Node n, Node nil, double x, double y, double w, double h, Lista resultado) {
    Red_Black_Node *node = n;

    if (node == nil) {
        return;
    }

    double x1 = node->mbbX1;
    double y1 = node->mbbY1;
    double w1 = node->mbbX2 - x1;
    double h1 = node->mbbY2 - y1;
    if (((x + w) >= (x1 + w1))) {
        if (((y + h) >= (y1 + h1))) {
            if (x <= x1 && y <= y1) {
                insereFim(resultado, n);
            }
        }
    }

    mbbFullyInside(node->left, nil, x, y, w, h, resultado);
    mbbFullyInside(node->right, nil, x, y, w, h, resultado);
}

Info getInfoSRB(SRBTree t, Node n, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2) {
    Red_Black_Node *node = n;
    *mbbX1 = node->mbbX1;
    *mbbY1 = node->mbbY1;
    *mbbX2 = node->mbbX2;
    *mbbY2 = node->mbbY2;
    return node->value;
}

Node getNodeSRB(SRBTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2) {
    Red_Black_Root *tree = t;
    Red_Black_Node *node = searchNode(t, tree->root, xa, ya, mbbX1, mbbY1, mbbX2, mbbY2);
    return node;
}

Node searchNode(SRBTree t, Node n, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *new_node = n;
    if (new_node == red_black_tree->nil) {
        return NULL;
    }

    if (fabs(new_node->x - xa) <= red_black_tree->epislon && fabs(new_node->y - ya) <= red_black_tree->epislon) {
        *mbbX1 = new_node->mbbX1;
        *mbbY1 = new_node->mbbY1;
        *mbbX2 = new_node->mbbX2;
        *mbbY2 = new_node->mbbY2;
        return new_node;
    }

    if ((xa < new_node->x) || (xa == new_node->x && ya < new_node->y)) {
        return searchNode(t, new_node->left, xa, ya, mbbX1, mbbY1, mbbX2, mbbY2);

    } else {
        return searchNode(t, new_node->right, xa, ya, mbbX1, mbbY1, mbbX2, mbbY2);
    }
}

void updateInfoSRB(SRBTree t, Node n, Info i) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *node = n;

    double x = getX(i);
    double y = getY(i);

    if (fabs(node->x - x) <= red_black_tree->epislon && fabs(node->y - y) <= red_black_tree->epislon) {
        node->value = i;
        printf("Sucesso ao atualizar a info\n");  // Apenas trocadas as informações

    } else {
        removeSRB(t, node->x, node->y, 0, 0, 0, 0);  // Remove info atual e analisa os asos para reinserir o nó atualizado
        switch (getId(i)) {
            case 1:
                insertSRB(t, x, y, x - getR(i), y - getR(i), 2 * getR(i), 2 * getR(i), i);
                break;

            case 2:
                insertSRB(t, x, y, x, y, x + getW(i), y + getH(i), i);
                break;

            case 3:;
                double y_aux, y2_aux;
                findLineXY(&y_aux, &y2_aux, i);
                insertSRB(t, x, y, x, y_aux, getX2(i), y2_aux, i);
                break;

            case 4:
                insertSRB(t, x, y, x, y, x, y, i);
                break;

            default:
                break;
        }
    }
} 

Info removeSRB(SRBTree t, double xa, double ya, double mbbX1, double mbbY1, double mbbX2, double mbbY2) {
    Red_Black_Root *tree = t;
    Red_Black_Node *rb_node = getNodeSRB(tree, xa, ya, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
    Red_Black_Node *nil = tree->nil;

    if (!rb_node) {
        printf("\nNODE x = %lf y = %lf NOT FOUND\n", xa, ya);
        return NULL;
    }

    if (fabs(rb_node->x - xa) <= tree->epislon && fabs(rb_node->y - ya) <= tree->epislon) {
        Info info = rb_node->value;
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

        if (x != nil) {
            fixTreeMBB(tree, x);
        }
        tree->size--;
        return info;
    }
    return NULL;  // ERRO!
}

void transplantRB(SRBTree t, Node n, Node n2) {
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

void fixRBdelete(SRBTree t, Node n) {
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

Node getLargestLeft(Node n, Node nil) {
    Red_Black_Node *node = n;
    while (node->right != nil) {
        node = node->right;
    }
    return node;
}

Node getSmallestRight(Node n, Node nil) {
    Red_Black_Node *node = n;
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

void printSRB(SRBTree t, char *nomeArq) {
    Red_Black_Root *tree = t;
    char node[] = "[fontname=\"Helvetica,Arial,sans-serif\" style=\"filled\"]";
    char edge[] = "[fontname=\"Helvetica,Arial,sans-serif\" color=\"black\"]";
    FILE *dotFile = fopen(nomeArq, "w");

    fprintf(dotFile, "digraph RB_Teste {\n");
    fprintf(dotFile, "\tnode %s\n", node);
    fprintf(dotFile, "\tedge %s\n\n", edge);
    fprintf(dotFile, "\t{\n");
    fprintf(dotFile, "\t\tnode [fillcolor=\" black\" fontcolor=\" white\"] %s \n", "nil");
    makeDotNodes(tree->root, tree->nil, dotFile);
    fprintf(dotFile, "\t}\n\n");
    makeDotEdges(tree->root, tree->nil, dotFile);
    fprintf(dotFile, "}\n");
    fclose(dotFile);
}

void makeDotNodes(Node n, Node nil, FILE *dotFile) {
    Red_Black_Node *node = n;
    if (node == nil) {
        return;
    }

    if (node->value) {
        if (isBlack(node)) {
            fprintf(dotFile, "\t\tnode [fillcolor=\" black\" fontcolor=\" white\"] %d \n", getId(node->value));
        } else if (isRed(node)) {
            fprintf(dotFile, "\t\tnode [fillcolor=\" red\" fontcolor=\" white\"] %d \n", getId(node->value));
        }
    }

    makeDotNodes(node->left, nil, dotFile);
    makeDotNodes(node->right, nil, dotFile);
}

void makeDotEdges(Node n, Node nil, FILE *dotFile) {
    Red_Black_Node *node = n;
    if (node == nil) {
        return;
    }

    if (node->value && node->left && node->left->value) {
        fprintf(dotFile, "\t%d -> %d \n", getId(node->value), getId(node->left->value));
    }
    if (node->value && node->right && node->right->value) {
        fprintf(dotFile, "\t%d -> %d \n", getId(node->value), getId(node->right->value));
    }
    if (node->left == nil && node->value) {
        fprintf(dotFile, "\t%d -> nil \n", getId(node->value));
    }
    if (node->right == nil && node->value) {
        fprintf(dotFile, "\t%d -> nil \n", getId(node->value));
    }

    makeDotEdges(node->left, nil, dotFile);
    makeDotEdges(node->right, nil, dotFile);
}

void percursoProfundidade(SRBTree t, FvisitaNo f, void *aux) {
    Red_Black_Root *rb_tree = t;
    traverseAux(rb_tree->root, rb_tree->nil, f, aux);
}

void traverseAux(Node root, Node nil, FvisitaNo f, void *aux) {
    Red_Black_Node *node = root;
    if (node == nil) {
        return;
    }

    if (node->value) {
        f(node->value, node->x, node->y, node->mbbX1, node->mbbY1, node->mbbX2, node->mbbY2, aux);
    }

    traverseAux(node->left, nil, f, aux);
    traverseAux(node->right, nil, f, aux);
}

void percursoLargura(SRBTree t, FvisitaNo f, void *aux) {
    Red_Black_Root *rb_tree = t;
    int h = heightOfLevel(rb_tree->root, rb_tree->nil);
    printf("\n\tTamanho da árvore: %d\n\n", rb_tree->size);
    for (int i = 0; i <= h; i++) {
        levelOrderAux(rb_tree->root, rb_tree->nil, i);
    }
}

void levelOrderAux(Node root, Node nil, int level) {
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

int heightOfLevel(Node n, Node nil) {
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
void percursoSimetrico(SRBTree t, FvisitaNo f, void *aux) {
    Red_Black_Root *br_tree = t;
    traverseSim(br_tree->root, br_tree->nil, f, aux);
}

void traverseSim(Node root, Node nil, FvisitaNo f, void *aux) {
    Red_Black_Node *node = root;
    if (node == nil) {
        return;
    }

    traverseSim(node->left, nil, f, aux);
    f(node->value, node->x, node->y, node->mbbX1, node->mbbY1, node->mbbX2, node->mbbY2, aux);
    traverseSim(node->right, nil, f, aux);
}

void killSRB(SRBTree t) {
    Red_Black_Root *red_black_tree = t;
    freeAux(red_black_tree->root, red_black_tree->nil);
    free(red_black_tree->nil);
    free(red_black_tree);
}

void freeAux(Node root, Node nil) {
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
