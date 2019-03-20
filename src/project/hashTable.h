#ifndef __HASHTABLE__H
#define __HASHTABLE__H

#include "../library/vector.h"
#include "diary.h"
#include "serving.h"
#include "stdlib.h"
#include<stdio.h>
typedef vector hashTable;

unsigned long hashServing(Serving*);
hashTable* servingTableFrom(vector*);
void insertServingHash(hashTable*, unsigned long, Serving*);
void insertEntry(hashTable*, entry* );
unsigned long hashEntry(entry*);
void doubleEntryTable(hashTable* table);
#endif