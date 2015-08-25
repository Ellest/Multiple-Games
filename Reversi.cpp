#include "stdafx.h"
#include "Reversi.h"
#define ONE 1
#define TWO 2

ostream &operator<< (ostream &os, const Reversi &re)
{
	os << endl << endl;
	// printing out who's turn it is on top of the game board
	if (re.whoseTurn == ONE){
		os << re.player1 << "'s Turn (O)" << endl;
	}
	else {
		os << re.player2 << "'s Turn (X)" << endl;
	}
	os << endl;
	unsigned int height = re.height;
	unsigned int width = re.width;
	//int length = ma.longest;
	vector<brownAlmond> board = re.board;
	//os << "longest: " << ma.longest << endl;
	for (int y = height - 1; y >= 0; y--){

		for (unsigned int x = 0; x < width; x++){
			int ind = (width * y) + (x);
			// checks if the color is either invalid or none. If it is so, the piece will be displayed as "Piece Color Error." This adds additional functionality as it tells the user what was wrong with the piece
			if (board[ind].display == "A"){
				os << setw(re.longest + 1) << board[ind].display << setw(re.longest + 1);
			}
			// If nothing was wrong with the piece print piece as it is.
			else if (!board[ind].display.empty() && board[ind].display != "A"){
				os << setw(re.longest + 1) << board[ind].display << setw(re.longest + 1);
			}
			else {
				os << setw(re.longest + 1) << board[ind].display << setw(re.longest + 1);
			}
			//At the last (righter-most) x coordinate 
			if (x == width - 1){
				os << endl << endl;
			}
		}

	}
	return os;
}

void Reversi::print()
{
	cout << *this;
}

// helper method for flipping a piece at a given index
void Reversi::flip(int ind)
{
	if (board[ind].display == "O"){
		board[ind].display = "X";
	}
	else {
		board[ind].display = "O";
	}
}

bool Reversi::done()
{
	// if there are any available moves for either players return false. This also takes care of the case where all the spaces are filled.
	if (availCheck("O") || availCheck("X")){
		return false;
	}
	// this part of code will only run if there are no more available moves left
	// counters for O and X pieces to tally the pieces up
	int oCount = 0;
	int xCount = 0;
	// for each cell in board check which piece is on the board.
	for (unsigned int i = 0; i < board.size(); i++){
		if (board[i].display == "O"){
			oCount++;
		}
		else if (board[i].display == "X"){
			xCount++;
		}
	}
	// more O pieces than X. Player 1 Wins
	if (oCount > xCount){
		print();
		cout << player1 << " Wins!" << " ( " << oCount << " vs " << xCount << " ) " << endl;
		return true;
	}
	// Vice Versa
	else if (oCount < xCount){
		print();
		cout << player2 << " Wins!" << " ( " << xCount << " vs " << oCount << " ) " << endl;
		return true;
	}
	// there's a tie here
	else {
		return false;
	}
}

// stalemate method
bool Reversi::stalemate(){
	// helper methods for checking availability. If there are any available moves for either player one or two return false.
	if (availCheck("O") || availCheck("X")){
		return false;
	}
	// if the game is done return false
	if (done()){
		return false;
	}
	// else we have a tie thus return true. Intuition is that the game could only be in three different states: Playing, Done, or Tie. Since its neither of the first two, there must be a tie.
	else {
		print();
		return true;
	}
}

// checking validity of the left down diagonal (/). If there is a valid move, flip the pieces accordingly.
bool Reversi::checkDownLeftD(int x, int y, string wTurn, bool check)
{
	bool returnVal = false;
	// if x is less than 2 or y is less than 2 there is no need to check as this particular move will not be valid
	if (x < 2 || y < 2){
		return returnVal;
	}
	// start by checking the immediate piece
	int xCheck = x - 1;
	int yCheck = y - 1;
	// final coordinates (the coordinates to stop flipping pieces)
	int xFin;
	int yFin;
	while (xCheck >= 0 && yCheck >= 0){
		int ind = width * (yCheck + 1) + xCheck + 1;
		// for the immediately following piece
		if (xCheck == x - 1 && yCheck == y - 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the bottom left diagonal direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				xCheck--;
				yCheck--;
				continue;
			}
		}
		// further check
		else {
			// if the piece is of the player who's turn it is, then we stop checking further. Intuitively correct as this will be the ending point of our flip
			if (board[ind].display == wTurn){
				xFin = xCheck;
				yFin = yCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				xCheck--;
				yCheck--;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else {
		// if this was a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			// place a piece at the desired spot since it is a valid move.
			board[cInd].display = wTurn;
			int xChange = xFin + 1;
			int yChange = yFin + 1;
			// while xchange is less than the placed piece flip the pieces that are in the diagonal
			while (xChange < x && yChange < y){
				int idx = width * (yChange + 1) + xChange + 1;
				flip(idx);
				xChange++;
				yChange++;
			}
		}
		return returnVal;
	}
}

// method to check right diagonal (/) going up. If valid move do the flip.
bool Reversi::checkUpRightD(int x, int y, string wTurn, bool check)
{
	bool returnVal = false;
	// if x greater than 5 or y is greater than 5 there is no need to check as this particular move will not be valid
	if (x > 5 || y > 5){
		return returnVal;
	}
	int xCheck = x + 1;
	int yCheck = y + 1;
	int xFin;
	int yFin;
	while (xCheck <= 7 && yCheck <= 7){
		int ind = width * (yCheck + 1) + xCheck + 1;
		if (xCheck == x + 1 && yCheck == y + 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the upward right diagonal direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				xCheck++;
				yCheck++;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				xFin = xCheck;
				yFin = yCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				xCheck++;
				yCheck++;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else{
		// if this is a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int xChange = x + 1;
			int yChange = y + 1;
			while (xChange < xFin && yChange < yFin){
				int idx = width * (yChange + 1) + xChange + 1;
				flip(idx);
				xChange++;
				yChange++;
			}
		}
		return returnVal;
	}
}

// helper method for checking right move. Flip pieces accordingly
bool Reversi::checkRight(int x, int y, string wTurn, bool check)
{
	bool returnVal = false;
	// if x is greater than there is no need to check as this particular move will not be valid
	if (x > 5){
		return returnVal;
	}
	int xCheck = x + 1;
	int xFin;
	while (xCheck <= 7){
		int ind = width * (y + 1) + xCheck + 1;
		if (xCheck == x + 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the right direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				xCheck++;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				xFin = xCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				xCheck++;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else {
		// if this was a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int xChange = x + 1;
			while (xChange < xFin){
				int idx = width * (y + 1) + xChange + 1;
				flip(idx);
				xChange++;
			}
		}
		return returnVal;
	}

}

// method for checking left move. Flip pieces accordingly
bool Reversi::checkLeft(int x, int y, string wTurn, bool check){
	bool returnVal = false;
	// if x is less than 2 there is no need to check as this particular move will not be valid. The move can't overtake any moves to the left
	if (x < 2){
		return returnVal;
	}
	int xCheck = x - 1;
	int xFin;
	while (xCheck >= 0){
		int ind = width * (y + 1) + xCheck + 1;
		if (xCheck == x - 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the left direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				xCheck--;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				xFin = xCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				xCheck--;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else {
		// if this was a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int xChange = x - 1;
			while (xChange > xFin){
				int idx = width * (y + 1) + xChange + 1;
				flip(idx);
				xChange--;
			}
		}
		return returnVal;
	}
}

// checking down. if valid move flip pieces
bool Reversi::checkDown(int x, int y, string wTurn, bool check)
{
	bool returnVal = false;
	// if y is less than 2 there is no need to check as this particular move will not be valid
	if (y < 2){
		return returnVal;
	}
	int yCheck = y - 1;
	int yFin;
	while (yCheck >= 0){
		int ind = width * (yCheck + 1) + x + 1;
		if (yCheck == y - 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the bottom direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				yCheck--;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				yFin = yCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				yCheck--;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else {
		// if this was a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int yChange = y - 1;
			while (yChange > yFin){
				int idx = width * (yChange + 1) + x + 1;
				flip(idx);
				yChange--;
			}
		}
		return returnVal;
	}
}

// helper method for checking up move. flip pieces accordingly
bool Reversi::checkUp(int x, int y, string wTurn, bool check)
{
	bool returnVal = false;
	// if y is greater than 5 there is no need to check as this particular move will not be valid
	if (y > 5){
		return returnVal;
	}
	int yCheck = y + 1;
	int yFin;
	while (yCheck <= 7){
		int ind = width * (yCheck + 1) + x + 1;
		if (yCheck == y + 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the upward direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				yCheck++;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				yFin = yCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				yCheck++;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else{
		// if this was a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int yChange = y + 1;
			while (yChange < yFin){
				int idx = width * (yChange + 1) + x + 1;
				flip(idx);
				yChange++;
			}
		}
		return returnVal;
	}
}

// helper method for checking upward left diagonal move. flip pieces accordingly
bool Reversi::checkUpLeftD(int x, int y, string wTurn, bool check){
	bool returnVal = false;
	// if x is less than 2 or y is greater than 5 there is no need to check as this particular move will not be valid
	if (x < 2 || y > 5){
		return returnVal;
	}
	int xCheck = x - 1;
	int yCheck = y + 1;
	int xFin;
	int yFin;
	while (xCheck >= 0 && yCheck <= 7){
		int ind = width * (yCheck + 1) + xCheck + 1;
		if (xCheck == x - 1 && yCheck == y + 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the upward left diagonal direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				xCheck--;
				yCheck++;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				xFin = xCheck;
				yFin = yCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				xCheck--;
				yCheck++;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else{
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int xChange = x - 1;
			int yChange = y + 1;
			while (xChange > xFin && yChange < yFin){
				int idx = width * (yChange + 1) + xChange + 1;
				flip(idx);
				xChange--;
				yChange++;
			}
		}
		return returnVal;
	}
}

// helper method to check the down right diagonal move. flip pieces accordingly
bool Reversi::checkDownRightD(int x, int y, string wTurn, bool check){
	bool returnVal = false;
	// if x is greater than 5 or y is less than 2 there is no need to check as this particular move will not be valid
	if (x > 5 || y < 2){
		return returnVal;
	}
	int xCheck = x + 1;
	int yCheck = y - 1;
	int xFin;
	int yFin;
	while (xCheck <= 7 && yCheck >= 0){
		int ind = width * (yCheck + 1) + xCheck + 1;
		if (xCheck == x + 1 && yCheck == y - 1){
			if (board[ind].display == wTurn){
				// in order for the move to be a valid move in the bottom right diagonal direction the next piece must be the opponent's piece
				returnVal = false;
				break;
			}
			else if (board[ind].display == ""){
				// if blank there's no need to check further
				returnVal = false;
				break;
			}
			else{
				//indicates a need to check further
				xCheck++;
				yCheck--;
				continue;
			}
		}
		// further check
		else {
			if (board[ind].display == wTurn){
				xFin = xCheck;
				yFin = yCheck;
				returnVal = true;
				break;
			}
			else if (board[ind].display == ""){
				// hitting a blank spot will indicate that this particular move is not valid. 
				returnVal = false;
				break;
			}
			else {
				// keep going if the piece is the opponent's piece
				xCheck++;
				yCheck--;
			}
		}
	}
	// if the function is being run just to check, terminate here and return whether this move is valid or not
	if (check){
		return returnVal;
	}
	else{
		// if it was a valid move
		if (returnVal){
			int cInd = width * (y + 1) + x + 1;
			board[cInd].display = wTurn;
			int xChange = x + 1;
			int yChange = y - 1;
			while (xChange < xFin && yChange > yFin){
				int idx = width * (yChange + 1) + xChange + 1;
				flip(idx);
				xChange++;
				yChange--;
			}
		}
		return returnVal;
	}
}

bool Reversi::valid(int x, int y, string wTurn){
	// first check if the move is contiguous. If all the spaces touching the desired space are blanks, the move cannot be valid. 
	vector<bool> truthV;
	int index = width * (y + 1) + x + 1;
	int check;
	// counter to check if the move being placed is adjacent to a piece. If it isn't then the move is invalid
	int blnkCount = 0;
	// minimum
	int k = Below;
	// the max offset the y coordinate will be offset by at each layer
	int kMax = Up;
	// the max offset the x coordinate will be offset by at each layer
	int jMax = Right;
	// if the top row
	if (y == 7){
		// don't check above. 0 indicates its own row
		kMax = Current;
	}
	if (y == 0){
		// don't check below
		k = Current;
	}
	bool returnVal = false;
	while (k <= kMax){
		int j = -1;
		if (x == 7) {
			// if right end then don't check right
			jMax = Current;
		}
		if (x == 0) {
			// if left end then don't check left
			j = Current;
		}
		while (j <= jMax){
			check = index + (k * width) + j;
			if (check == index){
				j++;
				continue;
			}
			if (board[check].display == ""){
				blnkCount++;
			}
			j++;
		}
		k++;
	}
	// if the placed move is surrounded by empty cells return that the move is not valid
	if (blnkCount == 8){
		return false;
	}

	// check all move posibilities

	// bottom left diagonal
	bool bld = checkDownLeftD(x, y, wTurn, false);
	truthV.push_back(bld);

	// down
	bool dwn = checkDown(x, y, wTurn, false);
	truthV.push_back(dwn);

	// bottom right diagonal
	bool brd = checkDownRightD(x, y, wTurn, false);
	truthV.push_back(brd);

	// up left diagonal
	bool uld = checkUpLeftD(x, y, wTurn, false);
	truthV.push_back(uld);

	// up 
	bool up = checkUp(x, y, wTurn, false);
	truthV.push_back(up);

	// up right diagonal
	bool urd = checkUpRightD(x, y, wTurn, false);
	truthV.push_back(urd);

	// left
	bool lft = checkLeft(x, y, wTurn, false);
	truthV.push_back(lft);

	// right
	bool rgt = checkRight(x, y, wTurn, false);
	truthV.push_back(rgt);

	// determine if there was at least one valid move
	for (unsigned int i = 0; i < truthV.size(); i++){
		if (truthV[i] == true){
			truthV.clear();
			return true;
		}
	}
	// this means none of the moves were valid
	truthV.clear();
	return false;
}

// initializing the pieces for a new game
void Reversi::pieceInit()
{
	int xV = 3;
	int yV = 3;
	int iV = width * (yV + 1) + xV + 1;
	// 3,3
	board[iV].display = "X";
	yV++;
	iV = width * (yV + 1) + xV + 1;
	// 3,4
	board[iV].display = "O";
	xV++;
	iV = width * (yV + 1) + xV + 1;
	// 4,4
	board[iV].display = "X";
	yV--;
	// 4,3
	iV = width * (yV + 1) + xV + 1;
	board[iV].display = "O";

	
}

//helper method to switch turns. Manipulates the turn indicator var
void Reversi::swapTurn()
{
	if (whoseTurn == ONE){
		whoseTurn = TWO;
	}
	else {
		whoseTurn = ONE;
	}
}

// helper method for checking the availability of a specified player at a given coordinate.
bool Reversi::avail(int x, int y, string wTurn)
{
	//check the validity of each move
	bool cdl = checkDownLeftD(x, y, wTurn, true);
	bool cd = checkDown(x, y, wTurn, true);
	bool cdr = checkDownRightD(x, y, wTurn, true);
	bool cul = checkUpLeftD(x, y, wTurn, true);
	bool cu = checkUp(x, y, wTurn, true);
	bool cur = checkUpRightD(x, y, wTurn, true);
	bool cl = checkLeft(x, y, wTurn, true);
	bool cr = checkRight(x, y, wTurn, true);
	// any of the moves are valid, return true, else false.
	if (cdl || cd || cdr || cul || cu || cur || cl || cr){
		return true;
	}
	else {
		return false;
	}
}

// checks the move availability for each game board cell (only the play field and not the grid cells). 
bool Reversi::availCheck()
{
	// double for loop from 0 to 7 since the coordinates run from 0 to 7 both in x and y
	for (int j = 0; j < 8; j++){
		for (int i = 0; i < 8; i++){
			int ind = width * (j + 1) + i + 1;
			// if the spot is blank check for availability
			if (board[ind].display == ""){
				// how to handle which user has the current turn.
				if (whoseTurn == ONE){
					if (avail(i, j, "O")){
						return true;
					}
				}
				else {
					if (avail(i, j, "X")){
						return true;
					}
				}
			}
		}
	}
	return false;
}

// overloaded availCheck method. Adds functionality of being able to specify who's turn it is.
bool Reversi::availCheck(string s)
{
	for (int j = 0; j < 8; j++){
		for (int i = 0; i < 8; i++){
			int ind = width * (j + 1) + i + 1;
			if (board[ind].display == ""){
				if (avail(i, j, s)){
					return true;
				}
			}
		}
	}
	return false;
}

// turn method
int Reversi::turn()
{
	// checks if there is an available move for the current player. If not, indicate that it is so
	if (!availCheck()){
		return NoAvailableMoves;
	}
	unsigned int x;
	unsigned int y;
	int check = prompt(x, y);
	int index = width * (y + 1) + (x + 1);
	while (check != Success && check != Quit){
		check = prompt(x, y);
		index = width * (y + 1) + (x + 1);
	}
	if (check == Quit){
		return Quit;
	}
	else if (board[index].display != ""){
		cout << "Space Occupied!" << endl;
		return TurnError;
	}
	else {
		bool val;
		// check validity
		if (whoseTurn == ONE){
			string tStr = "O";
			val = valid(x, y, tStr);
		}
		else {
			string tStr = "X";
			val = valid(x, y, tStr);
		}
		// act accordingly
		if (val){
			return Done;
		}
		else {
			cout << "Invalid Move" << endl;
			return TurnError;
		}
	}
}

// save function
void Reversi::save(string s)
{
	ofstream saveFile;
	// this is the format I've chosen to save the data. Further explanation can be found in readMe.txt
	string fileName = "Riversi " + player1 + " " + player2 + ".txt";
	saveFile.open(fileName);
	string y = "yes";
	// if yes
	if (s.compare(y) == 0){
		int iVal;
		// write SAVE DATA along with whose turn it is separated by a space
		saveFile << "SAVE DATA " << whoseTurn << endl;
		for (unsigned int j = 1; j < height; j++){
			for (unsigned int i = 1; i < width; i++){
				iVal = width * j + i;
				saveFile << i - 1 << " " << j - 1 << " " << board[iVal].display << endl;
			}
		}
		saveFile.close();
	}
	// if no save
	else {
		saveFile << "NO DATA" << endl;
		saveFile.close();
	}
}

int Reversi::prompt(unsigned int &a, unsigned int &b)
{
	// asks the user to pick a piece
	cout << "Type the Coordinate \"X,Y\" to Place Your Piece | Type \"quit\" to Stop Playing : ";
	string s;
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
			if (x < 0 || x > width - 2 || y < 0 || y > height - 2){
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

int Reversi::play(){
	// set the width and height to be 9 since the play board is 8 x 8 and with the grid cells the entire game board is 9 x 9
	setWidth(9);
	setHeight(9);
	// resizes the board and initialzes the grid
	setBoard();
	boardInit();
	// initializing the turn to player one
	whoseTurn = ONE;
	longest = 2;
	// Handle Sava Data
	string saveFileName = "Riversi " + player1 + " " + player2 + ".txt";
	ifstream ifs(saveFileName);
	// see if the file exits
	if (ifs.is_open()){
		// prompt if the user wants to continue with the save data or start a new game
		cout << "Save File Exists. Would You Like To Continue? (y/n) : ";
		string uRes;
		getline(cin, uRes);
		// if not yes (y) or no (n) keep prompting
		while (uRes != "y" && uRes != "n"){
			cout << "Save File Exists. Would You Like To Continue? (y/n) : ";
			getline(cin, uRes);
		}
		// if yes
		if (uRes == "y"){
			cout << endl << "Loading Save Data ..." << endl;
			string resultString;
			getline(ifs, resultString);
			// wrapping first line in a istringstream for extraction and manipulation
			istringstream extractor(resultString);
			string firstWord;
			string dummy;
			int turnVar;
			extractor >> firstWord;
			// if the first word is NO or is blank (indicating no data since either SAVE DATA or NO DATA must be on the first line
			if (firstWord == "NO" || firstWord == ""){
				// notify the state
				cout << endl << "Empty Save File. Starting New Game.";
				// initializing starting pieces
				pieceInit();
			}
			else {
				// dummy string for "DATA" and turnVar for the indicator on whose turn it is
				if (extractor >> dummy && extractor >> turnVar){
					whoseTurn = turnVar;
					// while not end of file
					while (ifs.good()){
						getline(ifs, resultString);
						int xCrd;
						int yCrd;
						string pieceDis;
						istringstream extrctor(resultString);
						// populating the cells that have save data.
						if (extrctor >> xCrd && extrctor >> yCrd && extrctor >> pieceDis){
							// since the grid is 8 x 8 the lowest must be 0 and max must be 7 for either coordinates
							if (xCrd > 7 || yCrd > 7 || xCrd < 0 || yCrd < 0){
								extrctor.clear();
								continue;
							}
							if (pieceDis != "O" && pieceDis != "X"){
								extrctor.clear();
								continue;
							}
							int iVal = width * (yCrd + 1) + (xCrd + 1);
							board[iVal].display = pieceDis;
						}
					}
				}
				// returns Data Error. The First line must contain the turn variable
				else {
					cout << "Data Error" << endl;
					return DataErr;
				}
			}
		}
		// if chooses not to continue old game
		else {
			cout << endl << "Starting New Game";
			pieceInit();
		}
	}
	// if there is no save data file for the two specified users
	else {
		cout << endl << "No Save Data. Starting New Game";
		pieceInit();
	}
	ifs.close();
	cout << endl;

	// handling erroneous data. If a completed or stalemated save file is given return the according values
	if (done()){
		cout << "Data Indicates Completed Game. Please Start a New Game!" << endl;
		return Success;
	}
	if (stalemate()){
		cout << "Data Indicates Completed Game. Please Start a New Game!" << endl;
		return StaleMate;
	}

	while (true){
		print();
		int play = turn();
		// until the three terminating conditions of a turn is met 
		while (play != Done && play != Quit && play != NoAvailableMoves){
			play = turn();
		}
		// if user decides to quit
		if (play == Quit){
			return Quit;
		}
		// check if done
		if (done()){
			return Success;
		}
		// check stalemate
		if (stalemate()){
			cout << "********* Stalemate! We Have a Tie! *********" << endl;
			return StaleMate;
		}
		// indicates that there are no moves for the current player
		if (play == NoAvailableMoves){
			if (whoseTurn == ONE){
				cout << endl << "*********No Available Moves for " << player1 << " *********" << endl;
			}
			else {
				cout << endl << "*********No Available Moves for " << player2 << " *********" << endl;
			}
		}
		// swap turns
		swapTurn();
	}
}
