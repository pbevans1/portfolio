#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "mainMenu.h"
#include "string.h"
#include "read.h"
#include "diary.h"


#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C

vector* getUserDiaryMenu();
void diaryCrudMenu(vector* diary, struct Node*);
char** formatNextTenEntries(vector* diary, int startNum, char* button);
int numEntries(char** formattedEntries);

string* displayMainMenu(struct Node* productRoot)  {
    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html


    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    

    // menu_win = newwin(0, 0, LINES, COLS);
    vector* userDiary = getUserDiaryMenu();
    diaryCrudMenu(userDiary, productRoot);
    finish(0);
    // FIXME
    return newString();
}

void diaryAddMenu(vector* diary, struct Node* productRoot) {
    int instructionHeight = LINES / 6;
    char instructions[] = "What kind of food did you eat? ";
    printCentered(instructionHeight, instructions);
    mvprintw(instructionHeight + 1, COLS/2 - 20, "Item Name: ");
    
    clear();
}

void diaryCrudMenu(vector* diary, struct Node* productRoot) {
    int instructionHeight = LINES / 6;
    char instructions[] = "Click any entry view, modify, or delete it, or press the button to add a new one.";
    int lastEntryDisplayed = 0;
    char addButton[] = " New Entry";
    char** currentPage;
    while(1) {
        clear();
        printCentered(instructionHeight, instructions);
        currentPage = formatNextTenEntries(diary, lastEntryDisplayed, addButton);
        int numToDisplay = numEntries(currentPage);
        int x = (COLS / 5);
        int choice = selectFromDiary(instructionHeight + 2, x, currentPage, numToDisplay + 1);
        if (choice == 0) diaryAddMenu(diary, productRoot);
        getch();
        break;
    }
}

void diaryAddMenu(vector* diary, struct Node* productRoot) {

}

int numEntries(char** formattedEntries) {
    int i;
    for (i = 1; i < 11; i++) {
        if (formattedEntries[i] == NULL) break;
    }
    return i - 1;
}

char** formatNextTenEntries(vector* diary, int startNum, char* button) {
    char** formattedEntries = malloc(sizeof(char*) * 11);
    formattedEntries[0] = button;
    int entriesIndex = 1;
    // Fill up to 10 empty slots
    for (int i = startNum; i < diary->size && entriesIndex < 11; i++) {
        entry* currentEntry = (entry*) diary->contents[i];
        formattedEntries[entriesIndex] = formatEntry(currentEntry);
        entriesIndex++;
    }
    // Write NULLs to empty slots
    for (int i = entriesIndex; i < 11; i++) {
        formattedEntries[i] = NULL;
    }
    return formattedEntries;
}

vector* getUserDiaryMenu(struct Node* productRoot) {
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
            char* options[] = {"Start a new diary", "Enter a different username"};
            choice = selectFromChoices(start_menu, welcomeHeight+5, (COLS - 30) / 2, options, 2);
            choice++; // Convert choice from index to counting number;
            if (choice == 1) {
                destroyWindow(start_menu);
                return newVector();
            }    
            if (choice == 2) continue;

        } else {
            printCentered(welcomeHeight+4, "We found your last save! Would you like to ");
            char* options[] = {"Open it", "Overwrite it", "Enter a different username"};
            choice = selectFromChoices(start_menu, welcomeHeight+5, (COLS - 30) / 2, options, 3);
            if (choice == 1) {
                destroyWindow(start_menu);
                return readDiary(username->contents, productRoot);
            }
            if (choice == 2) {
                destroyWindow(start_menu);
                return newVector();
            }
            if (choice == 3) continue;
        }
    }
    
    getch();
    // Unreachable
    printf("Uh-oh! We reached unreachable!");
    getch();
    destroyWindow(start_menu);

    return newVector();
} 


void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        // exit(0);
}




#endif