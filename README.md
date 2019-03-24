
Getting Started: 
Clone this repository 'git clone https://github.com/pbevans1/portfolio.git'

Change into the 'portfolio/' directory by entering 'cd portfolio'.

Once the download is complete you have several options to build the project.
    1. Recommended: enter 'make build-all' at the command prompt.
            This will run shell scripts to download the appropriate files from the FDA, unzip them, and create the csv file expected by the program. It will then build the program.

    2. Super Space Saver: enter 'make' at the command prompt.
            Use only if you've already used the shell script provided by Dr. Anderson to create 'food_database.csv'. Copy 'food_database.csv' into the directory 'portfolio/data/' before using 'make'.

    3. Space Saver: enter 'make database' followed by 'make' at the command prompt.
            Use this option if you've already downloaded the FDA data files. Copy them into 'portfolio/dataBuilder/' before running 'make database'. If you want to download them manually, they can be found at https://www.ars.usda.gov/ARSUserFiles/80400525/Data/BFPDB/BFPD_csv_07132018.zip 

If you ever have questions about what the directory structure should look like, you can find a complete listing at the end of this document. 

When the project is built, use 'make run' to start the program. 


Help: 
    General: To use the program, type 'make run' and follow the directions on screen. You can use keyboard and mouse to navigate.
    Quitting: The exit button is in the top left corner.
    Username: If you've forgotten your username try 'make list-users'
    Help: You can use 'make help' to see these instructions again.






Final directory structure: 

├── README.md
├── basename
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
│   ├── food_database.csv
│   └── preston.log
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
├── ls
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