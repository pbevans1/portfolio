#include "hashTable.h"

#ifndef __HASHTABLE__C
#define __HASHTABLE__C

hashTable* newTable() {
    hashTable* new = malloc(sizeof(hashTable));
    new->size = 0;
    new->capacity = 30;
    new->contents = malloc(sizeof(void*) * new->capacity);
    for (int i = 0; i < new->capacity; i++) {
        new->contents[i] = NULL;
    }
    return new;
}

void insertEntry(hashTable* table, entry* new) { 
    if (table->size * 10 > table->capacity * 7) {
        doubleEntryTable(table);
    }
    unsigned long hash = hashEntry(new);
    int key = hash % table->capacity;
    while(table->contents[key] != NULL) {
        entry* currentEntry = (entry*) table->contents[key];
        if(currentEntry->isDeleted) {
            break;
        }
        key = (key + 1) % table->capacity;
    }
    table->contents[key] = new;
}

unsigned long hashEntry(entry* new) {
    // FIXME
    return 1;
}

void doubleEntryTable(hashTable* table) {
    table->capacity *= 2;
    table->size = 0;
    void** temp = table->contents;
    table->contents = malloc(sizeof(void*) * table->capacity);
    for(int i = 0; i < (table->capacity / 2); i++) {
        if (temp[i] != NULL) {
            entry* current = (entry*) temp[i];
            if (current->isDeleted) continue;
            insertEntry(table, current);
        }
    }
    free(temp);
}

hashTable* servingTableFrom(vector* src) {
    hashTable* table = malloc(sizeof(hashTable));
    table->size = 0;
    // table->size = src->size;
    table->capacity = src->size;
    table->contents = malloc(sizeof(Serving*) * table->capacity);
    Serving* currentServing;
    while((currentServing = (Serving*) popFromVec(src))) { 
        insertServingHash(table, hashServing(currentServing), currentServing);
    }
    return table;
}

void insertServingHash(hashTable* table, unsigned long hash, Serving* node) {
    // If hash table is at 70% load factor, expand
    if(((table->size * 100) / 70) >= table->capacity) { //FIXME: table won't double without this
    // if(((table->size * 100) / 95) >= table->capacity) { //FIXME: table won't double without this
        doubleVecSize(table);
    }
    // insert with linear probing
    unsigned long key = hash % table->capacity;
    while (table->contents[key] != NULL) {
        Serving* serving = (Serving*) table->contents[key];
        if (serving->NDB_Number == node->NDB_Number) return;
        key++;
    }
    table->contents[key] = (void*) node;
    table->size++;
}

unsigned long hashServing(Serving* serving) {
    return serving->NDB_Number - 45001524;
}

Serving* getServingWithCode(hashTable* table, int NDB_Number) {
    int currentIndex = NDB_Number - 45001524;
    while (((Serving*) table->contents[currentIndex])->NDB_Number != NDB_Number) {
        return NULL; //FIXME
    }
    return NULL; // FIXME
}


#endif