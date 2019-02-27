#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "mainMenu.h"

#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C

void displayMainMenu()  {


    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
    int ch;
    int screenRows, screenCols;

    char str[23];

    initscr();			/* Start curses mode 		  */
    keypad(stdscr, TRUE);
    getmaxyx(stdscr,screenRows,screenCols);
    cbreak();
    noecho();			/* Don't echo() while we do getch */
    char message[] = "Enter a String:\n";
	mvprintw(screenRows/2, centerHoriz(message, screenCols), message);
    getstr(str);
	mvprintw(screenRows/2 +1, centerHoriz(message, screenCols), "You entered: %s", str);
    mvprintw(screenRows-2,0,"This screen has %d rows and %d columns\n",screenRows,screenCols);
    printw("Try resizing your window(if possible) and then run this program again");
    refresh();
    
	// ch = getch();			/* Wait for user input */

    // if (ch == KEY_F(1)) printw("F1 was pressed");
    // else
	// {	printw("The pressed key is ");
	// 	attron(A_BOLD);
	// 	printw("%c", ch);
	// 	attroff(A_BOLD);
	// }
    refresh();
    getch();
	endwin();			/* End curses mode		  */


    // /* Curses initialization boilerplate from https://invisible-island.net/ncurses/ncurses-intro.html#using */
    // int num = 0;

    // /* initialize your non-curses data structures here */

    // (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

    // (void) initscr();      /* initialize the curses library */
    // keypad(stdscr, TRUE);  /* enable keyboard mapping */
    // leaveok(stdscr, TRUE);  /* leave cursor in place on refresh */
    // (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    // // cbreak();       /* take input chars one at a time, no wait for \n */
    // (void) echo();         /* echo input - in color */
    // if (has_colors())
    // {
    //     start_color();

    //     /*
    //      * Simple color assignment, often all we need.  Color pair 0 cannot
    //      * be redefined.  This example uses the same value for the color
    //      * pair as for the foreground color, though of course that is not
    //      * necessary:
    //      */
    //     init_pair(1, COLOR_RED,     COLOR_BLACK);
    //     init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    //     init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    //     init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    //     init_pair(5, COLOR_CYAN,    COLOR_BLACK);
    //     init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    //     init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    // }
    // for (int i = 1;1<10;i++)
    //     {
    //         int c = getch();     /* refresh, accept single keystroke of input */
    //         attrset(COLOR_PAIR(num % 8));
    //         num++;
    //         /* process the command keystroke */
    //     }

    //     finish(0);               /* we're done */
}

    


static void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        exit(0);
}




#endif