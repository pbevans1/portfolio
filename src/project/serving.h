#include "../library/customString.h"

#ifndef __SERVING__H 
#define __SERVING__H 

// enum source {
//     GDSN = 0,
//     LI =  1,
//     UNKNOWN = 2,
// };

typedef struct __serving {
    int NDB_Number;
    int servingSize;
    string* regUnit;
    int houseServingSize;
    string* houseUnit;
    
} Serving;


Serving* getServingFromString(char*);
// char *strtokm(char*, const char*);
void prettyPrintServing(Serving*);

#endif
