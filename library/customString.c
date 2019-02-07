#include<stdio.h>
#include<stdlib.h> 
// #include<stdbool.h> 
#include<string.h>
#include "customString.h"

#ifndef __STRING_CUST_H
#define __STRING_CUST_H

string* newString() {
    string* new = malloc(sizeof(string));
    new->size = 0;
    new->capacity = 1;
    new->contents = malloc(sizeof(char) * new->capacity);
    new->contents[0] = '\0';
    return new;
}

int len(string* str) {
    return str->size;
}

bool strEquals(string* str1, string* str2) {
    return (strcmp(str1->contents, str2->contents) == 0);
}

bool strComesBefore(string* str1, string* str2) {
    return (strcmp(str1->contents, str2->contents) < 0);
}


void printStr(string* str) {
    for (int i = 0; i < str->size; i++) {
        printf("%c", str->contents[i]);
    }
    printf("\n");
}
 
void pushToStr(string* str, char value) {
    if (str->size == str->capacity) {
        str->capacity *= 2;
        char* temp_contents = malloc(sizeof(char) * (str)->capacity);
        for (int i = 0; i < str->size; i++) {
            temp_contents[i] = str->contents[i];
        }
        for (int i = str->size; i < str->capacity; i++) {
            temp_contents[i] = '\0';
        }
        free(str->contents);
        str->contents = temp_contents;
    }
    str->contents[str->size] = value;
    str->size++;
}

string* copyStr(string* str) {
    string* new = newString();
    for (int i = 0; i < str->size; i++) {
        pushToStr(new, str->contents[i]);
    }
    return new;
}

char popFromStr(string* str) {
    if (str->size == 0) return '\0';
    char last = str->contents[--str->size];
    if (str->size <= (str->capacity / 4)) {
        str->capacity /= 2;
        char* temp_contents = malloc(sizeof(char) * (str)->capacity);
        for (int i = 0; i < str->size; i++) {
            temp_contents[i] = str->contents[i];
        }
        for (int i = str->size; i < str->capacity; i++) {
            temp_contents[i] = '\0';
        }
        free(str->contents);
        str->contents = temp_contents;
    }
    str->contents[str->size] = '\0';
    return last;
}

string* destroyStr(string* str) {
    free(str->contents);
    free(str);
    return NULL;
}

void test_string() {
    string* a = newString();
    string* b = newString();

    for (int i = 0; i < 20; i++) {
        pushToStr(a, (char)(i + 97));
    }
    pushToStr(a, 'z');
    for (int i = 0; i < 80; i++) {
        pushToStr(b, (char)(i + 97));
    }
    string* c = copyStr(b); 
    if (!strEquals(c, b)) {
        printf("Error in customString line 102!\n");
        return;
    }
    
    for (int i = 0; i < 60; i++) {
        popFromStr(b);
    }
    
    pushToStr(b, 'y');
    popFromStr(a);
    popFromStr(b);
    if (!strEquals(a, b)) {
        printf("Error in customString line 113!\n");
        return;
    }
    printf("Finished testing customstring... All tests passed\n");
}

// int main() {
//     test_string();
// }
#endif