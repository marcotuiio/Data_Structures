#include "libs.h"
// #include "avl_tree.h"
#include "hash_table.h"

int main () {
    // Tree t = newTree();
    // void *aux = NULL;

    // insertTree(t, getRoot(t), 10);
    // insertTree(t, getRoot(t), 11);
    // insertTree(t, getRoot(t), 8);
    // insertTree(t, getRoot(t), 14);
    // insertTree(t, getRoot(t), 7);
    // insertTree(t, getRoot(t), 16);
    // insertTree(t, getRoot(t), 12);
    // insertTree(t, getRoot(t), 102);
    // insertTree(t, getRoot(t), 105);
    // insertTree(t, getRoot(t), 1);

    // printf("\n");
    // traversePreOrder(t, print, aux);
    // printf("\n");
    // removeNode(t, getRoot(t), 10);
    // traversePreOrder(t, print, aux);
    // printf("\n");

    // freeTree(t);

    createTable();
    void *p = createPerson("Marcus", 256);
    insertTable(p);
    void *p2 = createPerson("Bia", 27);
    insertTable(p2);
    void *p3 = createPerson("Jordan", 14);
    insertTable(p3);
    void *p4 = createPerson("Tausio", 17);
    insertTable(p4);
    void *p5 = createPerson("Eliza", 48);
    insertTable(p5);
    void *p6 = createPerson("Sarah", 32);
    insertTable(p6);
    void *p7 = createPerson("Kate", 1);
    insertTable(p7);
    void *p8 = createPerson("John", 2);
    insertTable(p8);
    void *p9 = createPerson("Paul", 3);
    insertTable(p9);
    void *p10 = createPerson("Robert", 98);
    insertTable(p10);
    printTable();
    
    void *p11 = createPerson("Jose", 256);
    insertTable(p11);
    void *p12 = createPerson("Dream", 102928392);
    insertTable(p12);
    void *p13 = createPerson("Hiccup", 64);
    insertTable(p13);

    void *tmp = searchTable("George");

    if (tmp) {
        printf("\nFound %s\n", getName(tmp));
    } else {
        printf("\nNot found\n");
    }

    removeTable("Marcus");
    printTable();
    freeTable();

    return 0;
}