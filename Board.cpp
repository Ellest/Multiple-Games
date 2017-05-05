#include "stdafx.h"
#include "Board.h"
using namespace std;
#define numPiece 9

int boardDimension(ifstream& ifs, unsigned int& i, unsigned int& j){

	string dim;
	//getline extracts the line and stores it into the string variable dim
	if (getline(ifs, dim)){
		istringstream iss(dim);
		//if exactly two int variables were successfully extracted
		if (iss >> i && iss >> j){
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

int boardPieces(ifstream& ifs, vector<brownAlmond>& v, unsigned int a, unsigned int b, NineAlmonds& n){

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
			if (a > x && b > y && pieceCount <= numPiece){
				// this gets a reference to the first piece, then modifies it. The second run of the loop will get the reference to the second piece and so on.
				brownAlmond& piece = n.getPiece(pieceCount);
				piece.color = colorString(color);
				//here I check whether the piece's name (type) matches any of the types that should be passed in. If there isn't a match then the name (type) of the piece is set to "invalid."
				if (piece.color != "brown"){
					// if the color is not brown then the piece color will be set to Invalid. 
					piece.color = "Invalid";
					piece.display = display;
					// the following three lines of code sets the piece's x and y coordinate and the piece's index value on the board.
					piece.setX(x);
					piece.setY(y);
					piece.setIndex(a, x, y);
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
					piece.setIndex(a, x, y);
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











