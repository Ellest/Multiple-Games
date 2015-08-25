#include "stdafx.h"
#include "MagicSquare.h"
#define quitVal -987

ostream &operator<< (ostream &os, const MagicSquare &ma)
{
	os << endl;
	unsigned int height = ma.height;
	unsigned int width = ma.width;
	//int length = ma.longest;
	vector<brownAlmond> board = ma.board;
	//os << "longest: " << ma.longest << endl;
	for (int y = height - 1; y >= 0; y--){

		for (unsigned int x = 0; x < width; x++){
			int ind = (width * y) + (x);
			// checks if the color is either invalid or none. If it is so, the piece will be displayed as "Piece Color Error." This adds additional functionality as it tells the user what was wrong with the piece
			if (board[ind].display == "A"){
				os << setw(ma.longest + 1) << board[ind].display << setw(ma.longest + 1);
			}
			// If nothing was wrong with the piece print piece as it is.
			else if (!board[ind].display.empty() && board[ind].display != "A"){
				os << setw(ma.longest + 1) << board[ind].display << setw(ma.longest + 1);
			}
			else {
				os << setw(ma.longest + 1) << board[ind].display << setw(ma.longest + 1);
			}
			//At the last (righter-most) x coordinate 
			if (x == width - 1){
				os << endl << endl;
			}
		}

	}
	// this portion prints out the available pieces
	os << setw(ma.longest) << "  Available Pieces: ";
	for (unsigned int i = 0; i < ma.pLeft.size(); i++){
		os << ma.pLeft[i] << setw(ma.longest);
	}
	os << endl << endl;
	return os;
}

int MagicSquare::play()
{
	// setting width and height of the game class
	setWidth(num + 1);
	setHeight(num + 1);
	// set the board vec according to the width and height
	setBoard();
	// max value. Since this is a count 1 is subtracted ( as the max calcualation was arithmetic).
	int calc = (num * num) + mini - 1;
	// initializing the pLeft (pieces  left) array
	for (int i = mini; i <= calc; i++){
		pLeft.push_back(i);
	}
	row.resize(num);
	col.resize(num);
	// initializing diagonal sums.
	diagSum[0] = 0;
	diagSum[1] = 0;
	// helper method to initialize the grid on the board
	boardInit();
	// retrieving the longest length
	string leng = to_string(calc);
	string mLeng = to_string(mini);
	int lengInt = leng.length();
	int mLengInt = mLeng.length();
	int longer;
	// if the max number is greater in length than the min number (since min would be longer due to the negative sign) 
	if (lengInt > mLengInt){
		longer = lengInt;
	}
	else {
		longer = mLengInt;
	}
	// Handle Sava Data
	string saveFileName = "MagicSquare " + to_string(mini) + " " + to_string(width - 1) + ".txt";
	//cout << saveFileName << endl;
	ifstream ifs(saveFileName);
	// if file with specified name exists
	if (ifs.is_open()){
		// give option to continue with save data or start a new game
		cout << "Save File Exists. Would You Like To Continue? (y/n) : ";
		string uRes;
		getline(cin, uRes);
		while (uRes != "y" && uRes != "n"){
			cout << "Save File Exists. Would You Like To Continue? (y/n) : ";
			getline(cin, uRes);		
		}
		// if continue (yes)
		if (uRes == "y"){
			cout << endl << "Loading Save Data ..." << endl;
			string resultString;
			getline(ifs, resultString);
			istringstream extractor(resultString);
			string firstWord;
			if (extractor >> firstWord) {
			}
			else {
				firstWord = "";
			}
			// if NO DATA or Blank file
			if (firstWord == "NO" || firstWord == ""){
				cout << endl << "Empty Save File. Starting New Game." << endl;
			}
			else {
				// while not end of the file
				while (ifs.good()){
					getline(ifs, resultString);
					int xCrd;
					int yCrd;
					int pVal;
					istringstream extractor(resultString);
					// if correct values are retrieved
					if (extractor >> xCrd && extractor >> yCrd && extractor >> pVal){
						
						// This was Missing

						if (xCrd > num-1 || yCrd > num-1 || xCrd < 0 || yCrd < 0){
							extractor.clear();
							continue;
						}

						// This was Missing

						auto it = find(pLeft.begin(), pLeft.end(), pVal);

						if (it == pLeft.end()){
							continue;
						}

						int iVal = width * (yCrd+1) + (xCrd+1);
						board[iVal].value = pVal;
						board[iVal].display = to_string(pVal);
						row[yCrd] += pVal;
						col[xCrd] += pVal;
						// utilizing a helper method to check if the value is in the top left to bottom right ( \ ) diagonal
						if (isDiag(xCrd, yCrd)){
							// update the sum in order to be check when done is called
							diagSum[0] += pVal;
						}
						// this uses the logic that the diagonal that traverses from the bottom left to top right ( / ) have the conditional that x and y must equal each other (i.e. in a 4 x 4 grid (0,0) (1,1) (2,2) (3,3) would be in the bottom left to top right diagonal)
						if (xCrd == yCrd){
							// update the sum in order to be check when done is called
							diagSum[1] += pVal;
						}
						// delete the input value from the array of points that are available
						pLeft.erase(it);
					}
				}
			}
		}
	}
	ifs.close();
	// handling completed or stalemated data. Return correct values if the save data is already complete.
	if (pLeft.size() == 0){
		bool result = stalemate();
		if (result){
			print();
			cout << "********* Stalemate! Try Again. *********" << endl;
			cout << endl << "Stalemate Data Saved. Please Start a New Game!" << endl;
			return StaleMate;

		}
		else {
			print();
			cout << "********* Game Completed. Congratualations! *********" << endl;
			cout << endl << "Completed Data Saved. Please Start a New Game!" << endl;
			return Success;
		}
	}

	while (true){
		// setting longest
		longest = longer + 1;
		print();
		int play = turn();
		while (play != Done && play != Quit){
			play = turn();
		}
		if (play == Quit){
			return Quit;
		}
		// if there are no pieces left check done or stalemate. It doesn't make sense to check for done or stalemate unless all pieces have been placed. 
		if (pLeft.size() == 0){
			bool result = stalemate();
			if (result){
				print();
				cout << "********* Stalemate! Try Again. *********" << endl;
				return StaleMate;
				
			}
			else {
				print();
				cout << "********* Game Completed. Congratualations! *********" << endl;
				return Success;
			}
		}
	}
}

void MagicSquare::print()
{
	cout << *this;
}

bool MagicSquare::done()
{
	// if there are any pieces left. The game can't be done
	if (pLeft.size() > 0){
		//cout << "size error" << endl;
		return false;
	}
	// checks all the row sums
	unsigned int rStart = 1;
	while (rStart <= height - 2){
		cout << "rowSum: " << row[rStart] << endl;
		if (row[rStart - 1] != row[rStart]){
			//cout << "row sum error" << endl;
			return false;
		}
		rStart++;
	}
	// checks all the column sums
	unsigned int cStart = 1;
	while (cStart <= width - 2){
		if (col[cStart - 1] != col[cStart]){
			//cout << "col sum error" << endl;
			return false;
		}
		cStart++;
	}
	// checks the match between the two diagonal sums
	if (diagSum[0] == diagSum[1] && diagSum[0] == row[0]){
		return true;
	}
	else {
		return false;
	}
}

bool MagicSquare::stalemate()
{
	// there are only two possible ending conditions for the magicsquares game: stalemate or done. This signifies that if the game is "done" there must be no stalemate, and vice versa. 
	if (done()){
		return false;
	}
	return true;
}

void MagicSquare::save(string s)
{
	ofstream saveFile;
	string fileName = "MagicSquare " + to_string(mini) + " " + to_string(width-1) + ".txt";
	saveFile.open(fileName);
	string y = "yes";
	if (s.compare(y) == 0){
		int iVal;
		saveFile << "SAVE DATA" << endl;
		for (unsigned int j = 1; j < height; j++){
			for (unsigned int i = 1; i < width; i++){
				iVal = width * j + i;
				saveFile << i-1 << " " << j-1 << " " << board[iVal].display << endl;
			}
		}
		saveFile.close();
	}
	else {
		saveFile << "NO DATA" << endl;
		saveFile.close();
	}
}

int MagicSquare::prompt(unsigned int &a, unsigned int &b)
{
	// asks the user to pick a piece
	cout << "Type the Coordinate \"X,Y\" to place a number | Type \"quit\" to Stop Playing : ";
	string s;
	int o = 0;
	getline(cin, s);
	// if the input was empty
	if (s.empty()){
		cout << "********* Invalid Input! (Empty) ********* Must Type a Command *********" << endl;
		return IncorrectCommand;
	}
	// else if the user indicated to quit
	else if (s == "quit"){
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
		unsigned int x;
		unsigned int y;
		istringstream iss(s);
		// if exactly 2 integers were extracted
		if (iss >> x && iss >> y){
			if (x < 0 || x > width-2 || y < 0 || y > height-2){
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

void MagicSquare::prompt(int &a)
{
	cout << "Pick the Piece to Place | Type \"quit\" to Quit the Game: ";
	string s;
	int o = 0;
	getline(cin, s);
	// if the input was empty
	if (s.empty()){
		cout << "********* Invalid Input! (Empty) ********* Must Type a Command *********" << endl;
		return;
	}
	else if (s == "quit"){
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
			// use of quitVal which would act as the "Quit" flag
			a = quitVal;
			return;
		}
		// if no
		else if (c == "n"){
			cin.clear();
			return;
		}
		// if neither y or n
		else {
			cout << "Must Type y or n!" << endl;
			cin.clear();
			return;
		}
	}
	else {
		int comp;
		istringstream iss(s);
		// if the value is a number (being able to extract the istringstream wrapped string into an int value would indicate that this is true)
		if (iss >> comp){
			// using a vector iterator to find if the inputted value exists
			auto it = find(pLeft.begin(), pLeft.end(), comp);
			// if the inputted value does not exist
			if (it == pLeft.end()){
				cout << "Invalid Piece" << endl;
				return;
			}
			else {
				// delete the input value from the array of points that are available
				pLeft.erase(it);
				a = comp;
				return;
			}
		}
		else {
			cout << "Must Enter a Number!" << endl;
			return;
		}
	}
}

int MagicSquare::turn()
{
	unsigned int x;
	unsigned int y;
	int check = prompt(x , y);
	// equation for retrieving the index used for the previous labs
	int index = width * (y + 1) + (x + 1);
	while (check != Success && check != Quit){
		check = prompt(x, y);
		index = width * (y + 1) + (x + 1);
	}
	if (check == Quit){
		return Quit;
	}
	else if (board[index].value > 0){
		cout << "Space Occupied!" << endl;
		return TurnError;
	}
	else {
		int z;
		prompt(z);
		// this is to catch if the user wants to quit. Quitval is an arbitrary low (negative) number thus would never be called directly. Since turn has a return type of int, it was either this or using flags.
		while (z != quitVal && z < mini){
			// fix this part
			prompt(z);
		}
		// if the quitVal flag was set (if the user inputted "quit")
		if (z == quitVal){
			return Quit;
		}
		else {
			int index = width * (y + 1) + (x + 1);
			int r = y;
			int c = x;
			// update the row and column sums in order to be check when done is called
			row[r] += z;
			col[c] += z;
			// utilizing a helper method to check if the value is in the top left to bottom right ( \ ) diagonal
			if (isDiag(x, y)){
				// update the sum in order to be check when done is called
				diagSum[0] += z;
				cout << "diagSum0: " << diagSum[0] << endl;
			}
			// this uses the logic that the diagonal that traverses from the bottom left to top right ( / ) have the conditional that x and y must equal each other (i.e. in a 4 x 4 grid (0,0) (1,1) (2,2) (3,3) would be in the bottom left to top right diagonal)
			if (x == y){
				// update the sum in order to be check when done is called
				diagSum[1] += z;
				cout << "diagSum1: " << diagSum[1] << endl;
			}
			board[index].value = z;
			board[index].display = to_string(z);
			return Done;
		}
	}
}
// helper method to check if the inputed cell was in the top-left to bottom-right diagonal.
bool MagicSquare::isDiag(int x, int y)
{
	int xStart = 0;
	// offset by 2 since the height includes the grid and the indeces starts from 0
	int yStart = height - 2;
	while (yStart >= 0){
		if (x == xStart && y == yStart){
			return true;
		}
		xStart++;
		yStart--;
	}
	return false;
}