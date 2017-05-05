# Multiple Games (Nine Almonds, Magic Square, and Reversi) in C++

========================================================================
    CONSOLE APPLICATION : Lab4 Project Overview
========================================================================

Elliot  Yun Lab 4 					Student ID: 419298

========================================================================
TestCases:

* (for NineAlmonds) Again, Pieces.txt must be present for the program to run*
NineAlmonds: 
I tested similar patterns of inputs and game completions (including quits)
as lab2. It performed the same, successfully, as the code was simply refactored.
Pieces.txt is still used since the lab was based off of the earlier modules. 

MagicSquare:
Tested similar patterns as the NineAlmonds game since the prompt messages are
similar. 
Tested where the inputted string or value was not an integer. This notified 
the user of an invalid input. 
A piece that wasn't one of the pieces left was inputted. This prompted
the user that the piece was an invalid piece.
Finished the game in a stalemate. The returned result indicated a stalemate
Finished the game successfully. Returned 0. 
I had my game designed so that stalemate will only be checked when there 
are no pieces left to be placed. This makes sense as it would be pointless
to check before. The stalemate checks if the game is "done" as it can only
either be done or end with a stalemate. 
Sum of each row, column, and diagonal is updated every move the user makes
then are compared upon the depletion of all pieces.
I ran into errors mostly in the beginning, as I was refactoring my code 
and diving up the classes into base and derived classes. It was mostly syntax
errors and going through the notes was helpful in solving the problems. 

Reversi:

I played online reversi several times to fully grasp the concept of 
reversi and what moves are allowed and what aren't. When checking for the
validity and flipping the pieces accordingly if the move was valid, I used
the algorithm that first checks the next cell in the direction and continues
to check further only if the next piece is the opponent's piece. This makes
sense as if the immediately following piece is of your own or the cell is blank,
the particular move will be invalid. This uses the invariant that a 
valid move must be placed where at least a single opponent's piece is 
overtaken by the move. Then I repeat this algorithm for each of the 8 
different directions a move could take to over take the opponent's pieces.
I stop and record the ending piece, if the algorithm comes upon a piece that 
is of the same as the user whose turn it is. Otherwise, if I end up hitting
an empty spot I return that the particular move in the direction is not valid.
I utilize this similar algorithm to check for move availabilty through out the
board for each user, handling swapping turns accordingly. I've tested all possible
ways of over taking or flipping opponent's pieces as I have completed full 
games and observed that everything works correctly. The game correctly 
determines when there are no available moves currently for either user and 
switches the turns accordingly. The game correctly detects when it is done 
and determines whether there was a stalemate or not. 

========================================================================
Save Features:

For NineAlmonds only, one master save file "NineAlmonds.txt" exists. This
is because NineAlmonds has a static board size which means it's unnecessary
to have more than one game. For MagicSquare, since I have done the extra
credit portion for lab 3 I designed my code so that a save file will be created
for different dimensions and starting values (min values). An example of 
a save data for MagicSquare will be "MagicSquare 1 3.txt" which indicates
that the MagicSquare starts at 1 and has a 3x3 board. I believe this is 
necessary because users may want to save multiple games with different
specifications, thus creating a save file for each "type" of game for 
MagicSquare was necessary. Similarly, for Reversi I designed my code so that 
it creates a new save data file for each user pair. For instance, if 
Alice and Bob were playing and were player 1 and player 2 respectively,
the save file of the game between these two would be titled "Reversi Alice Bob.txt"
This is necessary since a user may want to save the game state that he/she
is playing with a particular user and may want to start a new game with a 
different user. These files are located and parsed as I check for their 
existence to notify the user of the validity of the save data between 
the two users given as command line arguments. I also ask whether the 
user wants to continue a save data or start anew, which I felt was necessary
since it would at more flexibility to the UI. If the user chooses not to continue,
a new game is initialized and the user (or users) can start over. 

Along with either "SAVE DATA" or "NO DATA" that populate every save data
I write/store the turn count variable for NineAlmonds and turn indicator for 
Reversi. These values are then parsed when the game is initialized 
and are assigned to variables accordingly to fully set up the game from 
the save data given. "NO DATA" results in a new game started, as is the 
same for when the file is blank (corrupted or empty).

Upon the load of save data, the status of the game is checked so that 
the game terminates if the save data already is completed or has a stalemate.
This is necessary because, although such state should never be saved 
by the user since the game would end right then when one of these conditions
have been met, the data might be manipulated or changed by external sources
and handling such erroneous data is crucial in implementing a successful 
game. 

========================================================================
Copy Control:

The use of copy constructors besides the default copy costructor was 
unnecessary for the work flow of my project as all initialization starts
right before the game actually starts and, therefore, didn't need to implement
the controls to have a successfully working lab. I made sure all the 
initiazlizing, error handling, and other setting up is done before a game
can fully start, thus providing the functionality of a custom constructor.
I do utilize a shared_ptr as mentioned in the instructions to keep track
of the retain count of the game object that is created at the start of 
the executable which should get destoryed once it goes out of scope or the 
executable is about to terminate. 

========================================================================
AppWizard has created this Lab4 application for you.

This file contains a summary of what you will find in each of the files that
make up your Lab3 application.


Lab4.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Lab4.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Lab4.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Lab3.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
