#ifndef __HASHTABLE__H
#define __HASHTABLE__H

#include "../library/vector.h"
#include "diary.h"
#include "serving.h"
#include "stdlib.h"
#include<stdio.h>
#include "../library/customString.h"
#include <string.h>

typedef vector hashTable;

unsigned long hashServing(Serving*);
hashTable* servingTableFrom(vector*);
void insertServingHash(hashTable*, unsigned long, Serving*);
void insertEntry(hashTable*, entry* );
unsigned long hashEntry(entry*);
void doubleEntryTable(hashTable* table);
int entriesMatch(entry*, entry*);
unsigned long hashNameDate(string*, string*);
int matchesEntry(string*, string*, entry*);
void deleteByNameDate(hashTable*, string*, string*);
hashTable* newTable();
int getEntryLocation(hashTable*, entry*);
#endif