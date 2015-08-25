// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MagicSquare.h"
using namespace std;

// usage function to guide users on how to use the program.
void usage() {

	cout << "Usage: The Program supports the following variations of arguments (following the program executable)" << endl
		<< "[Argument1] [Argument2] [Argument3]" << endl
		<< "Argument1(required) - Must either be \"MagicSquare\" or \"NineAlmonds\" or \"Reversi\"" << endl
		<< "Argument2(not required) - Only Available for the MagicSquare Game. Specifies the edge of the square game board. Must be an number greater than 1." << endl
		<< "Argument3(not required) - Only Available for the MagicSquare Game. Specifies the Minimum value in which the pieces will start on. Value Must be an integer value" << endl
		<< "Argument2 and Argument3 are REQUIRED For the \"Reversi\" Option and Each Specify a User Name for Each Player." << endl;

}



// my design implements the printBoard function from lab1 thus the operator was not necessary as the board is updated after every move and is printed out using the printBoard. 
// There is a private member called "board" which is a vector of brownAlmonds and the state of the board was kept track updating that variable.

int main(int argc, char * argv[])
{
	GameBase *newGame;
	shared_ptr<GameBase> myPointer;
	try {
		newGame->command(argc, argv);
	}
	catch (errs e){
		usage();
		return e;
	}
	try {
		myPointer = newGame->instance();
	}
	catch (errs e){
		cout << "NullPointer" << endl;
		return e;
	}
	// if a bad argument was given a null pointer will be returned
	//GameBase *shared_ptr = newGame;
	// calling play of the class.
	int result = myPointer->play();
	// destroying (deallocing) the pointer and there for the allocated game
	//delete shared_ptr;
	return result;
}

