#include <signal.h>
#include <stdlib.h>
#include "../library/displayHelper.h"
#include "mainMenu.h"
#include "string.h"
#include "read.h"


#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C

string* display_start_menu();

string* displayMainMenu()  {
    // From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

    WINDOW *menu_win;
    int c, choice = 0;

    char *choices[] = { 	"",
			"Choice 2",
			"Choice 3",
			"Choice 4",
			"Exit",
		  };

    int n_choices = sizeof(choices) / sizeof(char *);
    
    int startx, starty, width, height;
	int ch;
    char str[23];
    // string* username = newString();
    char username[550] = {"\0"};

    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    attron(A_REVERSE);
	// mvprintw(23, 1, "Click exit to quit");
    refresh();
    attroff(A_REVERSE);

    starty = LINES / 6;
    startx = (COLS - 30) / 2;

    // menu_win = newwin(0, 0, LINES, COLS);
    string* name = display_start_menu(username); 
    endwin();
    return name;
    

    // print_menu(menu_win, 1, choices, n_choices);
	// /* Get all the mouse events */
	// mousemask(ALL_MOUSE_EVENTS, NULL);
	// keypad(menu_win, TRUE);
	// refresh();

	// while(1){ 
	// c = wgetch(menu_win);
	// 	if (c == KEY_MOUSE) {
	// 		if(getmouse(&event) == OK){	/* When the user clicks left mouse button */
    //             mvprintw(0, 0, "if 2");
	// 			//if(event.bstate & BUTTON1_PRESSED) {	
    //                 // break;
    //             report_choice(event.x + 1, event.y + 1, startx, starty, &choice, n_choices, choices);
    //             if(choice == -1) break; // Exit
    //             //mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"", choice, choices[choice - 1]);
    //             //refresh(); 
	// 			//}
	// 		}
	// 		print_menu(menu_win, choice, choices, n_choices);
	// 		break;
	// 	}
	// }
		
	// mvprintw(29, 0, "You chose choice %d with choice string %s", choice, choices[choice - 1]);
	// // clrtoeol();

    getch();
	endwin();			/* End curses mode		  */
}

string* display_start_menu() {
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
            if (choice == 2) continue;
            // printCentered(welcome_y+5, "Press any key to continue.");
        } else {
            printCentered(welcome_y+4, "We found your last save! Would you like to ");
            char* options[] = {"1. Open it", "2. Overwrite it", "3. Enter a different username"};
            choice = selectFromChoices(start_menu, welcome_y+5, (COLS - 30) / 2, options, 3);
            if (choice == 3) continue;
            if (choice == 1) readDiary(username->contents);
        }
    }
    for(int i = 5; i < 8; i++) {
        move(welcome_y+i, 0);
        clrtoeol();
    }
    refresh();
    mvprintw(welcome_y+5,  (COLS - 20) /2, "You selected %d", choice);
    getch();

    return username;
} 


static void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        exit(0);
}




#endif