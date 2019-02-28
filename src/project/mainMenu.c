#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "mainMenu.h"


#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C



void displayMainMenu()  {
    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

    MEVENT event;
    WINDOW *menu_win;
    int c, choice = 0;

    char *choices[] = { 	"Choice 1",
			"Choice 2",
			"Choice 3",
			"Choice 4",
			"Exit",
		  };

    int n_choices = sizeof(choices) / sizeof(char *);
    
    int startx, starty, width, height;
	int ch;
    char str[23];

    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    attron(A_REVERSE);
	mvprintw(23, 1, "Click exit to quit");
    refresh();
    attroff(A_REVERSE);

    starty = (LINES - 10) / 2;
    startx = (COLS - 30) / 2;

    menu_win = newwin(10, 30, starty, startx);
    print_menu(menu_win, 1, choices, n_choices);
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	keypad(menu_win, TRUE);
	refresh();

	while(1){ 
	c = wgetch(menu_win);
		if (c == KEY_MOUSE) {
			if(getmouse(&event) == OK){	/* When the user clicks left mouse button */
				if(event.bstate & BUTTON1_PRESSED) {	
                    // break;
                    report_choice(event.x + 1, event.y + 1, startx, starty, &choice, n_choices, choices);
					if(choice == -1) break; // Exit
                    mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"", choice, choices[choice - 1]);
					refresh(); 
				}
			}
			print_menu(menu_win, choice, choices, n_choices);
			break;
		}
	}
		
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();

    getch();
	endwin();			/* End curses mode		  */
}

    


static void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        exit(0);
}




#endif