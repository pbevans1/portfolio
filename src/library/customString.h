#ifndef __STRING_CUST_H
#define __STRING_CUST_H

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>


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
int strEquals(string*, string*);
int strComesBefore(string*, string*);
void printStr(string*);
string* copyStr(string*);
string* strFrom(char*);
char *strtokm(char *str, const char *delim);
unsigned long hashStr(string* name);
void uppercase(char []);
void trim(char[]);
void trimStr(string*);
void freeStr(string*);
string* joinStr(string*, string*, char*);
#endif
