#ifndef __STRING_CUST_C
#define __STRING_CUST_C
#include "customString.h"


string* newString() {
    string* new = malloc(sizeof(string));
    new->size = 0;
    new->capacity = 2;
    new->contents = malloc(sizeof(char) * new->capacity);
    new->contents[1] = '\0';
    return new;
}

int len(string* str) { 
    return str->size;
}

int minInt(int a, int b) {
    if (a < b) return a;
    return b;
}

int strEquals(string* str1, string* str2) {
    int size = minInt(str1->size, str2->size);
    return (strncmp(str1->contents, str2->contents, size) == 0);
}

int strComesBefore(string* str1, string* str2) {
    int size = minInt(str1->size, str2->size);
    return (strncmp(str1->contents, str2->contents, size) < 0);
}


void printStr(string* str) {
    printf("%s", str->contents);
}

// Create new string from char*
string* strFrom(char* str) {
    string* new = malloc(sizeof(string));
    int capacity = strlen(str) + 1;
    int size = capacity - 1;
    new->contents = malloc(sizeof(char) * capacity);
    strncpy(new->contents, str, size);
    new->contents[size] = '\0';
    new->capacity = capacity;
    new->size = size;
    return new;
}

// Append to string class 
void pushToStr(string* str, char value) {
    int i;
    char* temp_contents ;
    if ((str->size + 1) == str->capacity) { 
    // If adding a character would overwrite the last null
        str->capacity *= 2;
        temp_contents = malloc(sizeof(char) * (str)->capacity);
        for (i = 0; i < str->size; i++) {
            temp_contents[i] = str->contents[i];
        }
        for (i = str->size; i < str->capacity; i++) {
            temp_contents[i] = '\0';
        }
        free(str->contents);
        str->contents = temp_contents;
    }
    str->contents[str->size] = value;
    str->size++;
}

// Create a deep copy of a string
string* copyStr(string* str) {
    int i;
    string* new = newString();
    for (i = 0; i < str->size; i++) {
        pushToStr(new, str->contents[i]);
    }
    return new;
}

// Pop from a string
char popFromStr(string* str) {
    int i;
    if (str->size == 0) return '\0';
    char last = str->contents[--str->size];
    if (str->size <= (str->capacity / 4)) {
        str->capacity /= 2;
        char* temp_contents = malloc(sizeof(char) * (str)->capacity);
        for (i = 0; i < str->size; i++) {
            temp_contents[i] = str->contents[i];
        }
        for (i = str->size; i < str->capacity; i++) {
            temp_contents[i] = '\0';
        }
        free(str->contents);
        str->contents = temp_contents;
    }
    str->contents[str->size] = '\0';
    return last;
}

// Deep free a string
string* destroyStr(string* str) {
    free(str->contents);
    free(str);
    return NULL;
}

// Uppercase a target char array
void uppercase(char target[]) {
    int i;
    int size = strlen(target);
    for(i = 0; i<size;i++) {
        if (target[i] >= 97 && target[i] <= 122)
            target[i] = target[i] - 32;
    }
}

// Trime whitespace from target char array
void trim(char target[]) {
    int size = strlen(target);
    int lastIndex = 0;
    int i;
    for(i = 0; i<size;i++) {
        if (target[i] != ' ' && target[i] != '\n' && target[i] != '\t') lastIndex = i;
    }
    target[lastIndex + 1] = '\0';
}

// Trim whitespace from target string
void trimStr(string* target) {
    //FIXME: Double check that size is correct
    int lastIndex = 0;
    for(int i=0; i<target->size;i++) {
        if (target->contents[i] != ' ' && target->contents[i] != '\n' && target->contents[i] != '\t') lastIndex = i;
    }
    target->contents[lastIndex + 1] = '\0';
    target->size = lastIndex+1;
}

// Deep free a string
void freeStr(string* target) {
    free(target->contents);
    free(target);
}

// Concatenate two strings with a separating charactor. Returns a new string
string* joinStr(string* s1, string* s2, char* separator) {
    int i, size;
    string* new;
    if (s1 == NULL || s2 == NULL) return NULL;
    size = s1->size + s2->size + strlen(separator);
    new = malloc(sizeof(string));
    new->size = size;
    new->capacity = size + 1;
    new->contents = malloc(sizeof(char) * new->capacity);
    // Copy str1 to new
    for (i = 0; i < s1->size; i++) {
        new->contents[i] = s1->contents[i];
    }
    // Insert separator
    for (i = 0; i < strlen(separator); i++) {
        new->contents[i + s1->size] = separator[i];
    }
    // Append str2
    for (i = 0; i < s2->size; i++) {
        new->contents[i + s1->size + strlen(separator)] = s2->contents[i];
    }
    new->contents[new->size] = '\0';
    return new;
}
// From https://stackoverflow.com/questions/8512958/is-there-a-windows-variant-of-strsep
char* mystrsep(char** stringp, const char* delim)
{
  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}
#endif
