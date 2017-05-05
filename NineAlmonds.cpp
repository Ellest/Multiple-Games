#include "stdafx.h"
#include "NineAlmonds.h"
#define WIDTH 6
#define numPiece 9
#define MIN 0
#define MAX 4
#define REMOVE -1

void NineAlmonds::print()
{
	cout << *this;
}

// save method
void NineAlmonds::save(string s){
	ofstream saveFile;
	string fileName = "NineAlmonds.txt";
	saveFile.open(fileName);
	string y = "yes";
	if (s.compare(y) == 0){
		int iVal;
		// writes SAVE DATA along with the current turncount
		saveFile << "SAVE DATA " << turnCount << endl;
		// for each game board cell
		for (unsigned int j = 1; j < height; j++){
			for (unsigned int i = 1; i < width; i++){
				iVal = width * j + i;
				if (board[iVal].display == "A"){
					// stores the x and y coordinates
					saveFile << i - 1 << " " << j - 1 << endl;
				}
			}
		}
		saveFile.close();
	}
	else {
		// writes NO DATA if user decides not to save.
		saveFile << "NO DATA" << endl;
		saveFile.close();
	}
}

ostream &operator<< (ostream &os, const NineAlmonds &na)
{
	os << endl;
	unsigned int height = na.height;
	unsigned int width = na.width;
	int longest = na.longest;
	vector<brownAlmond> board = na.board;
	for (int y = height - 1; y >= 0; y--){

		for (unsigned int x = 0; x < width; x++){
			int ind = (width * y) + (x);
			// checks if the color is either invalid or none. If it is so, the piece will be displayed as "Piece Color Error." This adds additional functionality as it tells the user what was wrong with the piece
			if (board[ind].display == "A"){
				os << setw(longest + 1) << board[ind].display << setw(longest + 1);
			}
			// If nothing was wrong with the piece print piece as it is.
			else if (!board[ind].display.empty() && board[ind].display != "A"){
				os << setw(longest + 1) << board[ind].display << setw(longest + 1);
			}
			else {
				os << setw(longest + 1) << board[ind].display << setw(longest + 1);
			}
			//At the last (righter-most) x coordinate 
			if (x == width - 1){
				os << endl << endl;
			}
		}

	}
	return os;
}

int NineAlmonds::boardDimension(ifstream& ifs, unsigned int& i, unsigned int& j){

	string dim;
	//getline extracts the line and stores it into the string variable dim
	if (getline(ifs, dim)){
		istringstream iss(dim);
		//if exactly two int variables were successfully extracted
		if (iss >> i && iss >> j){
			setWidth(i);
			setHeight(j);
			return errs::Success;
		}
		else{
			return errs::ExtractionError;
		}
	}
	else{
		//GetLineError is returned if the function failed to retrieve 2 integers for the width and height
		return errs::GetLineError;
	}

}

//done method
bool NineAlmonds::done(){
	vector<brownAlmond> vect;
	//checks all piece using a for loop and a helper method to retrieve each piece
	for (int i = 1; i <= numPiece; i++){
		brownAlmond ba = getPiece(i);
		//if the piece has been erased the coordinates (both x and y) will be set to -1. Thus if the piece has a coordinate of -1 then the piece must have been deleted from the board.
		if (ba.getX() != -1){
			vect.push_back(ba);
		}
	}
	// check how many pieces are left if more than 1 are left on the board return false.
	if (vect.size() >= 2){
		return false;
	}
	else {
		//if the single remaining piece is on the middle square, or coordinate "2,2", then return true
		if (vect[0].getX() == 2 && vect[0].getY() == 2){
			return true;
		}
		// if the last piece is not at "2,2", then the game isn't finished. This will lead to a stalemate which is checked in the stalemate method.
		else{
			return false;
		}
	}
}

int NineAlmonds::boardPieces(ifstream& ifs, vector<brownAlmond>& v){
	/*correctNum is utilized to check if no pieces were successfully extracted and stored.
	if correctNum = 0 at the end then the function returns an error associated with the
	enumeration label "extractionError"*/

	//set board coordinate labels. 
	v[0].display = "+"; v[1].display = "0"; v[2].display = "1"; v[3].display = "2"; v[4].display = "3"; v[5].display = "4";


	v[6].display = "0";


	v[12].display = "1";


	v[18].display = "2";


	v[24].display = "3";


	v[30].display = "4";

	int correctNum = 0;
	string pieces;
	string color;
	string display;
	unsigned int x;
	unsigned int y;
	int index;
	// pieceCount variable is used to assign an integer value (1-9) for each piece. 
	int pieceCount = 1;
	while (getline(ifs, pieces)){
		istringstream iss(pieces);
		//checks if all the extractions were successful if not move on to else to do nothing
		if (iss >> color && iss >> display && iss >> x && iss >> y){
			if (pieceCount <= numPiece){
				// this gets a reference to the first piece, then modifies it. The second run of the loop will get the reference to the second piece and so on.
				brownAlmond& piece = getPiece(pieceCount);
				piece.color = colorString(color);
				//here I check whether the piece's name (type) matches any of the types that should be passed in. If there isn't a match then the name (type) of the piece is set to "invalid."
				if (piece.color != "brown"){
					// if the color is not brown then the piece color will be set to Invalid. 
					piece.color = "Invalid";
					piece.display = display;
					// the following three lines of code sets the piece's x and y coordinate and the piece's index value on the board.
					piece.setX(x);
					piece.setY(y);
					piece.setIndex(width, x, y);
					index = piece.getIndex();
					// stores the piece on the board.
					v[index] = piece;
					correctNum++;
					iss.str("");
				}
				// if the color of the piece is brown (which should be) then set everything else as well.
				else {
					piece.display = display;
					// the following three lines of code sets the piece's x and y coordinate and the piece's index value on the board.
					piece.setX(x);
					piece.setY(y);
					piece.setIndex(width, x, y);
					index = piece.getIndex();
					// stores the piece on the board.
					v[index] = piece;
					correctNum++;
					//flushing the istringstream
					iss.str("");
				}
				//if the type is neither a no-match nor Checkers, then the type must belong to the chess enumerated display set.
			}
			else {
				//flushing the istringstream
				iss.str("");
				//continue on to next piece if the location of the piece is out of bounds
			}
			pieceCount++;
		}
	}
	if (correctNum != 0){
		return errs::Success;
	}
	else{
		return errs::ExtractionError;
	}


}

void NineAlmonds::checkMove(vector<brownAlmond> &checkList, int x, int y)
{
	for (int i = 1; i < 10; i++){
		// retrieves a piece. The for loop will check all pieces
		brownAlmond piece = getPiece(i);
		int xC = piece.getX();
		int yC = piece.getY();
		int iC = piece.getIndex();
		if (xC == x && yC == y){
			// do not include if it's the same piece
		}
		else if (xC < MIN || yC < MIN){
			// do not include non-existant piece (or erased piece)
		}
		// checks if the piece can move down (by overtaking another piece)
		else if (xC == x && yC + 1 == y && yC != MIN){
			// if there isn't a piece below the piece being checked.
			if (board[iC - 6].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move up
		else if (xC == x && yC - 1 == y && yC != MAX){
			// if there isn't a piece above the piece being checked.
			if (board[iC + 6].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move to the left
		else if (yC == y && xC + 1 == x && xC != MIN){
			// if there isn't a piece left to the piece being checked.
			if (board[iC - 1].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move to the right
		else if (yC == y && xC - 1 == x && xC != MAX){
			// if there isn't a piece right to the piece being checked.
			if (board[iC + 1].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move diagonally southwest
		else if (yC + 1 == y && xC + 1 == x && xC != MIN && yC != MIN){
			// if there isnt'a piece southwest to the piece being checked.
			if (board[iC - 7].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move diagonally northeast
		else if (yC - 1 == y && xC - 1 == x && xC != MAX && yC != MAX){
			// if there isn't a piece northeast to the piece being checked
			if (board[iC + 7].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move diagonally northwest
		else if (yC - 1 == y && xC + 1 == x && xC != MIN && yC != MAX){
			// if there isn't a piece northwest to the piece being checked.
			if (board[iC + 5].display != "A"){
				checkList.push_back(piece);
			}
		}
		// checks if the piece can move diagonally southeast
		else if (yC + 1 == y && xC - 1 == x && xC != MAX && yC != MIN){
			// if there isn't a piece southeast to the piece being checked.
			if (board[iC - 5].display != "A"){
				checkList.push_back(piece);
			}
		}
	}
}

bool NineAlmonds::stalemate()
{
	//checks if done is true, if it is then stalemate returns false;
	if (done()){
		return false;
	}
	else{
		vector<brownAlmond> check;
		//checks all piece using a for loop and a helper method to retrieve each piece. 
		for (unsigned int i = 1; i < 10; i++){
			brownAlmond piece = getPiece(i);
			// if a piece has been deleted, then omit the piece.
			if (piece.getX() != -1){
				check.push_back(piece);
			}
		}
		//if done isn't true and there is only one piece left, then return true.
		if (check.size() < 2){
			return true;
		}
		// this double for loops compares each piece against every other piece to see if the two are adjacent to each other, else stalemate returns true.
		// Altough the algorithm used here has a runtime of n^2, there are only 9 pieces in this game and I figured with only 9 pieces this algorithm would not affect the running time by much.
		for (unsigned int i = 0; i < check.size(); i++){
			brownAlmond piece = check[i];
			int x1 = piece.getX();
			int y1 = piece.getY();
			for (unsigned int j = i + 1; j < check.size(); j++){
				brownAlmond piece2 = check[j];
				int x2 = piece2.getX();
				int y2 = piece2.getY();
				if (x1 == x2){
					// if the two are vertically adjacent
					if (y1 + 1 == y2 || y1 - 1 == y2){
						return false;
					}
				}
				else if (y1 == y2){
					// if the two are horizontally adjactent
					if (x1 + 1 == x2 || x1 - 1 == x2){
						return false;
					}
				}
				else if (x1 == x2 - 1){
					// if the two are diagonally (right) adjacent
					if (y1 == y2 - 1 || y1 == y2 + 1){
						return false;
					}
				}
				else if (x1 == x2 + 1){
					// if the two are diagonally (left) adjacent
					if (y1 == y2 - 1 || y1 == y2 + 1){
						return false;
					}
				}
			}
		}
		// if the code reaches this point then that means none of the conditions in the for loop was true for every possible pair of pieces. Thus, there is a stalemate at hand.
		return true;
	}
}

int NineAlmonds::prompt(unsigned int &a, unsigned int &b)
{
	// asks the user to pick a piece
	cout << "Type the Coordinate \"X,Y\" of a Piece to Move | Type \"Quit\" to Stop Playing : ";
	string s;
	int o = 0;
	getline(cin, s);
	// if the input was empty
	if (s.empty()){
		cout << "********* Invalid Input! (Empty) ********* Must Type a Command *********" << endl;
		return IncorrectCommand;
	}
	// else if the user indicated to quit
	else if (s == "Quit"){
		// checks if the user did want to Quit.
		cout << "Are You Sure? (y/n) : ";
		string c;
		getline(cin, c);
		// if yes
		if (c == "y"){
			cout << "Save Current Game State? (y/n) : ";
			string res;
			getline(cin, res);
			while (res != "y" && res != "n"){
				cout << "Save Current Game State? (y/n) : ";
				getline(cin, res);
			}
			string yes = "yes";
			string no = "no";
			if (res == "y"){
				save(yes);
				//d = 1;
			}
			else {
				save(no);
			}
			cout << "Good Bye" << endl;
			//d = 1;
			return Quit;
		}
		// if no
		else if (c == "n"){
			cin.clear();
			return IncorrectCommand;
		}
		// if neither y or n
		else {
			cout << "Must Type y or n!" << endl;
			cin.clear();
			return IncorrectCommand;
		}

	}
	else{
		int count = 0;
		// for all chars in the string extracted.
		for (char& c : s){
			// increment the count if there is a comma. 
			if (c == ','){
				c = ' ';
				count++;
			}
			//checks if a character is neither a comma nor a digit. Re-promts the user if this is the case.
			else if (!isdigit(c)){
				cout << "********* Invalid Input! (Non-Digit) ********* X and Y Must Be Numbers *********" << endl;
				cin.clear();
				return IncorrectCommand;
			}
		}
		//checks if there was exactly one comma. Will prevent syntax error in input
		if (count != 1){
			cout << "********* Invalid Input! ********* Recheck Input Format (example:  3,2) *********" << endl;
			cin.clear();
			return IncorrectCommand;
		}
		// initiating variables x and y to extract the input stream into. 
		int x;
		int y;
		istringstream iss(s);
		// if exactly 2 integers were extracted
		if (iss >> x && iss >> y){
			if (x < MIN || x > MAX || y < MIN || y > MAX){
				cout << "********* Invalid Input! (Out of Bounds) ********* Check the Board Coordinates *********" << endl;
				cin.clear();
				return IncorrectCommand;
			}
			else{
				// since a and b are references, assigning x and y to a and b respectively will change the values of the two parameters passed in outside of the method.
				a = x;
				b = y;
				return Success;
			}
		}
		// if the extraction of 2 variables failed. 
		else {
			cout << "extraction failure" << endl;
			cin.clear();
			return IncorrectCommand;
		}
	}
}

int NineAlmonds::prompt(unsigned int &a, unsigned int &b, int overLoad)
{
	// changed statement to ask the destination instead.
	cout << "Type the Coordinate \"X,Y\" to Move to | Type \"Quit\" to Stop Playing : ";
	string s;
	int o = 0;
	getline(cin, s);
	// if the string is empty notify the user of the error.
	if (s.empty()){
		cout << "********* Invalid Input! (Empty) ********* Must Type a Command *********" << endl;
		return IncorrectCommand;
	}
	// if it isn't empty check if the user decided to quit by typing "Quit"
	else if (s == "Quit"){
		// double check for improved usage.
		cout << "Are You Sure? (y/n) : ";
		string c;
		getline(cin, c);
		// if user inputted yes
		if (c == "y"){
			cout << "Save Current Game State? (y/n) : ";
			string res;
			getline(cin, res);
			while (res != "y" && res != "n"){
				cout << "Save Current Game State? (y/n) : ";
				getline(cin, res);
			}
			string yes = "yes";
			string no = "no";
			if (res == "y"){
				save(yes);
				//d = 1;
			}
			else {
				save(no);
			}
			cout << "Good Bye" << endl;
			//d = 1;
			return Quit;
		}
		// if user decided not to quit throw Incorrect command and resume the loop.
		else if (c == "n"){
			// clear the input stream
			cin.clear();
			return IncorrectCommand;
		}
		// if the answer was neither "y" nor "n" then prompt the user of the correct usage
		else {
			cout << "Must Type y or n!" << endl;
			// clear the input stream
			cin.clear();
			return IncorrectCommand;
		}
	}
	//if the answer stream was neither empty nor "Quit"
	else{
		int count = 0;
		// for all chars in the string extracted.
		for (char& c : s){
			if (c == ','){
				c = ' ';
				count++;
			}
			//checks if a character is neither a comma nor a digit. Re-promts the user if this is the case.
			else if (!isdigit(c)){
				cout << "********* Invalid Input! (Non-Digit) ********* X and Y Must Be Numbers *********" << endl;
				cin.clear();
				return IncorrectCommand;
			}
		}
		//checks if there was exactly one comma. Will prevent syntax error in input
		if (count != 1){
			cout << "********* Invalid Input! ********* Recheck Input Format (example:  3,2) *********" << endl;
			cin.clear();
			return IncorrectCommand;
		}
		// 2 variables to be used for extraction
		int x;
		int y;
		//wrapping string in an istringstream
		istringstream iss(s);
		// if extraction onto exactly 2 integers was successful
		if (iss >> x && iss >> y){
			if (x < MIN || x > MAX || y < MIN || y > MAX){
				cout << "********* Invalid Input! (Out of Bounds) ********* Check the Board Coordinates *********" << endl;
				cin.clear();
				return IncorrectCommand;
			}
			else{
				// a and b are references, changing them would affect the variables even outside the function, which we want. 
				a = x;
				b = y;
				return Success;
			}
		}
		// if the extraction was not successful.
		else {
			cout << "extraction failure" << endl;
			cin.clear();
			return IncorrectCommand;
		}
	}
}

int NineAlmonds::turnHelper(int board[WIDTH][WIDTH], int x1, int y1, int x2, int y2)
{
	//utilize the helper method to get the piece that was on that specific index of the board (overtaken)
	brownAlmond& b = getPieceByCord(x1, y1);
	// delete the piece from the board display
	board[b.getIndex()].display = "";
	// set the index of the piece with coordinate -1,-1 which indicates a deleted piece
	b.setIndex(WIDTH, -1, -1);
	// set x and y coordinates to -1
	b.setX(-1);
	b.setY(-1);
	//utilize the helper method to get the piece that was on that specific index of the board (piece selected)
	brownAlmond& b2 = getPieceByCord(x1, y1);
	// empty out display at original location
	board[b2.getIndex()].display = "";
	// set the piece with the new coordinates
	b2.setX(x2);
	b2.setY(y2);
	b2.setIndex(WIDTH, x2, y2);
	// set the display on the board
	board[b2.getIndex()].display = "A";
	// if the board printed successfully
	if (printBoard(board, WIDTH, WIDTH) == Success){
		// check if the game has been completed. This will prevent users from being prompted if the game is already finished
		if (done()){
			return Done;
		}
		// check if there is a stalemate. This will prevent users from being prompted if the game hit a stalemate
		if (stalemate()){
			return StaleMate;
		}
		// display the user's move
		printString += " " + to_string(x1) + "," + to_string(y1) + " to " + to_string(x2) + "," + to_string(y2);
		cout << printString << endl;
		// prompt the user if he/she wants to continue the turn
		cout << "Continue this turn (y/n)?  ";
		string s;
		getline(cin, s);
		// keep prompting until the user answers y for yes or n for no.
		while (s != "y" && s != "n"){
			cout << "Continue this turn (y/n)?  ";
			getline(cin, s);
		}
		// if yes
		if (s == "y"){
			// run the overloaded turn function with the ending coordinates as the beginnign coordinates for the next move in the turn.
			int t = turn(x2, y2);
			// re run turn until it returns the proper value
			while (t != Success && t != Quit && t != Stuck && t != Done && t != StaleMate){
				t = turn(x2, y2);
			}
			// return the return value accordingly
			return t;
		}
		else {
		// if the user decides to end the turn dispose of his moves so far so that the move display will start over in the following turn. 
			printString = "";
		// return success if the user indicated n to end the turn.
			return Success;
		}
	}
}

// Turn method 
// Instead of using the two coordinates extracted from user input, it uses the two variables that were passed from the turn() function to use the ending space from the previous move as the piece to be moved for the following move.
int NineAlmonds::turn(int x = 0, int y = 0) 
{

	if (x != 0 or y != 0){
		vector<brownAlmond> checkList;
		checkMove(checkList, x, y);
		// if there aren't any valid moves available then return Stuck to turn() which will then return Stuck to play() to tell the user that he/she is stuck and cannot continue the turn.
		if (checkList.size() < 1){
			printString = "";
			checkList.clear();
			return Stuck;
		}
	}
	// 4 unsigned integers to be used for extraction
	unsigned int x1 = x;
	unsigned int y1 = y;
	unsigned int x2 = 0;
	unsigned int y2 = 0;
	// prompts the user
	int check = prompt(x1, y1);
	// if the prompt returned neither Success nor Quit, then reprompt the user
	while (check != Success && check != Quit){
		check = prompt(x1, y1);
	}
	// if the user indicated to quit, catch the action and return Quit.
	if (check == Quit){
		return Quit;
	}
	// initialized a vector of brownAlmonds to pass in to the helper method to check for move availability
	vector<brownAlmond> checkList;
	checkMove(checkList, x1, y1);
	// checkList being empty indicates that none of the other pieces provide a valid move. Thus the function will return WrongChoice indicating that the user should pick a different piece.
	if (checkList.size() < 1){
		checkList.clear();
		return WrongChoice;
	}
	// if there is a valid move. Prompt the user with the overloaded prompt function to retrieve the destination for the piece picked.
	int check2 = prompt(x2, y2, 1);
	// if the prompt function did not return success or quit, keep prompting the user.
	while (check2 != Success && check2 != Quit){
		check2 = prompt(x2, y2, 1);
	}
	// if the user indicated to quit, then return Quit which will be caught in the play() method.
	if (check2 == Quit){
		return Quit;
	}

	// the following multiple lines of code checks the validity of the inputted move.
	// checks if there is a piece on the board with the coordinates inputted.
	// the code simply executes a certain behavior for different possibilities with minimal tweaks. Thus, I thought it was unnecessary to overwhelm with detailed comments for every single case except the first case. 
	if (board[WIDTH * (y1 + 1) + (x1 + 1)].display == "A"){
		// checks if the destination is empty
		if (board[WIDTH * (y2 + 1) + (x2 + 1)].display.empty()){
			// if the move was either up or down.
			if (x1 == x2 && (y1 == y2 + 2 || y1 == y2 - 2)){
				// if the move was down
				if (y1 - 2 == y2){
					// checks if there exists a piece below the piece selected to be overtaken.
					if (board[WIDTH * (y1) + (x1 + 1)].display == "A"){
						//utilize the helper method to get the piece that was on that specific index of the board (overtaken)
						return turnHelper(board, x1, y1 - 1, x2, y2);
					}
					// if there isn't a piece to be over taken then it is not a valid move.
					else {
						return TurnError;
					}
				}
				// identical reasoning as the case above but for when the user indicated a move upwards.
				else if (y1 + 2 == y2){
					// checks if a piece exits a square above to be overtaken. 
					if (board[WIDTH * (y1 + 2) + (x1 + 1)].display == "A"){
						return turnHelper(board, x1, y1 + 1, x2, y2);
						// gets piece by cord
					}
					else {
						return TurnError;
					}
				}
			}
			// else if the user's inputted moves indicated a move either to the left or to the right
			else if((y1 == y2) && (x1 == x2 - 2 || x1 == x2 + 2)){
				// if the user tried to move to the left. Identical reasoning applies as the first case with lengthy comments to show the steps.
				if (x1 - 2 == x2){
					// check if there is a piece to be overtaken to the left of the selected piece.
					if (board[WIDTH * (y1 + 1) + (x1)].display == "A"){
						return turnHelper(board, x1 - 1, y1, x2, y2);
					}
					else {
						return TurnError;
					}
				}
				// if the user decided to move to the right.
				else if (x1 == x2 - 2){
					// once again identical explanations apply to the steps here as the first case.
					// if there is a piece to be overtaken to the right
					if (board[WIDTH * (y1 + 1)+(x1 + 2)].display == "A"){
						return turnHelper(board, x1 + 1, y1, x2, y2);
					}
					else {
						return TurnError;
					}
				}
			}
			//else if the inputted move indicates a move diagonally to the right (southeast or northeast)
			else if (x2 == x1 + 2 && (y2 == y1 + 2 || y2 == y1 - 2)){
				// if the move indicates northeast
				if (y2 == y1 + 2){
					// once again identical explanations apply to the steps here as the first case.
					// if there is a piece to be overtaken at northeast
					if (board[WIDTH * (y1 + 2) + (x1 + 2)].display == "A"){
						return turnHelper(board, x1 + 1, y1 + 1, x2, y2);
					}
					else {
						return TurnError;
					}
				}
				// if the user indicated to move southeast
				else if (y2 == y1 - 2){
					// once again identical explanations apply to the steps here as the first case.
					// check if there is a piece to be overtaken to the southeast
					if (board[WIDTH * (y1) + (x1 + 2)].display == "A"){
						return turnHelper(board, x1 + 1, y1 - 1, x2, y2);
					}
					else {
						return TurnError;
					}
				}
			}
			// else if the user indicated to move either northwest or southwest
			else if (x2 == x1 - 2 && (y2 == y1 + 2 || y2 == y1 - 2)){
				// if the user indicated to move north west
				if (y2 == y1 + 2){
					// once again identical explanations apply to the steps here as the first case.
					// if there is a piece to be overtaken to the northwest
					if (board[WIDTH * (y1 + 2) + (x1)].display == "A"){
						return turnHelper(board, x1 - 1, y1 + 1, x2, y2);
					}
					else {
						return TurnError;
					}
				}
				// if the move indicated to move southwest
				else if (y2 == y1 - 2){
					// once again identical explanations apply to the steps here as the first case.
					// if there is a piece to be overtaken to the southwest.
					if (board[WIDTH * (y1) + (x1)].display == "A"){
						return turnHelper(board, x1 - 1, y1 - 1, x2, y2);
					}
					else {
						return TurnError;
					}
				}
				else {
					return PrintError;
				}
			}
			// if the move indicated fits into none of the cases specified then it is not a valid move.
			else {
				cout << "********* Invalid Input! (Invalid Move) ********* " << endl;
				return TurnError;
			}
		}
		// if the destination coordinates does not indicate an empty space
		else {
			cout << "********* Invalid Second Input! (Destination Occupied) ********* " << endl;
			return TurnError;
		}
	}
	// if there isn't a piece at the first coordinate specified.
	else {
		cout << "********* Invalid First Input! (None Existent Piece) ********* " << endl;
		return TurnError;
	}
	return TurnError;
}

int NineAlmonds::play()
{
	//NineAlmonds* na = this;
	unsigned int x = 0;
	unsigned int y = 0;
	// Pieces.txt contains the information to all the pieces in the game board as well as the game board's dimensions. Use is further specified in readme.txt

	// Handling Save Data
	ifstream saveStream("NineAlmonds.txt");
	ifstream ifs("Pieces.txt");
	// if file exists
	if (saveStream.is_open()){
		// ask to continue or start new game
		cout << "Save File Exists. Would You Like To Continue? (y/n) : ";
		string uRes;
		getline(cin, uRes);
		while (uRes != "y" && uRes != "n"){
			cout << "Save File Exists. Would You Like To Continue? (y/n) : ";
			getline(cin, uRes);
		}
		// if continue
		if (uRes == "y"){
			cout << endl << "Loading Save Data ..." << endl;
			string resultString;
			getline(saveStream, resultString);
			istringstream extractor(resultString);
			string firstWord;
			extractor >> firstWord;
			// if NO DATA or blank file
			if (firstWord == "NO" || firstWord == ""){
				cout << endl << "Empty Save File. Starting New Game." << endl;
				// new game format
				//ifstream ifs("Pieces.txt");
				int checkMe = boardDimension(ifs, x, y);
				if (checkMe == GetLineError){
					cout << "Make Sure Pieces.txt Is in the directory" << endl;
				}
				setBoard();
				boardPieces(ifs, board);
				turnCount = 0;
			}
			else{
				string dummy;
				int turnVal;
				pieceCount = 0;
				// retrieve the amount of turns used in the saved data
				if (extractor >> dummy && extractor >> turnVal){
					turnCount = turnVal;
				}
				else {
					// if unable to get this info return an error
					cout << "Data Error" << endl;
					return DataErr;
				}
				int pCount = 1;
				// initialize game
				// 5 x 5 board with grid view. Thus 6 x 6
				setWidth(6);
				setHeight(6);
				setBoard();
				boardInit();
				while (saveStream.good()){
					string resultString;
					getline(saveStream, resultString);
					int xCrd;
					int yCrd;
					istringstream extrct(resultString);
					// get the coordinate of each piece and display it on the board while setting up the game accordingly to the save data.
					if (extrct >> xCrd && extrct >> yCrd){

						// THIS WAS MISSING ----------------------------------------------------------------------------------------------------
						if (xCrd > 4 || yCrd > 4 || xCrd < 0 || yCrd < 0){
							extrct.clear();
							continue;
						}
						//----------------------------------------------------------------------------------------------------------------------

						else {
							brownAlmond &piece = getPiece(pCount);
							pCount++;
							piece.display = "A";
							// the following three lines of code sets the piece's x and y coordinate and the piece's index value on the board.
							piece.setX(xCrd);
							piece.setY(yCrd);
							piece.setIndex(width, xCrd, yCrd);
							int index = piece.getIndex();
							// stores the piece on the board.
							board[index] = piece;
							pieceCount++;
						}
					}
				}
			}
		}
		else {
			// if response is No (n) start a new game
			int checkMe = boardDimension(ifs, x, y);
			if (checkMe == GetLineError){
				cout << "Make Sure Pieces.txt Is in the directory" << endl;
				return Stuck;
			}
			setBoard();
			boardPieces(ifs, board);
			turnCount = 0;
		}
	}
	// else start a new game
	else {
		//ifstream ifs("Pieces.txt");
		int checkMe = boardDimension(ifs, x, y);
		if (checkMe == GetLineError){
			cout << "Make Sure Pieces.txt Is in the directory" << endl;
			return Stuck;
		}
		setBoard();
		boardPieces(ifs, board);
		turnCount = 0;
		pieceCount = 9;
	}
	if (pieceCount == 0){
		cout << "No Valid Piece Exists. Starting New Game." << endl;
		int checkMe = boardDimension(ifs, x, y);
		if (checkMe == GetLineError){
			cout << "Make Sure Pieces.txt Is in the directory" << endl;
			return Stuck;
		}
		setBoard();
		boardPieces(ifs, board);
		turnCount = 0;
	}
	ifs.close();
	saveStream.close();
	setLongest();
	if (stalemate()){
		cout << "********* Stalemate! Try Again. *********" << endl
			<< "You Took " << turnCount << " Turn(s)" << endl;
		cout << endl << "Stalemate Data Saved. Please Start New Game!" << endl;
		return StaleMate;
	}
	if (done()){
		cout << "********* Game Completed. Congratualations! *********" << endl
			<< "You Took " << turnCount << " Turn(s) to Complete!" << endl;
		cout << endl << "Complete Data Saved. Please Start New Game!" << endl;
		return Success;
	}
	print();
	// turnCount is a class variable used solely for the purpose of keeping track of a user's number of turns.
	// infinite loop unless an acceptable value is returned 
	while (true){
		// calls turn
		int Turn = turn();
		// increment the turn count indicating that a turn has started.
		turnCount++;
		// while turn() returns none of these return values, turn() is invoked again to have the user complete a successful turn, to get stuck, or decides to quit.
		// these values also acts as a "catch" for values such as Done, StaleMate, Stuck, or Quit to act accordingly when such values were returned.
		while (Turn != Success && Turn != Quit && Turn != Stuck && Turn != Done && Turn != StaleMate && Turn != WrongChoice){
			Turn = turn();
			//increment the turncount after invoking turn() each time.
			turnCount++;
		}
		if (Turn == Quit){
			// if the user decides to quit the turn is void. Therefore, decrement the turnCount by 1.
			turnCount--;
			cout << "You Took " << turnCount << " Turn(s)" << endl;
			return Quit;
		}
		if (stalemate()){
			cout << "********* Stalemate! Try Again. *********" << endl
				<< "You Took " << turnCount << " Turn(s)" << endl;
			return StaleMate;
		}
		if (done()){
			cout << "********* Game Completed. Congratualations! *********" << endl
				<< "You Took " << turnCount << " Turn(s) to Complete!" << endl;
			return Success;
		}
		//if the user had made a wrong choice turnCount is decremented without giving a turn penalty.
		if (Turn == WrongChoice) {
			turnCount--;
			cout << "No Valid Moves For Selected Piece! Pick a Different Piece" << endl;
		}
		// if the user gets stuck however, the user is given a penalty of their turn ending without the turn count being decremented.
		if (Turn == Stuck){
			cout << "No More Valid Moves For This Piece! Pick a Different Piece" << endl;
		}
		cout << "Turns Currently Used: " << turnCount << endl;

	}
}