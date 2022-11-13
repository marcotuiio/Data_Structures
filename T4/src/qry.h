#include "libs.h"
#include "infos.h"
#include "digraph.h"
#include "rb_tree.h"
#include "svg.h"

#ifndef QRY_H
#define QRY_H

void readQry(Rb t, Digraph d, char *bedQry, char *bsdSvg, char *bsdTxt);
// Função que lê o arquivo de consulta e define a execução das funções especificas

FILE *openQry(char *bedQry);
// Função que abre o arquivo de consulta.

FILE *openTxt(char *bsdTxt);
// Função que abre o arquivo de texto.

void oFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
void lookCep(InfoRb i, void *aux);
// Armazena a posição geográfica do endereço cep/face/num

void catac(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
void catacQuadras(InfoRb i, void *aux);
bool catacEdges(Digraph g, Edge e, int td, int tf, void *extra);
// Remover as quadras contidas na região delimitada pelo retângulo x,y,w,h. Arestas
// incidentes em vértices dentro do retângulo especificado devem ser removidas.4

void pnt(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
// Modifica as cores de preenchimento e de borda da quadra identificada por cep para cfill e cstrk.

void blq(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
// Bloqueia o fluxo num determinado sentido (ou seja, desabilita a aresta) em todas arestas que se
// originarem num vértice dentro da região retangular especificada. Os possíveis valores de
// sentido são: ns (bloqueia arestas no sentido norte=>sul); sn (bloqueia sentido sul=>norte),
// lo (bloqueia leste=>oeste), ol (bloqueia oeste=>leste)

void rbl(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
// Desbloqueia as arestas que foram bloqueadas por um comando blq anterior de mesmo nome.

void rf(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
// Faz percurso em profundidade no mapa viário classificando as arestas conforme classificação
// usual. As arestas cruzadas devem ser consideradas como “pontes” entre regiões
// parcialmente inacessíveis. A velocidade máxima de tais arestas devem ser multiplicadas pelo fator
// do parâmetro.

void bFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
// Faz o percurso em largura no grafo, a partir do nó mais próximo da coordenada (x,y), multiplicando
// a velocidade média pelo fator especificado.

void pFunc(FILE *qry, FILE *txt, FILE *svg, Rb t, Digraph d);
// Determina o melhor trajeto entre a origem (@o) e o destino especificado pelo endereço
// cep/face/num. O percurso na representação pictórica deve indicar o trajeto mais curto na cor
// cmc e o trajeto mais rápido com a cor cmr.

#endif