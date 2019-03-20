#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "mainMenu.h"
#include "string.h"
#include "read.h"
#include "diary.h"


#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C

string* getUsernameMenu();

string* displayMainMenu()  {
    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html


    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    

    // menu_win = newwin(0, 0, LINES, COLS);
    string* username = getUsernameMenu(); 
    finish(0);
    return username;
}

string* getUsernameMenu() {
    //Open Welcome Screen
    WINDOW* start_menu = newwin(0, 0, LINES, COLS);
    char welcome[] = "Welcome to Nutrition Tracker Pro!";
    int welcome_y = LINES / 6;
    int choice;
    string* username;
    while (1) {
        clear();
        printCentered(welcome_y, welcome);
        //Get Username	
        char instructions[] = "Enter a username to continue: ";
        mvprintw(welcome_y+3, ((COLS - 40) / 2), instructions);
        username = readString(50, '\n');
        
        move(welcome_y+3, 0);
        clrtoeol();
        int startx = (COLS - username->size - 8) / 2;
        mvprintw(welcome_y+3, startx, "Hello %s!", username->contents);

        
        //Check for log file
        if (!logFileExists(username->contents)) {
            printCentered(welcome_y+4, "We couldn't find any old log files for you");
            char* options[] = {"1. Start a new diary", "2. Enter a different username"};
            choice = selectFromChoices(start_menu, welcome_y+5, (COLS - 30) / 2, options, 2);
            if (choice == 1) return username;
            if (choice == 2) continue;
            // printCentered(welcome_y+5, "Press any key to continue.");
        } else {
            printCentered(welcome_y+4, "We found your last save! Would you like to ");
            char* options[] = {"1. Open it", "2. Overwrite it", "3. Enter a different username"};
            choice = selectFromChoices(start_menu, welcome_y+5, (COLS - 30) / 2, options, 3);
            if (choice == 1) {
                entry* diary = readDiary(username->contents);
                break;
            }
            if (choice == 3) continue;
        }
    }
    
    getch();

    return username;
} 


void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        // exit(0);
}




#endif