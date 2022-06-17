#include "libs.h"

#ifndef TREE_H
#define TREE_H

/*
* Uma árvore Xyy é uma árvore ternária, espacial, não balanceada. 
* A cada nó r da árvore é associado um ponto de 2 dimensões (r.x e r.y) denominado âncora 
* do nó e uma informação relacionada tal ponto. 
* Um nó divide o plano em 3 regiões, associadas a três subárvores:
* 
*  - sub-árvore esquerda (se) contém nós (d) cujas coordenadas x (d.x) são estritamente
*    menores que a coordenada x de r, ou seja: d.x < r.x
*  - sub-árvore mediana (sm): (d.x >= r.x) & (d.y < r.y)
*  - sub-árvore direita (sd): (d.x >= r.x) & (d.y >= r.y)
* 
* A árvore implementa 2 percursos: em largura e em profundidade. Tais percursos recebem
* como parâmetro uma função que processa a informação associada ao nó visitado.
* 
* Também são providas operações de seleção espacial. A primeira seleciona os nós da
* árvore cujas âncoras são internas a uma região retangular. A segunda seleciona os
* nós da árvore cujas informações associadas podem ser consideradas internas a uma
* região retangular. Esta operação recebe por parâmetro uma função que decide se 
* tal informação é considerada (ou não) interna. A terceira, similarmente, seleciona os nós 
* da árvore cujo um dado ponto é interno à informação associada ao nó.
* 
* Nós removidos não são desalocados imediatamente, mas apenas marcados como delidos.
* Eventualmente, a árvore é re-criada sem os nós removidos. Isto ocorre quando o
* fator de degradação fd = #removidos/#total_nós > limiar. 
* Este limiar é definido no momento da criação da árvore.
*/

Tree createTree();
// Cria uma árvore vazia e retorna um ponteiro para ela

Node createNode(Info value, double x, double y, int ctrl);
// Insere a informação i, associada à âncora (x,y) na árvore t.
// Retorna um indicador do nó inserido.

Node insertTree(Tree root, Node node, double x, double y, Info i, int ctrl);

Node getLeft(Node root);
// Recebe um nó de uma árvore e retorna o filho esquerdo desse nó
// Se o nó recebido for uma folha, retorna nulo

Node getRight(Node root);
// Recebe um nó de uma árvore e retorna o filho direito desse nó
// Se o nó recebido for uma folha, retorna nulo

Node getCenter(Node root);
// Recebe um nó de uma árvore e retorna o filho central desse nó
// Se o nó recebido for uma folha, retorna nulo

double getTX(Node root);
// Recebe um nó de uma árvore e retorna o valor de X
// do respectivo nó

double getTY(Node root);
// Recebe um nó de uma árvore e retorna o valor de Y
// do respectivo nó

int getCtrl(Node root);
// Recebe um nó de uma árvore e retorna o valor da unidade de controle
// do respectivo nó

Node getRoot(Tree tree);
// Recebe uma árvore e retorna o nó referente a raiz dessa árvore

int getSize(Tree tree);
// Recebe uma árvore e retorna a quantidade de elementos que essa aŕvore
// está armazenando

Info getInfo(Node root);
// Recebe um nó e retorna a informação armazenada nesse nó

Info searchTree(Node root, double x, double y);
// Recebe um nó de uma árvore (na primeira chamada esse nó deve ser a raiz), um x
// e um y a serem procurados na árvore. 

Node removeNode(Tree root, Node node, double x, double y, int id);
// Recebe a aŕvore e um nó dessa árvore, um x e um y referente ao nó
// que deve ser deletado da árvore. Se o nó a ser deletado possui mais de um filho, 
// a função marca removido é ativada
int analyseNode(Node root);

bool getRemovedStatus(Node root);
// Recebe um nó e retorna o status de remoção do respectivo nó

void markRemoved(Tree root, Node node);
// Marca como removido o nó node. Caso, após a remoção ativa-se a função calcFD e se
// o fator de degradação superar o limiar definido na criação, a árvore deve ser recriada.

bool calcFD(Tree root);
// Recebe uma árvore e analisa se o fator de degradação dessa árvore
// supera o limiar definido na criação. Retorna verdadeiro se supera.

// void fixTree(Tree root);
// void reinsert(Tree root, Node valid[15], int ult);
// Funções complemetares que devem receber uma arvóre Xyy, percorrem todos os
// nós dela e a organizam, removendo os nós removidos por comandos anteriores
// e montando uma nova árvore consideravelmente melhor e mais distribuida

// percurso em profundidade (pre order)
void preOrderNodes(Lista my_list, Node root, double x1, double y1, double x2, double y2);
void preOrderInfos(Lista my_list, Node root, double x1, double y1, double x2, double y2);
// Recebe um nó (na primeira chamada esse nó desse ser a raiz da árvore)
// e percorre todos os nós

// percurso em largura
Tree rebuildTree(Node root);
void rebuildGivenLevel(Node root, Tree new, int level);
int height(Node root);
// funções complementaras que dada uma árvore, 
// imprimem os nós em nível, começando por um indice 0;

// Nesses funções, os pontos formam um retângulo
Lista getNodesDentroRegiaoXyyT(Tree t, double x1, double y1, double x2, double y2);
// Retorna uma lista dos nós da árvore t cujas ancoras estao dentro da região delimitada pelos
// pontos (x1,y1) e (x2,y2) 
bool pointIsInside(Node node, double x1, double y1, double x2, double y2);

Lista getInfosDentroRegiaoXyyT (Tree t, double x1, double y1, double x2, double y2);
// Retorna um lista dos nos cujas respectivas informacoes associadas estao dentro da regiao
// delimitada pelos pontos (x1,y1) e (x2,y2). A funcao f é usada para determinar se uma informacao
// armazenada na arvore esta' dentro da regiao.
// Retorna uma lista vazia, caso não existam informacoes internas.
 
Lista getInfosAtingidoPontoXyyT (Tree t, double x, double y);
// Retorna uma lista dos nos para os quais o ponto (x,y) possa ser considerado
// interno 'as  informacoes associadas ao nó. A funcao f e' invocada para determinar
// se o ponto (x,y) é interno a uma informacao especifica.

void freeTree(Node root);
// Percorre toda a árvore, realizando a liberação da memória ocupada

#endif
