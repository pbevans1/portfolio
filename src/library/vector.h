
#ifndef __VECTOR_INT_H
#define __VECTOR_INT_H

#include<stdio.h>
#include <string.h>
#include<stdlib.h> 

typedef struct _vector {
    int size;
    int capacity;
    void **contents;
} vector;

vector* newVector();
void pushToVec(vector*, void*);
void* popFromVec(vector*);
vector* destroyVec(vector*);
void doubleVecSize(vector* );


#endif
