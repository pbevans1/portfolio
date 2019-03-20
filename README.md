
Getting Started: 
Clone this repository 'git clone https://github.com/pbevans1/portfolio.git'


Once the download is complete you have several options to build the project.
    1. Recommended: enter 'make build-all' at the command prompt.
            This will run shell scripts to download the appropriate files from the FDA, unzip them, and create the csv file expected by the program. It will then build the program.

    2. Super Space Saver: enter 'make' at the command prompt.
            Use only if you've already used the shell script provided by Dr. Anderson to create 'food_database.csv'. Copy 'food_database.csv' into the directory 'portfolio/data/' before using 'make'.

    3. Space Saver: enter 'make database' followed by 'make' at the command prompt.
            Use this option if you've already downloaded the FDA data files. Copy them into 'portfolio/dataBuilder/' before running 'make database'.

If you ever have questions about what the directory structure should look like, you can find a complete listing at the end of this document. 

When the project is built, use 'make run' to start the program. 


Help: 
    This project was built using ncurses. In general, you have several options at any given prompt. 

        1. Use the mouse to click on an option
        2. Press a numeric key to select the corresponding option.
        3. Use the up and down arrows and 'enter' key to select an option.




Final Directory Structure:
    .
    ├── README.md
    ├── bin
    │   ├── avlTree.o
    │   ├── customString.o 
    │   ├── displayHelper.o
    │   ├── hashTable.o
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
    │   └── food_database.csv
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
            ├── hashTable.c
            ├── hashTable.h
            ├── main.c
            ├── mainMenu.c
            ├── mainMenu.h
            ├── makefile
            ├── products.c
            ├── products.h
            ├── read.c
            ├── read.h
            ├── serving.c
            └── serving.h

