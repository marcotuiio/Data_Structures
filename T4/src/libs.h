#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#ifndef LIBS_H
#define LIBS_H

typedef void* Paths;
typedef void* Controller;

typedef void *Digraph;
typedef int Node;    // posição no grafo
typedef void *Edge;
typedef void* InfoNode;
typedef void* InfoEdge;

typedef void *Lista;

typedef void *Queue;

typedef void *PQueue;
typedef void *PInfo;
typedef void *Chave;

typedef void *AvlNode;
typedef void *Avl;
typedef void *InfoAvl;    

#define CIRCLE "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"55%%\" />\n"
#define RECTANGLE "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"45%%\" stroke-width=\"1.1%%\" />\n"
#define LINE "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" />\n"
#define TEXT "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"60%%\" ><![CDATA[%s]]></text>\n"

// HEADER FILE AUXILIAR PARA IMPORTS DE LIBS DO C;
// Usado também para realizar typedefs de void*;
// Deve ser importado em TODOS os .h do projeto!

#endif
