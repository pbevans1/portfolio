#include "hashTable.h"

#ifndef __HASHTABLE__C
#define __HASHTABLE__C

hashTable* servingTableFrom(vector* src) {
    hashTable* table = malloc(sizeof(hashTable));
    table->size = src->size;
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
    if(((table->size * 100) / 70) >= table->capacity) {
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


#endif