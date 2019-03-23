#include<stdio.h>
#include <string.h>
#include<stdlib.h> 
#include "vector.h"

#ifndef __VECTOR_INT_C
#define __VECTOR_INT_C

vector* newVector() {
    vector* new = malloc(sizeof(vector));
    new->size = 0;
    new->capacity = 1;
    new->contents = malloc(sizeof(void*) * new->capacity);
    for (int i = 0; i < new->capacity; ++i) {
        new->contents[i] = NULL;
    }
    return new;
}
 
void pushToVec(vector* vec, void* value) {
    if (vec->size >= vec->capacity) {
        doubleVecSize(vec);
    }
    vec->contents[vec->size] = value;
    vec->size++;
}

void doubleVecSize(vector* vec) { 
     vec->capacity *= 2; 
        void** temp_contents = malloc(sizeof(void*) * (vec)->capacity);
        memcpy(temp_contents, vec->contents, sizeof(void*) * vec->capacity / 2);
        free(vec->contents);
        vec->contents = temp_contents;
        for (int i = vec->size; i < vec->capacity; ++i) {
            vec->contents[i] = NULL;
        }
}

void* popFromVec(vector* vec) {
    if (vec->size == 0) return NULL;
    void* last = vec->contents[--vec->size];
    // if (vec->size <= (vec->capacity / 4)) {
    //     vec->capacity /= 2;
    //     void** temp_contents = malloc(sizeof(void*) * (vec)->capacity);
    //     memcpy(temp_contents, vec->contents, sizeof(void*) * vec->capacity / 2);
    //     free(vec->contents);
    //     vec->contents = temp_contents;
    // }
    return last;
}

vector* destroyVec(vector* vec) {
    free(vec->contents);
    free(vec);
    return NULL;
}


// int main() {
//     test_vector();
// }
#endif
