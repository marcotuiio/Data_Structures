#include "list_graph.h"

int main () {
    void *graph = createGraph(6);
    
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
    insertEdge(graph, 4, 5);
    insertEdge(graph, 5, 5);
    printTerminal(graph);

    printf("\n==> Teste DFS\n");
    dfsTraverse(graph, 3);

    printf("\n\n==> Teste BFS\n");
    bfsTraverse(graph, 0);

    printf("\n==> Depois da remoção\n");
    removeEdge(graph, 1, 3);
    printTerminal(graph);

    printGraph(graph);

    killGraph(graph);

    return 0;
}