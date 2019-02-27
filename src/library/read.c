#include "read.h"
#include "../project/players.h"


#ifndef __READ_CUST_C
#define __READ_CUST_C

vector* readPlayerFile() {
    FILE* fp = fopen("/Users/prestonevans/Downloads/mlb-pitch-data-20152018/player_names.csv", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    char buffer[700];
    fgets(buffer, 700, fp);
    printf("%s", buffer);
    vector* players = newVector();
    // for(int i = 0; i< 2218; i++) {
    
    while (fgets(buffer, 700, fp)) {
        pushToVec(players, getPlayer(buffer));
    }
    return players;
}
#endif