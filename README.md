# Overview:

This project is a nutrition tracking program - it allows users to log their meals and track macro-nutrient intake using data from the FDA. It is built in ANSI C11, and depends on the curses library to implement its user interface. If curses isn't installed on your machine, you'll need to download it. A video demonstration of the final product can be found at FIXME.

# Important Set up:
1. Downloading curses - if curses isn't installed on your machine, you can follow these directions to install it: https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/

2. Entering full screen - This project is intended to be run in full screen mode. If the terminal window is too small, some buttons may be invisible.

3. (Hopefully done by default) Configuring you terminal - This project requires mouse input for navigation. If you can't click buttons inside the program, make sure that your terminal is configured to pass mouse input to programs. Unfortunately, this setting is specific to each terminal so I can't provide general directions. Thankfully, it seems to be enabled by default in most setups, so you probably don't need to worry about it. If you do need to change your settings, try searching for 'enable mouse input {your terminal name}'

4. (If you're running over ssh) Enable X11 Forwarding - ensure that both server and client are configured for X11 forwarding, and be sure to use the -Y option on you ssh comand. 'ssh -Y hostname@address'. Directions for configuring  X11 forwarding can be found at https://unix.stackexchange.com/questions/12755/how-to-forward-x-over-ssh-to-run-graphics-applications-remotely



# Getting Started: 

1. Clone this repository 'git clone https://github.com/pbevans1/portfolio.git'

1. Change into the 'portfolio/' directory by entering 'cd portfolio'.

1. You have several options to build the project.
    
    1. Recommended: enter 'make build-all' at the command prompt.
            This will run shell scripts to download all necessary files from the FDA website, unzip them, and create the csv file expected by the program. It will then build the program.

    1. Super Space Saver: place the file 'food_database.csv' into the 'portfolio/data/' directory, then enter 'make' at the command prompt.
            Use this option only if you've already used the shell script provided by Dr. Anderson to create 'food_database.csv' (If you're unsure what this script is or where to find it, this option isn't for you!). Be sure to copy 'food_database.csv' into the directory 'portfolio/data/' before using 'make', or the script will complain at you!

    1. Space Saver: Move 'Nutrients.csv', 'Serving_size.csv', and 'Products.csv' into the directory 'portfolio/dataBuilder/', then enter 'make database' followed by 'make' at the command prompt.
            Use this option if you've already downloaded and unzipped the FDA data files ('Nutrients.csv', 'Serving_size.csv', Products.csv') from https://www.ars.usda.gov/ARSUserFiles/80400525/Data/BFPDB/BFPD_csv_07132018.zip. Copy those three files into 'portfolio/dataBuilder/' before running 'make database'. 
 

# Running: 
- When the project is built, use 'make run' to start the program. 


## Expected Inputs: 
* The project expects a tilde delimited csv file called 'food_database.csv' to be in the directory 'data/'. The file is expected to be in the following format:
        product id\~product name\~manufacturer\~energy units\~carb units\~fat units\~protein units\~serving size in grams or ml\~grams or ml\~serving size\~serving size units  
* Lines longer than 9000 characters are considered invalid, and will not be read by the program.



## Help: 
- General: To use the program, type 'make run' and follow the directions on screen. Use the keyboard and mouse to navigate.
- Quitting: The exit button is in the top left corner.
- Username: If you've forgotten your username try 'make list-users.' If you want to make a new username, you can enter it at the prompt, just like you would enter an existing one. The program will create it for you automatically.
- Help: You can use 'make help' to see these instructions again.


## Technical Notes:

The nutrition database is stored in memory as a self-balancing binary search tree (AVL Tree). It can run search in log n time, and builds in n log n time. 

The user diary is stored as a dynamic array of entries. It maintains a sorted list, running a modified insertion sort on each entry as it is added. This allows constant time read and update access at the expense of O(n) insert and delete. Since the diary needs to be displayed in order, an array was a natural choice. Since every entry is made manually through the user interface, the size of the diary is expected to be reasonably small so the cost of linear insert and delete is not expected to impact the user experience.


## Some Helpful Commands:
- 'make' - this command will compile the project without running it. The executables are stored in 'portfolio/bin/'
- 'make clean' - this command will delete all executable files so the project can be rebuilt
- 'make run' - this command will compile (if necessary) and run the project
- 'make users' - this command will list every user who has a log file on the local machine
- 'make help' - will give a few hints about using the program
- 'make download' - will download and unzip the FDA nutrition database. The output is stored in 'portfolio/dataBuilder/'
- 'make database' - will convert 'portfolio/databuilder/{Nutrients|Products|Serving_size}.csv' into 'data/food_database.csv'
- 'make build-all' - combines 'make', 'make download', and 'make database' into a single command
- 'make clean-all' - will delete all executable and data files (undoes 'make build-all')


## Organization:
- The top level directory 'portfolio/' contains the makefile, the readme, and several subdirectories. All 'make' commands should be run from this directory.   
- All C source code is found in the 'portfolio/src/' directory. Code is split between 'library/', which contains code that is general (as opposed to being tied tightly to this project), and 'project/', which contains application specific code.    
- Shell scripts, which are used to download and unzip the FDA files, as well as to build 'food_database.csv' can be found in the 'shellScripts/' directory. 
- The 'data/' directory is where 'food_database.csv' should be. It will also hold user log files once they are created.
- The 'dataBuilder/' directory is where the FDA files live. It also contains some intermediate files created by 'buildData.sh'
- Dont' worry if not all of these directories are present on download. The Makefile will create them when they're needed.
        
        

## Final Directory Structure:
<pre>
├── README.md
├── bin
│   ├── avlTree.o
│   ├── customString.o
│   ├── diary.o
│   ├── displayHelper.o
│   ├── main.out
│   ├── main.out.dSYM
│   │   └── Contents
│   │       ├── Info.plist
│   │       └── Resources
│   │           └── DWARF
│   │               └── main.out
│   ├── mainMenu.o
│   ├── products.o
│   ├── read.o
│   └── vector.o
├── data
│   └──food_database.csv
├── dataBuilder
│   ├── BFPD_Doc.pdf
│   ├── BFPD_csv_07132018.zip
│   ├── Derivation_Code_Description.csv
│   ├── Nutrients.csv
│   ├── Products.csv
│   ├── Serving_size.csv
│   ├── carbs
│   ├── ec
│   ├── energy
│   ├── fat
│   ├── fp
│   ├── nutrients
│   ├── pn
│   ├── product
│   ├── protein
│   └── serving
├── makefile
├── shellScripts
│   ├── buildData.sh
│   └── download.sh
└── src
    ├── library
    │   ├── avlTree.c
    │   ├── avlTree.h
    │   ├── customString.c
    │   ├── customString.h
    │   ├── displayHelper.c
    │   ├── displayHelper.h
    │   ├── vector.c
    │   └── vector.h
    └── project
        ├── diary.c
        ├── diary.h
        ├── main.c
        ├── mainMenu.c
        ├── mainMenu.h
        ├── products.c
        ├── products.h
        ├── read.c
        └── read.h
