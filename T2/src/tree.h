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
/*
* Cria uma árvore vazia e retorna um ponteiro para ela
*/

Node createNode(Info value, double x, double y, int ctrl);
/*
* Insere a informação i, associada à âncora (x,y) na árvore t.
* Retorna um indicador do nó inserido.
*/

Node insertTree(Tree root, Node node, double x, double y, Info i, int ctrl);

Node getLeft(Node root);

Node getRight(Node root);

Node getCenter(Node root);

int getCtrl(Node root);

Node getRoot(Tree tree);

int getSize(Tree tree);

void setInfo(Node root, Info i, double x, double y);

Info getInfo(Node root);

Info searchTree(Node root, double x, double y);

bool removeNode(Tree root, Node node);
bool marcaRemovido(Tree root, Node node);
/*
* Marca como removido o no' n. Caso, apos a remocao, o fator de degradacao
* superar o limiar definido na criacao, a arvore e' recriada sem os no's delidos.
*/

void fixTree(Tree root);
void reinsert(Tree root, Node valid[15], int ult);
/*
* Funções complemetares que devem receber uma arvóre Xyy, percorrem todos os
* nós dela e a organizam, removendo os nós removidos por comandos anteriores
* e montando uma nova árvore consideravelmente melhor e mais distribuida
*/


void printTree(Tree root);

Node postOrder(Node root);

void percursoProfundidadeAux(Node root, char* buffer, int depth);
void percursoProfundidade(Tree root);
// Funções complementares, que percorrem a árvore em profundidade,
// começando por um indice 0;

void quicksort (double *arr, int left, int right);
// Recebe um vetor de informações arr, a posição do primeiro elemento
// e a posição do ultimo elemento

void freeTree(Tree root);
// Percorre toda a árvore, realizando a liberação da memória ocupada

//void percursoLargura(Tree root);

#endif
