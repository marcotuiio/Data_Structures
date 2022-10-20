#include "digraph.h"

typedef struct StNode {
    Lista adjacentes;
    InfoNode info;
} StNode;

typedef struct Digraph {
    StNode *nodes;
    Hashtable nodeNames;
} Digraph;

typedef struct StEdge {
    bool habilitada;
    double peso;
    Node adjacentes;
    InfoEdge info;
} StEdge;