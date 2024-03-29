#include "/home/marcotuiio/Data_Structures/1UTIL/libs.h"

#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

void* createGraph(int n);

void insertEdge(void* g, int v1, int v2);

void removeEdge(void* g, int v1, int v2);

bool hasEdge(void* g, int v1, int v2);

void printGraph(void* g);

void printTerminal(void *g);

void dfsTraverse(void *g, int start);

void bfsTraverse(void *g, int start);

void killGraph(void* g);

#endif