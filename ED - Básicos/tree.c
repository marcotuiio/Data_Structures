#include "tree.h"

struct nd {
    Info value;
    struct nd *left;
    struct nd *right;
};
typedef struct nd tree_node;

Tree createNode(Info value) {
    tree_node *new_node = calloc(1, sizeof(tree_node));
    if(new_node != NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = value;
    }
    return new_node;
}

void setLeft(Tree root, Tree toLeft) {
    tree_node *my_root = root;
    tree_node *my_child = toLeft;

    my_root->left = my_child;
}

void setRight(Tree root, Tree toRight) {
    tree_node *my_root = root;
    tree_node *my_child = toRight;

    my_root->right = my_child;
}

void printTree(Tree root) {
    tree_node *my_root = root;

    if(my_root == NULL) {
        printf("EMPTY TREE\n");
        return;
    }

    printf("value = %d\n", my_root->value);
    printf("\nleft -- ");  
    printTree(my_root->left);
    printf("\nright -- ");  
    printTree(my_root->right);
    printf("\ndone\n");
}