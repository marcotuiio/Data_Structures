#include "list_graph.h"

int main () {
    void *graph = createGraph(5);
    
    printf("==> Grafo inicial\n");
    insertEdge(graph, 0, 1);
    insertEdge(graph, 0, 4);
    insertEdge(graph, 1, 2);
    insertEdge(graph, 1, 3);
    insertEdge(graph, 1, 4);
    insertEdge(graph, 2, 3);
    insertEdge(graph, 3, 4);
    insertEdge(graph, 4, 1);
    insertEdge(graph, 3, 2);
    printTerminal(graph);
    bfsTraverse(graph, 0);

    printf("\n==> Depois da remoção\n");
    removeEdge(graph, 1, 3);
    printTerminal(graph);

    printGraph(graph);

    killGraph(graph);

    return 0;
}