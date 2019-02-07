#include<stdio.h>
#include<stdlib.h> 
#include "vector.h"

#ifndef __VECTOR_INT_H
#define __VECTOR_INT_H

vector* newVector() {
    vector* new = malloc(sizeof(vector));
    new->size = 0;
    new->capacity = 1;
    new->contents = malloc(sizeof(int) * new->capacity);
    return new;
}
 
void pushToVec(vector* vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        int* temp_contents = malloc(sizeof(int) * (vec)->capacity);
        for (int i = 0; i < vec->size; i++) {
            temp_contents[i] = vec->contents[i];
        }
        free(vec->contents);
        vec->contents = temp_contents;
    }
    vec->contents[vec->size] = value;
    vec->size++;
}

int popFromVec(vector* vec) {
    if (vec->size == 0) return -99999999;
    int last = vec->contents[--vec->size];
    if (vec->size <= (vec->capacity / 4)) {
        vec->capacity /= 2;
        int* temp_contents = malloc(sizeof(int) * (vec)->capacity);
        for (int i = 0; i < vec->size; i++) {
            temp_contents[i] = vec->contents[i];
        }
        free(vec->contents);
        vec->contents = temp_contents;
    }
    return last;
}

vector* destroyVec(vector* vec) {
    free(vec->contents);
    free(vec);
    return NULL;
}

void test_vector() {
    vector* vec = newVector();
    int iters = 20;
    for (int i = 0; i < iters; i++) {
        pushToVec(vec, i);
    }
    for (int i = 0; i < iters; i++) {
        printf("%d, ", vec->contents[i]);
    }
    printf("\nDownward!\n");
    for (int i = 0; i < iters; i++) {
        printf("%d, ", popFromVec(vec));
    }
    printf("\nShould now see -99999999\n");
    printf("%d, ", popFromVec(vec));
}

// int main() {
//     test_vector();
// }
#endif