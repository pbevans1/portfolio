#include<stdbool.h>
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