#include "../library/vector.h"
#include "serving.h"
#include "stdlib.h"
#include<stdio.h>

#ifndef __HASHTABLE__H
#define __HASHTABLE__H

typedef vector hashTable;

unsigned long hashServing(Serving*);
hashTable* servingTableFrom(vector*);
void insertServingHash(hashTable*, unsigned long, Serving*);

#endif