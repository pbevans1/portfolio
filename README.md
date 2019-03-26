
Important Notes:

1. This project requires mouse input for navigation. Make sure that your terminal is configured to pass mouse input to programs. 

2. This project is intended to be run in full screen mode. If the terminal window is too small, some buttons may be invisible.

Getting Started: 

Clone this repository 'git clone https://github.com/pbevans1/portfolio.git'

Change into the 'portfolio/' directory by entering 'cd portfolio'.

The project expects a tilde delimited csv file called 'food_database.csv' to be in the directory 'data'. The file is expected to be in the following format:
        product id~product name~manufacturer~energy units~carb units~fat units~protein units~serving size in grams or ml~grams or ml~serving size~serving size units
        Lines longer than 9000 characters are considered invalid. 


Once the download is complete you have several options to build the project.
    
    1. Recommended: enter 'make build-all' at the command prompt.
            This will run shell scripts to download the appropriate files from the FDA, unzip them, and create the csv file expected by the program. It will then build the program.

    2. Super Space Saver: enter 'make' at the command prompt.
            Use only if you've already used the shell script provided by Dr. Anderson to create 'food_database.csv'. Copy 'food_database.csv' into the directory 'portfolio/data/' before using 'make'.

    3. Space Saver: enter 'make database' followed by 'make' at the command prompt.
            Use this option if you've already downloaded the FDA data files. Copy them into 'portfolio/dataBuilder/' before running 'make database'. If you want to download them manually, they can be found at https://www.ars.usda.gov/ARSUserFiles/80400525/Data/BFPDB/BFPD_csv_07132018.zip 
 


When the project is built, use 'make run' to start the program. 



Help: 

    General: To use the program, type 'make run' and follow the directions on screen. Use the keyboard and mouse to navigate.
    
    Quitting: The exit button is in the top left corner.
    
    Username: If you've forgotten your username try 'make list-users.' If you want to make a new username, you can enter it just like you would enter an existing one.
    
    Help: You can use 'make help' to see these instructions again.


Technical Notes:

        The nutrition database is stored in memory as a self-balancing binary search tree (AVL Tree). It can run search in log n time, and builds in n log n time. 

        The user diary is stored as a dynamic array of entries. It maintains a sorted list, running a modified insertion sort on each entry as it is added. This allows constant time read and update access at the expense of O(n) insert and delete. Since the diary needs to be displayed in order, an array was a natural choice. In addition, since every entry is made manually through the user interface, the size of the diary is expected to be reasonably small so the cost of linear insert and delete is not expected to impact the user experience.


