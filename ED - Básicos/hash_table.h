#include "libs.h"

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 10
#define MAX_NAME_LENGTH 20

unsigned int hash(char *key);
void createTable();
void printTable();
void *createPerson(char *name, int age);
char *getName(void *p);
bool insertTable(void *p);
void *searchTable(char *name);
void removeTable(char *name);
void freeTable();

#endif