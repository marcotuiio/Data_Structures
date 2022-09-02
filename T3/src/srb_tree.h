#ifndef _SRB_Tree_H
#define _SRB_Tree_H

#include "libs.h"

/*
    Uma árvore RubroNegra espacial (SRBTree) é uma árvore Rubro-Negra que associa uma coordenada no plano (âncora)
a uma dada informação e também define o menor retângulo envolvente (minimum bounding box -- MBB) que delimita
tal informação. Tipicamente, a âncora está dentro (incluindo fronteira) da MBB.
    O MBB é definido por 2 pontos (x1,y1) e (x2,y2), diagonal que determina o retângulo envolvente: x1 <= x2 e y1 <= y2.

    A chave de busca é a coordenada da âncora.

    A ordem da chave de busca é definido como, a seguir. Sejam ch1 e ch2 duas chaves de busca.
Define-se que ch1 < ch2, se:

        * ch1.x < ch2.x
        OU
        * ch1.x == ch2.x  AND ch1.y < ch2.y

caso contrario, ch1 == ch2

    Associa-se uma precisão epsilon à árvore. Está precisão é usada para determinar quando dois números
reais (da chave de busca) devem ser considerados como iguais. Assim v == w, se |v - w| <= epsilon.

    Algumas operações de busca retorna o nó da árvore onde uma determinada informação está armazenada.
Os dados referentes a este nó podem ser obtidos por outras operações, desde que estes nos continuem
validos. Qualquer remoção posterior faz com que nos (Node) retornados previamente devam ser considerados
inválidos.
*/

typedef void (*FvisitaNo)(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
/*
 * Processa a informação i associada a um nó da árvore, cuja âncora
 * é o ponto (x,y), bounding box (mbbX1,mbbY1) -- (mbbX2,mbbY2).
 * O parametro aux aponta para conjunto de dados
 * (provavelmente um registro) que sao compartilhados entre as
 * sucessivas invocações a esta função.
 */

SRBTree createSRB(double epsilon);
/*
  Retorna uma árvore vazia, com precisão epsilon.
  Retorna NULL caso não tenha conseguido criar a árvore.
 */

Node insertSRB(SRBTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info);
/*
  Insere a informação info na árvore t, associada a coordenada (x,y), sendo delimitada pelo retângulo definido
  pela diagonal (mbbX1,mbbY1) -- (mbbX2,mbbY2).
  Retorna o nó onde foi inserida a informação; NULL, caso ja exista informação com a mesma chave (veja acima)
  inserida.
 */

Node insertBBSRB(SRBTree t, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info);
/*
 Equivalente a insertSRB(t, mbbX1, mbbY1,  mbbX1, mbbY1,  mbbX2, mbbY2,  info)
 */

void getBBPartSRB(SRBTree t, double x, double y, double w, double h, Lista resultado);
/*
  Insere na lista resultado os nos da árvore (Node) que seu retângulo envolvente possua alguma
  intersecção com a região retangula de âncora (x,y), largura w e altura h.
 */

void getBBSRB(SRBTree t, double x, double y, double w, double h, Lista resultado);
/*
 Similar a getBbPartSRB, porém seleciona apenas os nos cujos retâgulos envolventes estejam
 inteiramente dentro da região.
 */

Info getInfoSRB(SRBTree t, Node n, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);
/*
  Retorna a informação associada ao nó n, sua âncora (xa,ya) e o retângulo envolvente (mbbX1,mbbY1) -- (mbbX2,mbbY2).
  Este nó deve ser um nó valido (veja acima).
 */

Node getNodeSRB(SRBTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);
/*
  Retorna o nó da árvore associado a âncora (xa,ya) e o retângulo envolvente; NULL, se tal âncora não existir.
 */

void updateInfoSRB(SRBTree t, Node n, Info i);
/*
  Altera a informação associada ao nó n que deve ser existente e valido.
  A âncora e o MBB deste nó não sao alterados, portanto, a informação deve permanecer compativel a estes dois
valores.
 */

Info removeSRB(SRBTree t, double xa, double ya, double mbbX1, double mbbY1, double mbbX2, double mbbY2);
/*
  Remove o nó da árvore cuja chave é a coordenada (xa,ya). Qualquer nó da árvore retornado por operações anteriores
  deve ser considerado invalido.
  Retorna a informação que estava associada a tal nó (ou NULL, se não encontrado), bem como o seu retângulo envolvente.
 */

void printSRB(SRBTree t, char *nomeArq);
/*
  "Desenha" (no formato dot) a árvore no arquivo nomeArq.
  Veja: https://graphviz.org/
 */

/*
  As proximas operações percorrem a árvore em largura/profundidade/simetrico.
  Invoca a função fVisita (veja descrição acima) em cada nó visitado
 */

void percursoLargura(SRBTree t, FvisitaNo fVisita, void *aux); // levelOrder

void percursoSimetrico(SRBTree t, FvisitaNo fVisita, void *aux); // inOrder

void percursoProfundidade(SRBTree t, FvisitaNo fVisita, void *aux); // preOrder

void killSRB(SRBTree t);
// Libera a memoria alocada para a árvore.

// DELETAR FUNÇÕES DE TESTE
// Node preOrder(Node n);
// Node getRoot(SRBTree t);

#endif