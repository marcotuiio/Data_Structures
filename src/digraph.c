#include "digraph.h"

// typedef struct no {
//   int vertex;
//   struct node* next;
// }NodeLocal;
// struct node* createNode(int);

typedef struct Graph {
  int numVertices;
  List *adjacents;
}graphLocal;

// // Cria no
// Node createNode(Node no,int v) {
//     NodeLocal *newNode;
//     newNode = malloc(sizeof(newNode));
//     newNode->vertex = v;
//     newNode->next = NULL;
//     return newNode;
// }

// Cria grafo
Digraph createGraph(int vertices) {
    graphLocal *graph = malloc(sizeof(graphLocal));

    graph->numVertices = vertices;
    graph->adjacents = malloc(vertices*sizeof(List));

    int i;
    for (i = 0; i < vertices; i++)
      graph->adjacents[i] = criaLista();

    return graph;
}

// Add aresta
Edge addEdge(Digraph g, Node from, Node to, InfoEdge info) {
    graphLocal *grafo = g;
    Edge e;
    if (grafo->adjacents[from] != NULL) {
      e = insertAresta(grafo->adjacents[from], info, from, to);
    }
    return e;
}

void setNodeName(Digraph g, Node n, char *nome) {
  graphLocal *grafo = g;
  setNomeVert(grafo->adjacents[n], nome);
}

void setNodeInfo(Digraph g, Node node, InfoNode info) {
  graphLocal *grafo = g;
  setInfoVert(grafo->adjacents[node], info);
}

InfoNode getNodeInfo(Digraph g, Node node) {
  graphLocal *grafo = g;
  return getInfoVert(grafo->adjacents[node]);
}

Node getFromNode(Digraph g, Edge e) {
  
  return getArestaFrom(e);
}

Node getToNode(Digraph g, Edge e) {
  
  return getArestaTo(e);
}

Node getNode(Digraph g,  char *nome){
  graphLocal *grafo = g;
  int i;
  for(i=0; i < grafo->numVertices; i++){
    if (strcmp(nome, getNomeVert(grafo->adjacents[i])) == 0){
      return i; 
    }
  }
  return -1;
  
}

Edge getEdge(Digraph g, Node from, Node to) {

  graphLocal* grafo = (graphLocal*) g;
  Edge aresta = searchEdge(grafo->adjacents[from], from, to);
  return aresta;
}

// void printGraph(Digraph g) {
//   graphLocal *grafo = g;
//   FILE *arq = fopen("grafoDot.dot", "w");

//   fprintf(arq, "digraph G {");
//   fprintf(arq, "\n\tnode [fontcolor=black style=filled]");
//   fprintf(arq, "\n\tedge [fontcolor=grey fontsize=12]\n\n");

//   for (Node aux = 0; aux < grafo->numVertices; aux++) {
//     fprintf(arq, "\tnode [label=%d] %d\n", getInfoVert(grafo->adjacents[aux]), getInfoVert(grafo->adjacents[aux]));
//   }

//   for (Node i = 0; i < grafo->numVertices; i++) {
//     for (Edge arestas = getInicio(grafo->adjacents[i]); arestas; arestas = getNext(arestas)) {
//       int info = getInfoVert(grafo->adjacents[getArestaTo(arestas)]);
//       fprintf(arq, "\t%d -> %d;\n", getInfoVert(grafo->adjacents[i]), info);
//     } 
//   }

//   fprintf(arq, "\n}");
//   fclose(arq);

// }

/* Digraph cloneOnlyVertices(Digraph g, bool keepInfo) {

    graphLocal* g 
}
 */