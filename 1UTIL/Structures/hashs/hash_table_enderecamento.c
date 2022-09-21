#include "hash_table.h"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
} person;

person *hash_table[TABLE_SIZE];

#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFUL )

unsigned int hash(char *key) {
    int len = strlen(key);
    unsigned int hash_value = 0;
    for (int i = 0; i < len; i++) {
        hash_value += key[i];
        hash_value = hash_value * key[i] % TABLE_SIZE;
    }
    return hash_value;
}

void createTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void printTable() {
    printf("\tStart\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!hash_table[i]) {
            printf("\t%i\t---\n", i);

        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t <deleted>\n", i);

        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("\tEnd\n");
}

void *createPerson(char *name, int age) {
    person *new_person = calloc(1, sizeof(person));
    strcpy(new_person->name, name);
    new_person->age = age;
    return new_person;
}

char *getName(void *p) {
    person *new_person = p;
    return new_person->name;
}

bool insertTable(void *p) {
    person *new_person = p;
    if (!p) {
        return false;
    }

    int index = hash(new_person->name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (!hash_table[try] || hash_table[try] == DELETED_NODE) {  // Empty slot
            hash_table[try] = new_person;
            return true;
        }
    }
    return false;
}

void *searchTable(char *name) {
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;

        if (!hash_table[try]) {
            return NULL;
        } 
        if (hash_table[try] == DELETED_NODE) continue;

        if (hash_table[try]) { // Non-empty slot
            if (!strcmp(hash_table[try]->name, name)) { // Found
                return hash_table[try];
            }
        }
    }
    return NULL;
}

void removeTable(char *name) {
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;

        if (!hash_table[try]) {
            return;
        } 
        if (hash_table[try] == DELETED_NODE) continue;

        if (hash_table[try]) { // Non-empty slot
            if (!strcmp(hash_table[try]->name, name)) { // Found
                free(hash_table[try]);
                hash_table[try] = NULL;
                return;
            }
        }
    }
}

void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != NULL) {
            free(hash_table[i]);
        }
    }
}