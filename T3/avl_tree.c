#include "avl_tree.h"

struct node {
    Info value;
    struct node* left;
    struct node* right;
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
    void* x;
    if (!avl_tree->root) {
        avl_tree->root = new_node;
        return;
    }

    if (i < avl_node->value) {
        new_node->left = insertTree(avl_tree, new_node->left, i);
        if (height(new_node->left) - height(new_node->right) > 2) {
            if (i < new_node->left->value) {
                x = rotateLeft(new_node);
            } else {
                x = rotateLeftRight(new_node);
            }
        }
    
    } else if (i > avl_node->value) {
        new_node->right = insertTree(avl_tree, new_node->right, i);
    
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

int getBalance(Node n) {
    Avl_Node *node = n;
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

