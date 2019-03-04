#include<stdbool.h>
#ifndef __STRING_CUST_H
#define __STRING_CUST_H
typedef struct _string {
    int size;
    int capacity;
    char *contents;
} string;

string* newString();
void pushToStr(string*, char);
char popFromStr(string*);
void test_string();
int len(string*);
bool strEquals(string*, string*);
bool strComesBefore(string*, string*);
void printStr(string*);
string* copyStr(string*);
string* strFrom(char*);
char *strtokm(char *str, const char *delim);

#endif