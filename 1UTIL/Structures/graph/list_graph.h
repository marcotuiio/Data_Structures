#include "- UTIL/libs.h"
#include "list.h"

#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

void* createGraph(int n);

void destroyGraph(void* g);

void addEdge(void* g, int v1, int v2);

void removeEdge(void* g, int v1, int v2);

bool hasEdge(void* g, int v1, int v2);

void printGraph(void* g);

#endif