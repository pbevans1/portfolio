#ifndef __DISPLAY__HELP__C
#define __DISPLAY__HELP__C
#include "displayHelper.h"

int centerHoriz(char message[], int numCols) {
    return ((numCols - strlen(message))/2);
}

// Helper method to pad a char* with whitespace
// Returns result as a string
string* createButtonString(char* text, int size) {
	string* new = malloc(sizeof(string));
	new->size = size;
	new->capacity = size + 1;
	new->contents = malloc(sizeof(char) * new->capacity);
	int textSize = strlen(text);
	int numSpaces = (size - textSize) / 2;
	int i;
	for(i = 0; i < new->capacity; i++) {
		new->contents[i] = '\0';
	}
	for (int i = 0; i <= numSpaces; i++) {
		new->contents[i] = ' ';
	}
	strcat(new->contents, text);
	for (int i = numSpaces + textSize + 1; i < new->size; i++) {
		new->contents[i] = ' ';
	}
	return new;
}

/* Report the choice according to mouse position */
// Modified From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
int report_choice(int mouse_x, int mouse_y, int startx, int endx, int y, int numChoices, char* choices[])
{	
	int choice;
 
	for(choice = 0; choice < numChoices; ++choice) {
		if(mouse_y == (y + (choice * 2)) && mouse_x >= startx && mouse_x <= endx)
		{	
			return choice;	
		} 
	}
	return -2;
}


// Specialized helper function for selecting items from the diary screen
// Corrects for double spacing of diary entries
int reportDiaryChoice(int mouse_x, int mouse_y, int startx, int endx , int y, int numChoices, char* choices[]) 
{	
	int choice;
	if(mouse_y == y && mouse_x >= (COLS / 2) - 5  && mouse_x <= (COLS / 2) + 5) return 0; // handle add button
	for(choice = 1; choice < numChoices; ++choice) {
		if(mouse_y == (y + (choice * 2)) && mouse_x >= startx && mouse_x <= endx)
		{	
			return choice;	
		} 
	}
	return -2;
}

// Prints a message centered horizontally at height y
void printCentered(int y, char* message) {
	int x = (COLS - strlen(message)) / 2;
	mvprintw(y, x, message);
	refresh();
}

// Gets the length of the longest string the user might click
int maxLen(char** choices, int numChoices) {
	int max = -1;
	for (int i = 0; i < numChoices; i++) {
		int len = strlen(choices[i]);
		if (len > max) max = len;
	}
	return max;
}

// Print spaces until the cursor reaches the given x-coordinate
void writeSpacesUntil(int x) {
	int currentx, y;
	getyx(stdscr, y, currentx);
	for (int i = currentx; i < x; i++) {
		addch(' ');
	}
	y--;
}

// Displays all of the users choices, reports the number of the choice selected
// -5 signifies exit, all other integers signify a choice
int selectFromChoices(WINDOW* win, int y, int x, char** choices, int numChoices) {
	cbreak(); 
	noecho();
	int input, choice;
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	MEVENT event;
	keypad(win, TRUE);

    // Print each string in choices, padding with spaces as necessary
	attron(A_REVERSE); 
	int maxlength = maxLen(choices, numChoices);
	for (int i = 0; i < numChoices; i++) {
		string* button = createButtonString(choices[i], maxlength);
		mvprintw(y+(i*2), x, button->contents);
		freeStr(button);
	}
	attroff(A_REVERSE);
	refresh();

    // Get input
	choice = 0;
	while(1){ 
		input = getch();
		if (input == KEY_MOUSE) {
            // Handle click events
			if (exitButtonWasClicked(input, event)) {
				return -5;
				}
			if(getmouse(&event) == OK){
				int mouseChoice = report_choice(event.x, event.y, x, x+maxlength, y, numChoices, choices);
				if (mouseChoice < 0) continue;
				choice = mouseChoice;
				return choice;
			}
		}
	}
	return choice; // return the choice
}

// Displays all of the users choices on the diary screen, reports the number of the choice selected
// -5 signifies exit, all other integers signify a choice
int selectFromDiary(int y, int x, char** choices, int numChoices) {
	cbreak();               /* Don't wait for newline when reading characters */
    noecho();
	MEVENT event;
	int input, choice;
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	keypad(stdscr, TRUE);
	attron(A_REVERSE); 
	printCentered(y, choices[0]);
	attroff(A_REVERSE);
	
    // Print each of the user's options
	int maxlength = maxLen(choices, numChoices);
	for (int i = 1; i < numChoices; i++) {
		mvprintw(y+(i*2), x, choices[i]); //double space
		writeSpacesUntil(maxlength);
	}
	refresh(); 

    // Get input
	choice = 0;
	while(1){ 
		input = getch();
		if (input == KEY_MOUSE) {
            // Handle click events
			if (exitButtonWasClicked(input, event)) return -5;
			if (previousButtonClicked(input, event)) return -3;
			if (nextButtonClicked(input, event)) return -1;
			if(getmouse(&event) == OK){
				int mouseChoice = reportDiaryChoice(event.x, event.y, x, x + maxlength, y, numChoices, choices);
				if (mouseChoice < 0) continue;
				choice = mouseChoice;
				return choice;
			}
		}
	}
	return choice; // return the choice
}

// Displays produts similar to the string entered by the user
// Returns the product whose name is clicked
Product* selectFromNearbyProducts(int x, int y, struct Node* closest) {
	clear();
	printBackButton();
	char instructions[] = "Click a product to select it, or 'back' to search again.";
	printCentered(y, instructions);
	struct Node* nearestProducts[5];
	char* productNames[6];

    // Find two predecessors and two succesors of the given AVL node
	nearestProducts[0] = closest;
	nearestProducts[1] = predecessor(closest);
	nearestProducts[2] = predecessor(nearestProducts[1]);
	nearestProducts[3] = successor(closest);
	nearestProducts[4] = successor(nearestProducts[3]);
	int maxLength = 0;
	char backButton[] = "   Back   ";
	productNames[0] = backButton;
    
    // Put the names of the products into a char** 
	for (int i = 0; i < 5; i++) {
		if (nearestProducts[i] == NULL) nearestProducts[i] = closest;
		char* name = nearestProducts[i]->product->name->contents;
		// printw("%d: %s\n", i, name);
		int nameLen = strlen(name);
		if (nameLen > maxLength) maxLength = nameLen;
		productNames[i + 1] = name;
	}
    // Pass the product names to a helper that will print and report a choice
	int choice = selectFromDiary(y + 4, x, productNames, 6);
	choice--; // convert user choice to index into products
    // Return the selected product
	if (choice < 0) return NULL;
	return nearestProducts[choice]->product;

}

// Reads a string to search. Handles clicks on the 'search' button and 'exit' buttons
string* readProductName(int startx, int starty, int maxLength, char delimiter, struct Node* productRoot) {
	noecho(); 
	string* input = newString();
	int ch;
	int x, y;
	MEVENT event;
	mousemask(ALL_MOUSE_EVENTS, NULL);

	char button[] = "  Search  ";
	attron(A_REVERSE);
	mvprintw(starty, startx, button);
	attroff(A_REVERSE);
	move(starty - 2, startx - 4);
    while (1) 
    {
		ch = getch();
		if (ch == delimiter && input->size != 0) break;
		if ((ch == 127 || ch == 8) && input->size > 0) { 
            //Handle backspace or delete
			popFromStr(input);
			getyx(stdscr, y, x);
			mvprintw(y, x-1, " ");
			mvprintw(y, x-1, "\0");
		} else if (ch >= 97 && ch <= 122 && input->size < maxLength) { 
            // Handle lowercase letters
			ch -= 32;
			pushToStr(input, ch);
			addch(ch);
		} else if (ch == '\n' && input->size != 0) {
			break;
		} else if (ch >= 32 && ch<126 && input->size < maxLength) {
            // Handle all other valid character codes
			pushToStr(input, ch);
			addch(ch);
		}  else if (ch == KEY_MOUSE) {
            // Handle click events
			if (exitButtonWasClicked(ch, event)) {
				return NULL;
			}
			if(getmouse(&event) == OK && input->size != 0){
				if (event.y == starty && event.x >= startx- 5 && event.x <= startx + 5)
					break;
			}
        }
    }
	return input;
}

// Reads a date. Handles clicks on the 'Enter' and 'Back' buttons
string* readDate(int startx, int starty, char delimiter, struct Node* productRoot) {
	noecho(); 
	string* input = newString();
	int ch;
	int x, y;
	MEVENT event;
	mousemask(ALL_MOUSE_EVENTS, NULL);

    // Print Enter Button
	char button[] = "  Enter  ";
	attron(A_REVERSE);
	mvprintw(starty, startx, button);
	attroff(A_REVERSE);
	move(starty - 2, startx + 4);

    // Get input
    while (1) 
    {
		ch = getch();
		if (ch == delimiter && input->size == 10) break;
		if ((ch == 127 || ch == 8) && input->size > 0) {
             // Handle backspace or delete
			if (input->size == 5 || input->size == 8) {
                // Automatically remove '/' characters
				popFromStr(input);
				getyx(stdscr, y, x);
				mvprintw(y, x-1, " ");
				mvprintw(y, x-1, "\0");
			}
			popFromStr(input);
			getyx(stdscr, y, x);
			mvprintw(y, x-1, " ");
			mvprintw(y, x-1, "\0");
		} else if (ch >= 48 && ch <= 57 && input->size < 10) {
            // Handle digit
			pushToStr(input, ch);
			addch(ch);
			if (input->size == 4 || input->size == 7) {
                // Automatically add '/' character
				pushToStr(input, '/');
				addch('/');
			}
		} else if (ch == KEY_MOUSE ) {
            // Handle click events
			if (exitButtonWasClicked(ch, event)) return NULL;
			if(getmouse(&event) == OK && input->size == 10){
				if (event.y == starty && event.x >= startx- 5 && event.x <= startx + 5)
				break;
			}
		}
		
    }
	return input;
}

// Reads a floating point value
double readFloat(int startx, int starty, char delimiter, struct Node* productRoot) {
	noecho(); 
	string* input = newString();
	int ch;
	int x, y;
	MEVENT event;
	mousemask(ALL_MOUSE_EVENTS, NULL);

    // Print Enter Button 
	char button[] = "  Enter  ";
	attron(A_REVERSE);
	mvprintw(starty, startx, button);
	attroff(A_REVERSE);
	move(starty - 2, startx + 4);

    // Get input
    while (1) 
    {
		ch = getch();
		if (ch == delimiter && input->size > 0) break;
		if ((ch == 127 || ch == 8) && input->size > 0) { 
            // Handle backspace or delete
			popFromStr(input);
			getyx(stdscr, y, x);
			mvprintw(y, x-1, " ");
			mvprintw(y, x-1, "\0");
		} else if (ch >= 48 && ch <= 57 && input->size < 5) {
            // Handle digit
			pushToStr(input, ch);
			addch(ch);
		} else if (ch == '.' && input->size != 0) {
            // Handle decimal
			int containsDecimal = 0;
			for (int i = 0; i < input->size; i++) { 
				// only allow one decimal per string 
				if (input->contents[i] == '.') containsDecimal = 1;
			}
			if (!containsDecimal){
				pushToStr(input, ch);
				addch('.');
			}
		}
		else if (ch == KEY_MOUSE ) {
            // Handle click events
			if (exitButtonWasClicked(ch, event)) return -5;
			if(getmouse(&event) == OK && input->size != 0){
				// printw("x, %d, y: %d", event.x, event.y);
				if (event.y == starty && event.x >= startx- 5 && event.x <= startx + 5)
				break;
			}
		}
		
    }
	double num = atof(input->contents);
	freeStr(input);
	return num;
}

// Reads a string of lowercase letters only
string* readString(int starty, int startx, int maxLength, char delimiter) {
	MEVENT event;
	mousemask(ALL_MOUSE_EVENTS, NULL);

	noecho();
	string* input = newString();
	int ch;
	int x, y;

    // Print Enter Button
	char button[] = "  Enter  ";
	attron(A_REVERSE);
	mvprintw(starty, startx, button);
	attroff(A_REVERSE);
	move(starty - 2, startx + 15);

    // Get input
    while (1) 
    {
		ch = getch();
		
		if (ch == delimiter && input->size != 0) break;
		if ((ch == 127 || ch == 8) && input->size > 0) { 
            // Handle backspace or delete
			popFromStr(input);
			getyx(stdscr, y, x);
			mvprintw(y, x-1, " ");
			mvprintw(y, x-1, "\0");
		} else if (ch >= 97 && ch <= 122 && input->size < maxLength) {
            // Handle Lowercase letters
			pushToStr(input, ch);
			addch(ch);
		} else if (ch >= 65 && ch <= 90 && input->size < maxLength) {
            // Handle uppercase letters
			ch += 32;
			pushToStr(input, ch);
			addch(ch);
		} else if (ch == KEY_MOUSE) {
            // Handle click events
			if (exitButtonWasClicked(ch, event)) {
				return NULL;
			}	
			if(getmouse(&event) == OK && input->size != 0){
				if (event.y == starty && event.x >= startx- 5 && event.x <= startx + 5)
				break;
			}
		} 
		refresh();
    }

    return input;
}

void printBackButton() {
	char exit[] =  "   Back   ";
	attron(A_REVERSE);
	// int x_coordinate = max(0, (COLS / 2  - 50));
	int x_coordinate = 0;
	int y_coordinate = 0;
	mvprintw(y_coordinate, x_coordinate, exit);
	attroff(A_REVERSE);
}
	

int exitButtonWasClicked(int input, MEVENT event) {
	int backHeight  = 0;
	int backX = 0;
	if (input == KEY_MOUSE) {
		if(getmouse(&event) == OK){
			if (event.y ==  backHeight && event.x >=  backX && event.x <= backX + 10)
				return 1;
		}
	}
	return 0;
}	


void printPreviousButton(vector* diary, int lastDisplayed, int instructionHeight) {
	if (lastDisplayed > 0) {
		attron(A_REVERSE);
		mvprintw(instructionHeight + 2, ( 2 * COLS / 7), " Previous ");
		attroff(A_REVERSE);
	}
}

void printNextButton(vector* diary, int lastDisplayed, int instructionHeight) {
	if ((lastDisplayed + 10) < diary->size) {
		attron(A_REVERSE);
		mvprintw(instructionHeight + 2, ( 4 * COLS / 7 + 10), "   Next   ");
		attroff(A_REVERSE);
	}
}

int previousButtonClicked(int input, MEVENT event) {
	int x = ( 2 * COLS / 7);
	int y = (LINES / 6 + 2);
	if (input == KEY_MOUSE) {
		if(getmouse(&event) == OK){
			if (event.y ==  y && event.x >=  x && event.x <= x + 10)
				return 1;
		}
	}
	return 0;
}

int nextButtonClicked(int input, MEVENT event) {
	int x = ( 4 * COLS / 7 + 10);
	int y = (LINES / 6 + 2);
	if (input == KEY_MOUSE) {
		if(getmouse(&event) == OK){
			if (event.y ==  y && event.x >=  x && event.x <= x + 10)
				return 1;
		}
	}
	return 0;
}

// Report which button was clicked on the update menu
int updateMenuButtonClicked(int input, MEVENT event) {
	int y = (LINES / 6 + 2);
	int itemx = ( 2 * COLS / 7);
	int datex = (COLS / 2 -8);
	int servingsx = ( 4 * COLS / 7 + 12);
	int donex= (COLS / 2 -8);
	int deletex = (COLS / 2 -8);
	if (input == KEY_MOUSE) {
		if(getmouse(&event) == OK){
			if (event.y ==  y && event.x >=  itemx && event.x <= itemx + 16)
				return -11;
			if (event.y ==  y && event.x >=  datex && event.x <= datex + 16)
				return - 10;
			if (event.y ==  y && event.x >=  servingsx && event.x <= servingsx + 16)
				return - 9;
			if (event.y ==  y + 2 && event.x >=  deletex && event.x <= deletex + 16)
				return - 8;
			if (event.y ==  y + 15 && event.x >=  donex && event.x <= donex + 16)
				return - 7;
		}
	}
	return 0;
}

void printExitButton() {
	char exit[] =  "   Exit   ";
	attron(A_REVERSE);
	// int x_coordinate = max(0, (COLS / 2  - 50));
	int x_coordinate = 0;
	int y_coordinate = 0;
	mvprintw(y_coordinate, x_coordinate, exit);
	attroff(A_REVERSE);
}

void printCancelButton() {
	char exit[] =  "  Cancel  ";
	attron(A_REVERSE);
	// int x_coordinate = max(0, (COLS / 2  - 50));
	int x_coordinate = 0;
	int y_coordinate = 0;
	mvprintw(y_coordinate, x_coordinate, exit);
	attroff(A_REVERSE);
}

void printUpdateMenuButtons() {
	int y = (LINES / 6 + 2);
	char item[] =     "    Update Item   ";
	char date[] =     "    Update Date   ";
	char servings[] = "  Update Servings ";
	char delete[]   = "      Delete      ";
	char done[]   =   "       Done       ";
	int itemx = ( 2 * COLS / 7);
	int datex = (COLS / 2 -8);
	int servingsx = ( 4 * COLS / 7 + 12);
	int deletex = (COLS / 2 -8);
	int donex= (COLS / 2 -8);
	attron(A_REVERSE);
	mvprintw(y, itemx, item);
	mvprintw(y, datex, date);
	mvprintw(y, servingsx, servings);
	mvprintw(y+2, deletex, delete);
	mvprintw(y+15,donex, done);
	attroff(A_REVERSE);
}

void printEntry(entry* ent) {
	int y = (LINES / 6 + 7);
	int x = (COLS / 2 - 8);
	Product* prod = ent->product;
	mvprintw(y, x, "Calories: %.1f", gramsCaloriesPerServing(prod) * ent->servings);
	mvprintw(y+1, x, "Carbs: %.1f g", gramsCarbsPerServing(prod)  * ent->servings);
	mvprintw(y+2, x, "Fat: %.1f g", gramsFatPerServing(prod)  * ent->servings);
	mvprintw(y+3, x, "Protein: %.1f g", gramsProteinPerServing(prod)  * ent->servings);
}

#endif
