#include "hash_table.h"

typedef struct person {
    char name[MAX_NAME_LENGTH];
    int age;
    struct person *next;
} person;

person *hash_table[TABLE_SIZE];

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

        } else {
            printf("\t%i\t", i);
            person *tmp = hash_table[i];
            while (tmp) {
                printf("%s | \t", tmp->name);
                tmp = tmp->next;
            }
            printf("\n"); 
        }
    }
    printf("\tEnd\n");
}

void *createPerson(char *name, int age) {
    person *new_person = calloc(1, sizeof(person));
    strcpy(new_person->name, name);
    new_person->age = age;
    new_person->next = NULL;
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
    new_person->next = hash_table[index];
    hash_table[index] = new_person;
    return true;
}

void *searchTable(char *name) {
    int index = hash(name);

    person *tmp = hash_table[index];

    while (tmp && strcmp(tmp->name, name) != 0) {
        tmp = tmp->next;
    }
    return tmp;
}

void removeTable(char *name) {
    int index = hash(name);

    person *tmp = hash_table[index];
    person *prev = NULL;

    while (tmp && strcmp(tmp->name, name) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp) {
        return;
    }
    if (!prev) { // deleting first element
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    free(tmp);
}

void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != NULL) {
            free(hash_table[i]);
        }
    }
}