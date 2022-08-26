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
    fixRBinsert(t, new_node);
}

Node insertAux(Tree t, Node n, int i) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *new_node = n;

    if (!new_node) {
        new_node = newNode(i);
        if (!red_black_tree->root) {
            red_black_tree->root = new_node;
            paintBlack(new_node);
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

void fixRBinsert(Tree t, Node n) {
    Red_Black_Root *rb_tree = t;
    Red_Black_Node *root = rb_tree->root;
    Red_Black_Node *z = n;
    Red_Black_Node *uncle_z = NULL;

    while ((z != root) && (isRed(z)) && (isRed(z->parent))) {
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

Node removeTree(Tree t, Node n, int i) {
    Red_Black_Root *red_black_tree = t;
    Red_Black_Node *rb_node = n;
    if (!rb_node) {
        return rb_node;
    }

    if (i < rb_node->value) {
        rb_node->left = removeTree(red_black_tree, rb_node->left, i);

    } else if (i > rb_node->value) {
        rb_node->right = removeTree(red_black_tree, rb_node->right, i);

    } else if (i == rb_node->value) {
        Red_Black_Node *aux = NULL;
        if (!rb_node->left && !rb_node->right) { // é folha
            fixRBdelete(red_black_tree, red_black_tree->root, rb_node); 
            free(rb_node);
            red_black_tree->size--;
            return NULL;

        } else if (!rb_node->left) {  // somente direita
            aux = rb_node->right;
            aux->parent = rb_node->parent;
            if (rb_node->parent) {
                if (rb_node == rb_node->parent->left) {
                    rb_node->parent->left = aux;
                } else if (rb_node == rb_node->parent->right) {
                    rb_node->parent->right = aux;
                }
            } else {
                red_black_tree->root = aux;
            }

            fixRBdelete(red_black_tree, red_black_tree->root, rb_node);
            free(rb_node);
            red_black_tree->size--;
            return aux;

        } else if (!rb_node->right) {  // somente esquerda
            aux = rb_node->left;
            aux->parent = rb_node->parent;
            if (rb_node->parent) {
                if (rb_node == rb_node->parent->left) {
                    rb_node->parent->left = aux;
                } else if (rb_node == rb_node->parent->right) {
                    rb_node->parent->right = aux;
                }
            } else {
                red_black_tree->root = aux;
            }
            
            fixRBdelete(red_black_tree, red_black_tree->root, rb_node);
            free(rb_node);
            red_black_tree->size--;
            return aux;

        } else if (rb_node->left && rb_node->right) {  // tem dois filhos
            aux = getLargestLeft(rb_node->left);
            rb_node->value = aux->value;
            rb_node->left = removeTree(red_black_tree, rb_node->left, aux->value);
        }
    }
    return rb_node;
}

void fixRBdelete(Tree t, Node rt, Node n) {
    Red_Black_Node *root = rt;
    Red_Black_Node *rb_node = n;
        
    while (root != rb_node && isBlack(rb_node) && root->parent) {
        Red_Black_Node *w = NULL;
 
        if (rb_node && rb_node == rb_node->parent->left) {
            w = rb_node->parent->right;

            if (w && isRed(w)) {
                paintRed(rb_node->parent);
                paintBlack(w);
                rotateLeft(t, rb_node->parent);
                w = rb_node->parent->right;
            }
            if (!w->left && !w->right) {
                paintRed(w);
                rb_node = rb_node->parent->right;

            } else if (!w->right && w->left && isBlack(w->left)) {
                paintRed(w);
                rb_node = rb_node->parent->right;

            } else if (!w->left && w->right && isBlack(w->right)) {
                paintRed(w);
                rb_node = rb_node->parent->right;
            
            } else if ((isBlack(w->left) && isBlack(w->right))) {
                paintRed(w);
                rb_node = rb_node->parent->right;
            
            } else if ((w->right && isBlack(w->right)) || !w->right) {
                if (w->left) {
                    paintBlack(w->left);
                }
                paintRed(w);
                rotateRight(t, w);
                w = rb_node->parent->right;
            }
            strcpy(w->color, rb_node->parent->color);
            paintBlack(rb_node->parent);
            if (w->right) {
                paintBlack(w->right);
            }
            rotateLeft(t, rb_node->parent);
            rb_node = root;

        } else if (rb_node && rb_node == rb_node->parent->right) {
            w = rb_node->parent->left;

            if (w && isRed(w)) {
                paintRed(rb_node->parent);
                paintBlack(w);
                rotateRight(t, rb_node->parent);
                w = rb_node->parent->left;
            }
            if (!w->left && !w->right) {
                paintRed(w);
                rb_node = rb_node->parent->left;

            } else if (!w->right && w->left && isBlack(w->left)) {
                paintRed(w);
                rb_node = rb_node->parent->left;

            } else if (!w->left && w->right && isBlack(w->right)) {
                paintRed(w);
                rb_node = rb_node->parent->left;
            
            } else if ((isBlack(w->left) && isBlack(w->right))) {
                paintRed(w);
                rb_node = rb_node->parent->left;
            
            } else if ((w->left && isBlack(w->left)) || !w->left) {
                if (w->right) {
                    paintBlack(w->right);
                }
                paintRed(w);
                rotateLeft(t, w);
                w = rb_node->parent->left;
            }
            strcpy(w->color, rb_node->parent->color);
            paintBlack(rb_node->parent);
            if (w->left) {
                paintBlack(w->left);
            }
            rotateLeft(t, rb_node->parent);
            rb_node = root;
        }

        paintBlack(rb_node);        
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