#include "libs.h"

#ifndef DIGRAPH_H
#define DIGRAPH_H

/*
Um Grafo Direcionado (Digraph) G é constituído por um conjunto de vértices V e
um conjunto de arestas E, denotado por G=(V,E).

Pode-se associar um dado (tipo Info) a arestas e a vertices de G.
Os nomes dos vértices são valores inteiros entre $0$ e |V|-1. É possível
associar nomes simbolicos a vertices e referencia-los através desses nomes.
Existem tres formas de fazer tal associacao: setNodeName associa explicitamente um nome a um no identificado
por seu numero; addVertex e addVertices associam nomes a vertices ainda nao nomeados (sem associacao explicita
ao seu numero).

Arestas de um grafo podem ser temporariamente desabilitadas. Uma aresta quando desabilitada parece ter
sido removida (ou seja, parece nao existir no grafo). Porem, as informacoes associadas a tal aresta
sao mantidas (apesar de inacessiveis). Posteriormente, a aresta pode ser habilitada novamente, retornando
ao estado que estava antes da desabilitacao.

Um grafo pode ser clonado por meio de 3 operacoes: cloneOnlyVertices, cria um novo grafo contendo apenas copias dos
vertices do grafo original; cloneOnlyEnabled, clona os vertices e as arestas habilitadas (ou seja, o novo grafo nao
contem nenhuma aresta desabilitada); cloneAll, clona todos os vertices e arestas do grafo.

O modulo tambem oferece duas operacoes de percurso sobre o grafo: busca em largura (bfs) e busca em profundidade (dfs).
Estes percursos tem por parametros funcoes que sao invocadas quando arestas do grafo sao "descobertas"
durante o percurso. Caso alguma dessas funcoes retornar TRUE, o percurso é interrompido.
*/

/*
  "e" é a aresta "descoberta"/"percorrida"/"classificada". td é o tempo da descoberta (quando pintado de cinza).
  tf e' tempo de finalizacao (quando pintado de preto).
*/
typedef bool (*procEdge)(Digraph g, Edge e, int td, int tf, void *extra);

typedef bool (*dfsRestarted)(Digraph g, void *extra);

/*
   Cria um grafo orientado contendo "nVert" vertices.
*/
Digraph createGraph(int nVert);

/*
   Cria um novo grafo contendo apenas copias dos vertices de g.
   Caso o vertice original contenha uma informacao e keepInfo for TRUE, a informacao é
   copiada para o novo vértice.
*/
Digraph cloneOnlyVertices(Digraph g, bool keepInfo);

/*
   Dado g=(V,E), produz G'=(V,E'), tal que, e'=(u,v) eh aresta de E', se e=(u,v) eh aresta de E
   e e esta' habilitada.
   Se keepInfo = TRUE, copia também as informaçoes associadas aos vertices e arestas clonados.
*/
Digraph cloneOnlyEnabled(Digraph g, bool keepInfo);

/*
   Cria uma copia exata do grafo g.
   Se keepInfo = TRUE, copia também as informaçoes associadas aos vertices e arestas clonados
*/
Digraph cloneAll(Digraph g, bool keepInfo);

/*
   Associa o nome "nome" ao vertice n. Substitui o nome pre-existente.
   O vertice n deve ser um vertice existente em G.
*/
void setNodeName(Digraph g, Node n, char *nome);

/*
   Associa nNomes contidos no vetor nomes a vertices de g.
   nNomes deve ser menor ou igual ao numero de vertices do
   grafo g (idealmente, deve ser igual)
*/
void addVerticesNames(Digraph g, char *nomes[], int nNomes);

/*
   Retorna no' cujo de nome e' "nome". Retorna -1, caso o nao
   exista no com o nome especificado.
*/
Node getNode(Digraph g, char *nome);

/*
   Retorna informacao associada ao no' node.
   node deve ser um no' existente no grafo.
*/
InfoNode getNodeInfo(Digraph g, Node node);

/*
   Atribui ao no' "node" a informacao "info"
*/
void setNodeInfo(Digraph g, Node node, InfoNode info);

/*
   Adiciona a aresta (from,to) ao grafo. Atribui
   a informacao info `a aresta.
*/
Edge addEdge(Digraph g, Node from, Node to, InfoEdge info);

/*
   Retorna a aresta (from,to). Se a aresta não existe,
   retorna NULL.
*/
Edge getEdge(Digraph g, Node from, Node to);

/*
   Retorna o no' de origem na aresta "e".
*/
Node getFromNode(Digraph g, Edge e);

/*
   Retorna o no' de destino da aresta "e".
*/
Node getToNode(Digraph g, Edge e);

/*
   Retorna a informacao associada 'a aresta "e".
   A informacao deve ter sido anteriormente associada 'a
   aresta pela operacao setEdgeInfo.
*/
InfoEdge getEdgeInfo(Digraph g, Edge e);

/*
   Associa a informacao "info" 'a aresta "e".
 */
void setEdgeInfo(Digraph g, Edge e, InfoEdge info);

/*
   Dado g=(V,E) tal que "e" pertence a E,
   retira "e" de E (E = E - {e}).
*/
void removeEdge(Digraph g, Edge e);

/*
   Desabilita a aresta "e".
   A aresta "e" deve existir no grafo g.
 */
void disableEdge(Digraph g, Edge e);

/*
   Reabilita a aresta "e" (que supostamente foi anteriormente
   desabilitada.
*/
void enableEdge(Digraph g, Edge e);

/*
   Reabilita todas as aresta do grafo que, por ventura,
   tenham sido desabilitadas.
*/
void enableAllEdges(Digraph g);

/*
   Retorna verdadeiro, se a aresta "e" esteja desabilitada;
   falso, caso contrario.
*/
bool isDisabled(Digraph g, Edge e);

/*
   Libera a memoria utilizada para armazenar dados sobre
   a aresta "e".
   ATENCAO: não remove a aresta do grafo
*/
void delEdge(Edge e);

/*
   Retorna verdadeiro se existe a aresta (from,to)
   no grafo g; falso, caso contrario.
*/
bool isAdjacent(Digraph g, Node from, Node to);

/*
   Adiciona 'a lista "nosAdjacentes" os nos adjacentes ao no "node".
*/
void adjacentNodes(Digraph g, Node node, Lista nosAdjacentes);

/*
   Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que,
   x == node.
*/
void adjacentEdges(Digraph g, Node node, Lista arestasAdjacentes);

/*
   Insere na lista "nomesNodes" os nomes atribuidos aos nos do grafo.
*/
void getNodeNames(Digraph g, Lista nomesNodes);

/*
   Insere na lista "arestas", as arestas (Edge) do grafo g.
*/
void getEdges(Digraph g, Lista arestas);

/*
   Faz percurso em profundidade sobre o grafo g, classificando as arestas do grafo em
   aresta de árvore, aresta de avanço, de retorno e cruzada. No momento da classificação,
   a respectiva funcao é invocada (caso nao seja NULL).
   "extra" e' um apontador que pode ser usado por qualquer uma das funcoes.
   A busca em profundidade, eventualmente, pode produzir uma floresta. Neste caso,
   a função newTree é invocada sempre que o percurso for retomado.
*/
bool dfs(Digraph g, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra);

/*
   Percorre o grafo g em largura. Invoca a funcao discoverNode (se != NULL)
   para a aresta (x,y) usada para "descobrir" o no' y.
*/
bool bfs(Digraph g, procEdge discoverNode, int start);

/*
   Libera a memoria utilizada no grafo
*/
void killGraph(Digraph g);

#endif
