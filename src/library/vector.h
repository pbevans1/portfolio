
#ifndef __VECTOR_INT_H
#define __VECTOR_INT_H

typedef struct _vector {
    int size;
    int capacity;
    void **contents;
} vector;

vector* newVector();
void pushToVec(vector*, void*);
void* popFromVec(vector*);
vector* destroyVec(vector*);


#endif