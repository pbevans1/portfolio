#ifndef __HASHTABLE__C
#define __HASHTABLE__C

#include "hashTable.h"

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

// From Stack Overflow https://stackoverflow.com/questions/2571683/djb2-hash-function
// Uses djb2 hash algorithm
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void insertEntry(hashTable* table, entry* new) { 
    if (table->size * 10 > table->capacity * 7) {
        doubleEntryTable(table);
    }
    unsigned long hash = hashEntry(new);
    int key = hash % table->capacity;
    while(table->contents[key] != NULL) {
        entry* currentEntry = (entry*) table->contents[key];
        if (entriesMatch(new, currentEntry)) return;
        if(currentEntry->isDeleted) {
            break;
        }
        key = (key + 1) % table->capacity;
    }
    table->contents[key] = new;
}

int getEntryLocation(hashTable* table, entry* ent) {
    if (ent == NULL) return 0;
    int key = hashEntry(ent) % table->capacity;
    while(table->contents[key] != NULL) {
        entry* currentEntry = (entry*) table->contents[key];
        if(currentEntry->isDeleted) {
            continue;
        }
        if (entriesMatch(ent, currentEntry)) return key;
        key = (key + 1) % table->capacity;
    }
    return 0;
}

entry* searchForEntry(hashTable* table, entry* ent) {
    int key = hashEntry(ent) % table->capacity;
    while(table->contents[key] != NULL) {
        entry* currentEntry = (entry*) table->contents[key];
        if(currentEntry->isDeleted) {
            continue;
        }
        if (entriesMatch(ent, currentEntry)) return currentEntry;
        key = (key + 1) % table->capacity;
    }
    return NULL;
}

entry* searchByNameDate(hashTable* table, string* name, string* date) {
    int key = hashNameDate(name, date) % table->capacity;
    while(table->contents[key] != NULL) {
        entry* currentEntry = (entry*) table->contents[key];
        if(currentEntry->isDeleted) {
            continue;
        }
        if (matchesEntry(name, date, currentEntry)) return currentEntry;
        key = (key + 1) % table->capacity;
    }
    return NULL;
}

void deleteEntry(hashTable* table, entry* del) {
    del->isDeleted = 1;
    --table->size;
}

void deleteByNameDate(hashTable* table, string* name, string* date) {
    entry* del = searchByNameDate(table, name, date);
    if (del == NULL) return;
    del->isDeleted = 1;
    --table->size;
}

int entriesMatch(entry* e1, entry* e2) {
    int dates = strEquals(e1->date, e2->date);
    int products = strEquals(e1->productName, e2->productName);
    return dates * products;
}

int matchesEntry(string* name, string* date, entry* e2) {
    int dates = strEquals(date, e2->date);
    int products = strEquals(name, e2->productName);
    return dates * products;
}

unsigned long hashEntry(entry* new) {
    // FIXME
    char name[300];
    strcpy(name, new->date->contents);
    strcat(name, new->productName->contents);
    return hash(name);
}
unsigned long hashNameDate(string* name, string* date) { 
    char hashString[300];
    strcpy(hashString, date->contents);
    strcat(hashString, name->contents);
    return hash(hashString);
}



void doubleEntryTable(hashTable* table) {
    table->capacity *= 2;
    table->size = 0;
    void** temp = table->contents;
    table->contents = malloc(sizeof(void*) * table->capacity);
    for(int i = 0; i < (table->capacity / 2); i++) {
        if (temp[i] != NULL) {
            entry* current = (entry*) temp[i];
            if (current->isDeleted) {
                freeEntry(current);
                continue;
            }
            insertEntry(table, current);
        }
    }
    free(temp);
}

// hashTable* servingTableFrom(vector* src) {
//     hashTable* table = malloc(sizeof(hashTable));
//     table->size = 0;
//     // table->size = src->size;
//     table->capacity = src->size;
//     table->contents = malloc(sizeof(Serving*) * table->capacity);
//     Serving* currentServing;
//     while((currentServing = (Serving*) popFromVec(src))) { 
//         insertServingHash(table, hashServing(currentServing), currentServing);
//     }
//     return table;
// }

// void insertServingHash(hashTable* table, unsigned long hash, Serving* node) {
//     // If hash table is at 70% load factor, expand
//     if(((table->size * 100) / 70) >= table->capacity) { //FIXME: table won't double without this
//     // if(((table->size * 100) / 95) >= table->capacity) { //FIXME: table won't double without this
//         doubleVecSize(table);
//     }
//     // insert with linear probing
//     unsigned long key = hash % table->capacity;
//     while (table->contents[key] != NULL) {
//         Serving* serving = (Serving*) table->contents[key];
//         if (serving->NDB_Number == node->NDB_Number) return;
//         key++;
//     }
//     table->contents[key] = (void*) node;
//     table->size++;
// }

// unsigned long hashServing(Serving* serving) {
//     return serving->NDB_Number - 45001524;
// }

// Serving* getServingWithCode(hashTable* table, int NDB_Number) {
//     int currentIndex = NDB_Number - 45001524;
//     while (((Serving*) table->contents[currentIndex])->NDB_Number != NDB_Number) {
//         return NULL; //FIXME
//     }
//     return NULL; // FIXME
// }


#endif
