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

Tree createNode(Info value);
/*
* Insere a informação i, associada à âncora (x,y) na árvore t.
* Retorna um indicador do nó inserido.
*/

void setLeft(Tree root, Tree toLeft);

void setRight(Tree root, Tree toRight);

Tree getLeft(Tree root);

Tree getRight(Tree root);

void removeNode(Tree node);

void printTree(Tree root);

void freeTree(Tree root);
/*
* Percorre toda a árvore, realizando a liberação da memória ocupada
*/

//void percursoLargura(Tree root);
//void percursoProfundidade(Tree root);

#endif
