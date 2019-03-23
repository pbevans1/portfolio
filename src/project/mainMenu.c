#ifndef __MAIN__MENU__C
#define __MAIN__MENU__C
#include "mainMenu.h"

struct user {
    vector* diary;
    string* username;
};

struct user* getUserDiaryMenu(struct Node*);
void diaryCrudMenu(vector* diary, struct Node*, string* username);
char** formatNextTenEntries(vector* diary, int startNum, char* button);
int numEntries(char** formattedEntries);

string* displayMainMenu(struct Node* productRoot)  {
    vector* userDiary;
    /* From http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html */
    initscr();			    /* Start curses mode */
    start_color();			/* Start color functionality */
    keypad(stdscr, TRUE);   /* Accept keyboard input  */
    cbreak();               /* Don't wait for newline when reading characters */
    noecho();			    /* Don't echo while we do getch */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    string* username = NULL;
    struct user* currentUser = getUserDiaryMenu(productRoot);
    username = currentUser->username;
    userDiary = currentUser->diary;
    diaryCrudMenu(userDiary, productRoot, username);
    finish(0);
    return username;
}

void diaryAddMenu(vector* diary, struct Node* productRoot, string* username) {
    
    string* name = NULL;
    int instructionHeight = LINES / 6;
    char instructions[] = "What kind of food did you eat? ";
    char servingInstructions[] = "How many servings did you eat?";
    char dateInstructions[] = "What was the date?";

    Product* product = NULL;
    string* date = NULL;
    double numServings = 0;
    struct Node* nearestNode;
    entry* new;
    /*  Get product */
    while (1) {
        clear();
        printExitButton();
        printCentered(instructionHeight, instructions);
        mvprintw(instructionHeight + 1, COLS/2 - 20, "Item Name: ");
        name = readProductName((COLS / 2) - 5, instructionHeight + 3, 100, '\n', productRoot);
        if (name == NULL) saveAndQuit(diary, username);
        nearestNode = findClosestNode(productRoot, name->contents);
        product = selectFromNearbyProducts(COLS / 3, instructionHeight, nearestNode);
        
        if (product != NULL) break;
    }
    while (1) {
        clear();
        printExitButton();
        printCentered(instructionHeight, dateInstructions);
        mvprintw(instructionHeight + 1, COLS/2 - 20, "Date (yyyy/mm/dd): ");
        date = readDate((COLS / 2) - 5, instructionHeight + 3, '\n', productRoot);
        if (date == NULL) saveAndQuit(diary, username);
        break;
    }
    while (1) {
        clear();
        char* productInfo = malloc(sizeof(char) * 500);
        sprintf(productInfo, "A serving of %s is %.2f %s", 
            product->name->contents, product->serving_size, product->serving_units->contents);
        printCentered(instructionHeight - 1, servingInstructions);
        printCentered(instructionHeight, productInfo);
        free(productInfo);
        printExitButton();
        mvprintw(instructionHeight + 1, COLS/2 - 22, "Servings (i.e 1.0): ");
        numServings = readFloat((COLS / 2) - 5, instructionHeight + 3, '\n', productRoot); 
        if (numServings < 0) saveAndQuit(diary, username);
        break;
    }
    new = entryFromProduct(product, date, numServings);
    if (new == NULL) {
        printw("ERROR NULL");
        getch();
    }
    insertIntoDiary(diary, new);
}

void diaryUpdateMenu(vector* diary, int index, struct Node* productRoot, string* username) {
    mousemask(ALL_MOUSE_EVENTS, NULL);
	MEVENT event;
    int instructionHeight = LINES / 6;
    int choice = 0;
    entry* ent = diary->contents[index];
    char instructions[] = "What kind of food did you eat? ";
    char servingInstructions[] = "How many servings did you eat?";
    char dateInstructions[] = "What was the date?";
    string* name;
    Product* product;
    string* date;
    struct Node* nearestNode;
    int numServings;
    while(1) {
        char* itemInfo = malloc(sizeof (char) * 500);
        clear();
        printExitButton();
        sprintf(itemInfo,  "On %s you ate %.1f servings of %s.", ent->date->contents, 
                    ent->servings, ent->product->name->contents);
        printCentered(instructionHeight, itemInfo);
        free(itemInfo);
        printUpdateMenuButtons();
        printEntry(ent);
        int input = getch();
        if (input == KEY_MOUSE) {
            if(getmouse(&event) == OK){
                choice = exitButtonWasClicked(input, event);
                if (choice == 1) saveAndQuit(diary, username);
                choice = updateMenuButtonClicked(input, event);
            }
        }
        if (choice == -11) {
            /*  Get new product */
            while (1) {
                clear();
                printExitButton();
                printCentered(instructionHeight, instructions);
                mvprintw(instructionHeight + 1, COLS/2 - 20, "Item Name: ");
                name = readProductName((COLS / 2) - 5, instructionHeight + 3, 100, '\n', productRoot);
                if (name == NULL) saveAndQuit(diary, username);
                nearestNode = findClosestNode(productRoot, name->contents);
                product = selectFromNearbyProducts(COLS / 3, instructionHeight, nearestNode);
                
                if (product != NULL) break;
            }
            ent->product = product;
            freeStr(ent->key);
            ent->key = joinStr(ent->date, ent->product->name, ": ");
        } 
        if (choice == -10) {
            /*  Get new date */
            while (1) {
                clear();
                printExitButton();
                printCentered(instructionHeight, dateInstructions);
                mvprintw(instructionHeight + 1, COLS/2 - 20, "Date (yyyy/mm/dd): ");
                date = readDate((COLS / 2) - 5, instructionHeight + 3, '\n', productRoot);
                if (date == NULL) saveAndQuit(diary, username);
                break;
            }
            freeStr(ent->date);
            ent->date = date;
            freeStr(ent->key);
            ent->key = joinStr(ent->date, ent->product->name, ": ");
        }
        if (choice == -9) {
            /* Get new servings*/
            while (1) {
                clear();
                char* productInfo = malloc(sizeof(char) * 500);
                sprintf(productInfo, "A serving of %s is %.2f %s", 
                    ent->product->name->contents, ent->product->serving_size, ent->product->serving_units->contents);
                printCentered(instructionHeight - 1, servingInstructions);
                printCentered(instructionHeight, productInfo);
                free(productInfo);
                printExitButton();
                mvprintw(instructionHeight + 1, COLS/2 - 22, "Servings (i.e 1.0): ");
                numServings = readFloat((COLS / 2) - 5, instructionHeight + 3, '\n', productRoot); 
                if (numServings < 0) saveAndQuit(diary, username);
                break;
            }
            ent->servings = numServings;
        }
        if (choice == -8) {
            /* Get new servings*/
            deleteAtIndex(diary, index);
            break;
        }
        if (choice == -7) {
            deleteAtIndex(diary, index);
            insertIntoDiary(diary, ent);
            break;
        }
    }

}

void diaryCrudMenu(vector* diary, struct Node* productRoot, string* username) {
    int instructionHeight = LINES / 6;
    char instructions[] = "Click any entry view, modify, or delete it, or press the button to add a new one.";
    int lastEntryDisplayed = 0;
    char addButton[] = " New Entry";
    char** currentPage;
    int numToDisplay, x, choice;
    while(1) {
        clear();
        printExitButton();
        printPreviousButton(diary, lastEntryDisplayed, instructionHeight);
        printNextButton(diary, lastEntryDisplayed, instructionHeight);
        printCentered(instructionHeight, instructions);
        currentPage = formatNextTenEntries(diary, lastEntryDisplayed, addButton);
        numToDisplay = numEntries(currentPage);
         x = (COLS / 4);
        
        choice = selectFromDiary(instructionHeight + 2, x, currentPage, numToDisplay + 1);
        if (choice == -5) saveAndQuit(diary, username);
        if (choice == -3 && lastEntryDisplayed > 0) {
            lastEntryDisplayed = max(lastEntryDisplayed - 10, 0);
            continue;
        }
         if (choice == -1 && (lastEntryDisplayed + 10) < diary->size) {
            lastEntryDisplayed = min(lastEntryDisplayed + 10, diary->size);
            continue;
        }
        if (choice == 0) diaryAddMenu(diary, productRoot, username);
        if (choice >= 1 && choice <= 10) diaryUpdateMenu(diary, (choice - 1 + lastEntryDisplayed), productRoot, username);
    }
}

int numEntries(char** formattedEntries) {
    int i;
    for (i = 1; i < 11; i++) {
        if (formattedEntries[i] == NULL) break;
    }
    return i - 1;
}

char** formatNextTenEntries(vector* diary, int startNum, char* button) {
    int i;
    char** formattedEntries = malloc(sizeof(char*) * 11);
    int entriesIndex;
    entriesIndex = 1;
    formattedEntries[0] = button;

    /* Fill up to 10 empty slots */
    for (i = startNum; i < diary->size && entriesIndex < 11; i++) {
        entry* currentEntry = (entry*) diary->contents[i];
        formattedEntries[entriesIndex] = formatEntry(currentEntry);
        entriesIndex++;
    }
    /* Write NULLs to empty slots */
    for (i = entriesIndex; i < 11; i++) {
        formattedEntries[i] = NULL;
    }
    return formattedEntries;
}

struct user* getUserDiaryMenu(struct Node* productRoot) {
    /* Open Welcome Screen */
    WINDOW* start_menu = newwin(0, 0, LINES, COLS);
    char welcome[] = "Welcome to NutritionTracker!";
    int welcomeHeight = LINES / 6;
    int choice, startx;
    char instructions[] = "Enter a username to continue: ";
    char* options[] = {"Start a new diary ", "Enter a different username"};
    char* foundOptions[] = {"Open it", "Overwrite it", "Enter a different username"};
    struct user* currentUser = malloc(sizeof(struct user));
    string* username = NULL;
    while (1) {
        clear();
        printCentered(welcomeHeight, welcome);
        /* Get Username	*/
        printExitButton();
        /* printBackButton(); */
        mvprintw(welcomeHeight + 3, ((COLS - 40) / 2), instructions);
        username = readString(welcomeHeight+5, ((COLS - 10) / 2), 50, '\n');
        if (username == NULL) finish(0); /*  if exit button was clicked*/
        /* move(welcomeHeight+3, 0); */
        currentUser->username = username;
        clear();
        printExitButton();
        startx = (COLS - username->size - 8) / 2;
        mvprintw(welcomeHeight, startx, "Hello %s!", username->contents);

        
        /*Check for log file */
        if (!logFileExists(username->contents)) {
            printCentered(welcomeHeight+2, "We couldn't find any old log files for you");
            choice = selectFromChoices(start_menu, welcomeHeight+4, (COLS - 30) / 2, options, 2);
            if (choice == -5) finish(0);
            choice++; /* Convert choice from index to counting number; */
            if (choice == 1) {
                destroyWindow(start_menu);
                currentUser->diary = newVector();
                return currentUser;
            }    
            if (choice == 2) continue;
        } else {
            printCentered(welcomeHeight+2, "We found your last save! Would you like to... ");
            choice = selectFromChoices(start_menu, welcomeHeight+4, (COLS - 30) / 2, foundOptions, 3);
            if (choice == -5) finish(0);
            choice++; /*  Convert choice from index to counting number; */
            if (choice == 1) {
                destroyWindow(start_menu);
                currentUser->diary = readDiary(username->contents, productRoot);
                return currentUser;
            }
            if (choice == 2) {
                destroyWindow(start_menu);
                currentUser->diary = newVector();
                return currentUser;
            }
            if (choice == 3) continue;
            
        }
    }
    
    getch();
    /* Unreachable */
    printf("Uh-oh! We reached unreachable!");
    getch();
    destroyWindow(start_menu);

    return currentUser;
} 


void finish(int sig) {
        endwin();
        /* do your non-curses wrapup here */
        exit(0);
}

void saveAndQuit(vector* diary, string* username) {
    saveDiary(diary, username);
    finish(0);
}



#endif
