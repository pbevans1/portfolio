
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
 

When the project is built, use 'make run' to start the program. 


Help: 
    General: To use the program, type 'make run' and follow the directions on screen. You can use keyboard and mouse to navigate.
    
    Quitting: The exit button is in the top left corner.
    
    Username: If you've forgotten your username try 'make list-users'
    
    Help: You can use 'make help' to see these instructions again.

