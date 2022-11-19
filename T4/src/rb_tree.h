#ifndef _RB_Tree_H
#define _RB_Tree_H

#include "libs.h"

/*
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
typedef void (*FvisitaNo)(InfoRb i, void *aux);

Rb createRB(double epsilon);
/*
  Retorna uma árvore vazia, com precisão epsilon.
  Retorna NULL caso não tenha conseguido criar a árvore.
*/

RbNode insertRB(Rb t, double x, double y, InfoRb info);
/*
  Insere a informação info na árvore t, associada a coordenada (x,y),
  Retorna o nó onde foi inserida a informação; NULL, caso ja exista informação com a mesma chave (veja acima)
  inserida.
 */


InfoRb getInfoRB(RbNode n);
/*
  Retorna a informação associada ao nó n, sua âncora (xa,ya).
  Este nó deve ser um nó valido (veja acima).
*/

void setInfoRB(RbNode n, InfoRb info);
/*
  Associa a informação info ao nó n.
  Este nó deve ser um nó valido (veja acima).
*/

RbNode getNodeRB(Rb t, double xa, double ya);
/*
  Retorna o nó da árvore associado a âncora (xa,ya); NULL, se tal âncora não existir.
*/

InfoRb removeRB(Rb t, double xa, double ya);
/*
  Remove o nó da árvore cuja chave é a coordenada (xa,ya). Qualquer nó da árvore retornado por operações anteriores
  deve ser considerado invalido.
  Retorna a informação que estava associada a tal nó (ou NULL, se não encontrado).
*/

void percursoLargura(Rb t, FvisitaNo fVisita, void *aux);  // levelOrder

void percursoProfundidade(Rb t, FvisitaNo fVisita, void *aux);  // preOrder

void killRB(Rb t);
// Libera a memoria alocada para a árvore.

#endif