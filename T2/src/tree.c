#include "tree.h"

#include "circle.h"
#include "line.h"
#include "list.h"
#include "qry.h"
#include "rectangle.h"
#include "text.h"

struct nd {
    Info value;
    struct nd *left;
    struct nd *right;
    struct nd *center;
    double x, y;
    int crtl;
    bool removed;
};
typedef struct nd tree_node;

struct rt {
    tree_node *root;
    int size;
    int qntdRemoved;
    double LIMIAR;
};
typedef struct rt tree_root;

Tree createTree() {
    tree_root *new_tree = calloc(1, sizeof(tree_root));
    new_tree->root = NULL;
    new_tree->size = 0;
    new_tree->qntdRemoved = 0;
    new_tree->LIMIAR = 0.33;

    return new_tree;
}

Node createNode(Info value, double x, double y, int ctrl) {
    // printf("Creating new node\n");
    tree_node *new_node = calloc(1, sizeof(tree_node));
    if (new_node != NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->center = NULL;
        new_node->value = value;
        new_node->x = x;
        new_node->y = y;
        new_node->crtl = ctrl;
        new_node->removed = false;
    }
    return new_node;
}

Node insertTree(Tree root, Node node, double x, double y, Info i, int ctrl) {
    // printf("Insertion\n");
    tree_root *my_root = root;
    tree_node *my_node = node;

    // Caso base: árvore vazia
    if (!my_node) {
        my_node = createNode(i, x, y, ctrl);
        if (!my_root->root) {
            my_root->root = my_node;
        }
        if (my_node) {
            my_root->size++;
            // printf("size %d\n", my_root->size);
            return my_node;
        }
    }

    // Se o x é menor que o x da raiz,
    // inserir a esquerda
    if (x < (my_node->x)) {
        my_node->left = insertTree(root, my_node->left, x, y, i, ctrl);

        // Se o x é maior igual que o do nó porém o y é menor,
        // inserir no meio
    } else if (x >= (my_node->x) && y < (my_node->y)) {
        my_node->center = insertTree(root, my_node->center, x, y, i, ctrl);

        // Se o x é maior igual que o do nó e o y também é maior igual que o do nó,
        // inserir a direita
    } else if (x >= (my_node->x) && y >= (my_node->y)) {
        my_node->right = insertTree(root, my_node->right, x, y, i, ctrl);
    }
    return my_node;
}

Node getLeft(Node root) {
    tree_node *my_node = root;

    return my_node->left;
}

Node getRight(Node root) {
    tree_node *my_node = root;

    return my_node->right;
}

Node getCenter(Node root) {
    tree_node *my_node = root;

    return my_node->center;
}

double getTX(Node root) {
    tree_node *my_node = root;

    return my_node->x;
}

double getTY(Node root) {
    tree_node *my_node = root;

    return my_node->y;
}

int getCtrl(Node root) {
    tree_node *my_node = root;

    return my_node->crtl;
}

Node getRoot(Tree tree) {
    tree_root *my_tree = tree;

    return my_tree->root;
}

int getSize(Tree tree) {
    tree_root *my_tree = tree;

    return my_tree->size;
}

Info getInfo(Node root) {
    tree_node *my_node = root;

    return my_node->value;
}

Info searchTree(Node root, double x, double y) {
    tree_node *my_node = root;

    if (my_node == NULL) {
        return NULL;
    }

    if (my_node->x == x && my_node->y == y) {
        return my_node->value;
    }

    if (x < my_node->x) {
        return searchTree(my_node->left, x, y);

    } else if (x >= my_node->x && y < my_node->y) {
        return searchTree(my_node->center, x, y);

    } else if (x >= my_node->x && y >= my_node->y) {
        return searchTree(my_node->right, x, y);
    }
    return (my_node->value);
}

Node removeNode(Tree root, Node node, double x, double y) {
    tree_root *my_root = root;
    tree_node *my_node = node;

    if (my_node == NULL) {
        return NULL;
    }

    if (x < my_node->x) {
        my_node->left = removeNode(my_root, my_node->left, x, y);

    } else if (x >= my_node->x && y < my_node->y) {
        my_node->center = removeNode(my_root, my_node->center, x, y);

    } else if (x >= my_node->x && y > my_node->y) {
        my_node->right = removeNode(my_root, my_node->right, x, y);

    // Chegamos no nó que queremos remover
    } else if (x == my_node->x && y == my_node->y) {
        // if (!my_node->left && !my_node->right && !my_node->center) {
        //     free(my_node);
        //     my_root->size--;
        //     my_node = NULL;
        
        // } else if (my_node->left && !my_node->center && !my_node->right) {
        //     tree_node *temp = my_node;
        //     my_node = my_node->left;
        //     free(temp);   
        //     my_root->size--;
        
        // } else if (my_node->right && !my_node->left && !my_node->center) {
        //     tree_node *temp = my_node;
        //     my_node = my_node->right;
        //     free(temp);
        //     my_root->size--;
        
        // } else if (my_node->center && !my_node->left && !my_node->right) {
        //     tree_node *temp = my_node;
        //     my_node = my_node->center;
        //     free(temp);
        //     my_root->size--;

        // } else {
        //     marcaRemovido(root, my_node);
        // }

        marcaRemovido(root, my_node);
        // printf("Removing node\n");
    }
    return my_node;
}

bool getRemovedStatus(Node root) {
    tree_node *my_node = root;

    if (my_node->removed) {
        // printf("TRUE %p\n", my_node);
    }
    return my_node->removed;
}

void marcaRemovido(Tree root, Node node) {
    tree_root *my_root = root;
    tree_node *toRemove = node;

    if (toRemove->removed) {
        return;
    }

    if (toRemove != NULL) {
        toRemove->removed = true;
        // printf("elemento removido %p\n", toRemove);
        my_root->qntdRemoved++;
        if (calcFD(my_root)) {
            my_root = printLevelOrder(my_root->root);
            my_root->qntdRemoved = 0;
            printf("NEED TO FIX TREE");
        }
    }
}

bool calcFD(Tree root) {
    tree_root *my_root = root;

    double fd = my_root->qntdRemoved / my_root->size;

    if (fd >= my_root->LIMIAR) {  // precisa refazer a arvore
        return true;
    }
    return false;
}

void preOrderNodes(Lista my_list, Node root, double x1, double y1, double x2, double y2) {
    tree_node *my_root = root;
    bool check;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    // printf("value = %p\n", my_root->value);
    if (!getRemovedStatus(my_root)) {
        check = pointIsInside(my_root, x1, y1, x2, y2);
        if (check) {
            // printf("%p\n", my_root);
            insereFim(my_list, my_root, my_root->x, my_root->y);
        }
    }

    preOrderNodes(my_list, my_root->left, x1, y1, x2, y2);
    preOrderNodes(my_list, my_root->center, x1, y1, x2, y2);
    preOrderNodes(my_list, my_root->right, x1, y1, x2, y2);
}

void preOrderInfos(Lista my_list, Node root, double x1, double y1, double x2, double y2) {
    tree_node *my_root = root;
    Info fig;
    bool check;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    // printf("value = %p\n", my_root->value);
    if (!getRemovedStatus(my_root)) {
        fig = getInfo(my_root);

        switch (getCtrl(my_root)) {
            case 1:
                check = isInsideCirc(fig, x1, y1, (x2 - x1), (y2 - y1));
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            case 2:
                check = isInsideRect(fig, x1, y1, (x2 - x1), (y2 - y1));
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            case 3:
                check = isInsideLine(fig, x1, y1, (x2 - x1), (y2 - y1));
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            case 4:
                check = isInsideText(fig, x1, y1, (x2 - x1), (y2 - y1));
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            default:
                break;
        }
    }

    preOrderInfos(my_list, my_root->left, x1, y1, x2, y2);
    preOrderInfos(my_list, my_root->center, x1, y1, x2, y2);
    preOrderInfos(my_list, my_root->right, x1, y1, x2, y2);
}

void preOrderAtingidos(Lista my_list, Node root, double x1, double y1) {
    tree_node *my_root = root;
    Info fig;
    bool check;

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    // printf("value = %p\n", my_root->value);
    if (!getRemovedStatus(my_root)) {
        fig = getInfo(my_root);

        switch (getCtrl(my_root)) {
            case 1:
                check = tpCirc(fig, x1, y1);
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            case 2:
                check = tpRect(fig, x1, y1);
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            case 3:
                check = tpLine(fig, x1, y1);
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            case 4:
                check = tpTxt(fig, x1, y1);
                if (check) {
                    // printf("%p\n", my_root);
                    insereFim(my_list, my_root->value, my_root->x, my_root->y);
                }
                break;

            default:
                break;
        }
    }

    preOrderAtingidos(my_list, my_root->left, x1, y1);
    preOrderAtingidos(my_list, my_root->center, x1, y1);
    preOrderAtingidos(my_list, my_root->right, x1, y1);
}

Tree printLevelOrder(Node root) {
    tree_node *my_root = root;
    Tree new_tree = createTree();

    if (my_root == NULL) {
        printf("EMPTY TREE\n");
        exit(0);
    }

    int maxLevel = height(my_root);
    int i;
    for (i = 1; i <= maxLevel; i++) {
        printGivenLevel(my_root, new_tree, i);
    }

    freeTree(my_root);

    return new_tree;
}

void printGivenLevel(Node root, Tree new, int level) {
    tree_node *my_root = root;

    if (my_root == NULL) {
        return;
    }
    if (level == 1) {
        if (!getRemovedStatus(my_root)) {
            switch (getCtrl(my_root)) {
                case 1:
                    insertTree(new, getRoot(new), my_root->x, my_root->y, my_root->value, 1);
                    break;

                case 2:
                    insertTree(new, getRoot(new), my_root->x, my_root->y, my_root->value, 2);
                    break;

                case 3:
                    insertTree(new, getRoot(new), my_root->x, my_root->y, my_root->value, 3);
                    break;

                case 4:
                    insertTree(new, getRoot(new), my_root->x, my_root->y, my_root->value, 4);
                    break;

                default:
                    break;
            }
        }

    } else if (level > 1) {
        printGivenLevel(my_root->left, new, level - 1);
        printGivenLevel(my_root->center, new, level - 1);
        printGivenLevel(my_root->right, new, level - 1);
    }
}

int height(Node root) {
    tree_node *my_root = root;

    if (root == NULL) {
        return 0;
    }

    int lheight = height(my_root->left);
    int rheight = height(my_root->right);

    if (lheight > rheight) {
        return (lheight + 1);
    } else {
        return (rheight + 1);
    }
}

Lista getNodesDentroRegiaoXyyT(Tree t, double x1, double y1, double x2, double y2) {
    tree_root *my_root = t;
    tree_node *my_node = my_root->root;

    Lista my_listNodes = createList();

    preOrderNodes(my_listNodes, my_node, x1, y1, (x2 - x1), (y2 - y1));

    return my_listNodes;
}

bool pointIsInside(Node node, double x1, double y1, double x2, double y2) {
    tree_node *my_node = node;
    double w = x2 - x1;
    double h = y2 - y1;

    if ((x1 + w) >= (my_node->x) && (y1 + h) >= (my_node->y)) {
        if (x1 <= my_node->x && y1 <= my_node->y) {
            return true;
        }
    }
    return false;
}

Lista getInfosDentroRegiaoXyyT(Tree t, double x1, double y1, double x2, double y2) {
    tree_root *my_root = t;
    tree_node *my_node = my_root->root;

    Lista my_listInfos = createList();

    preOrderInfos(my_listInfos, my_node, x1, y1, (x2 - x1), (y2 - y1));

    return my_listInfos;
}

Lista getInfosAtingidoPontoXyyT(Tree t, double x, double y) {
    tree_root *my_root = t;
    tree_node *my_node = my_root->root;

    Lista my_listAtingidos = createList();

    preOrderAtingidos(my_listAtingidos, my_node, x, y);

    return my_listAtingidos;
}

void freeTree(Node root) {
    tree_node *my_node = root;
    int ctrl;

    if (my_node == NULL) {
        return;
    }
    ctrl = getCtrl(my_node);
    if (ctrl == 1) {
        freeCirc(my_node->value);
    } else if (ctrl == 2) {
        freeRect(my_node->value);
    } else if (ctrl == 3) {
        freeLine(my_node->value);
    } else if (ctrl == 4) {
        freeTxt(my_node->value);
    }
    freeTree(my_node->left);
    freeTree(my_node->center);
    freeTree(my_node->right);
    if (my_node) {
        free(my_node);
    }
}
