#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "mainMenu.h"
#include "string.h"
#include "read.h"
#include "diary.h"


#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C

hashTable* getUserDiaryMenu();
void diaryCrudMenu(hashTable* diary);
string* displayMainMenu()  {
    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html


    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    

    // menu_win = newwin(0, 0, LINES, COLS);
    hashTable* userDiary = getUserDiaryMenu();
    diaryCrudMenu(userDiary);
    finish(0);
    // FIXME
    return newString();
}

void diaryCrudMenu(hashTable* diary) {
    int instructionHeight = LINES / 6;
    char instructions[] = "Click any entry view, modify, or delete it, or press the button to add a new one.";
    int currentEntry = 0;
    char addButton[] = "New Entry";
    while(1) {
        clear();
        printCentered(instructionHeight, instructions);

        getch();
        break;
    }
}

char** formatNextTenEntries(hashTable* diary, entry* lastDisplayed, int* numRetrieved, char* button) {
    char** formattedEntries = malloc(sizeof(char*) * 11);
    formattedEntries[0] = button;
    int start = getEntryLocation(diary, lastDisplayed);
    numRetrieved = 0;
    for (int i = start; i < diary->capacity; i++) {
        if (diary->contents[i] != NULL) {
            entry* currentEntry = diary->contents[i];
            if (currentEntry->isDeleted) continue;
            char* next = formatEntry(currentEntry);
            numRetrieved++;
            formattedEntries[*numRetrieved] = next;
            if (*numRetrieved >= 10) return formattedEntries;
        }
    }
    return NULL;
}

hashTable* getUserDiaryMenu() {
    //Open Welcome Screen
    WINDOW* start_menu = newwin(0, 0, LINES, COLS);
    char welcome[] = "Welcome to Nutrition Tracker Pro!";
    int welcomeHeight = LINES / 6;
    int choice;
    string* username;
    while (1) {
        clear();
        printCentered(welcomeHeight, welcome);
        //Get Username	
        char instructions[] = "Enter a username to continue: ";
        mvprintw(welcomeHeight+3, ((COLS - 40) / 2), instructions);
        username = readString(50, '\n');
        
        move(welcomeHeight+3, 0);
        clrtoeol();
        int startx = (COLS - username->size - 8) / 2;
        mvprintw(welcomeHeight+3, startx, "Hello %s!", username->contents);

        
        //Check for log file
        if (!logFileExists(username->contents)) {
            printCentered(welcomeHeight+4, "We couldn't find any old log files for you");
            char* options[] = {"1. Start a new diary", "2. Enter a different username"};
            choice = selectFromChoices(start_menu, welcomeHeight+5, (COLS - 30) / 2, options, 2);
            choice++; // Convert choice from index to number;
            if (choice == 1) {
                destroyWindow(start_menu);
                return newTable();
            }    
            if (choice == 2) continue;
            // printCentered(welcomeHeight+5, "Press any key to continue.");
        } else {
            printCentered(welcomeHeight+4, "We found your last save! Would you like to ");
            char* options[] = {"1. Open it", "2. Overwrite it", "3. Enter a different username"};
            choice = selectFromChoices(start_menu, welcomeHeight+5, (COLS - 30) / 2, options, 3);
            if (choice == 1) {
                destroyWindow(start_menu);
                return readDiary(username->contents);
            }
            if (choice == 2) {
                destroyWindow(start_menu);
                return newTable();
            }
            if (choice == 3) continue;
        }
    }
    
    getch();
    // Unreachable
    printf("Uh-oh! We reached unreachable!");
    getch();
    destroyWindow(start_menu);

    return newTable();
} 


void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        // exit(0);
}




#endif