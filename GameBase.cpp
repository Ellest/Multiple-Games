#include "stdafx.h"
#include "Reversi.h"
#define numPiece 9

shared_ptr<GameBase> GameBase::gamePtr = nullptr;

shared_ptr<GameBase> GameBase::instance(){
	if (gamePtr == nullptr){
		throw NullErr;
	}
	else {
		return gamePtr;
	}
}

void GameBase::setLongest(){
	for (int i = 1; i < 10; i++){
		brownAlmond b = getPiece(i);
		int pieceLength = b.display.length();
		if (pieceLength > longest){
			longest = pieceLength;
		}
	}
}

void GameBase::boardInit()
{
	int gridX = 0;
	int gridY = 0;
	for (unsigned int i = 0; i < board.size(); i++){
		if (i == 0){
			board[i].display = "+";
			continue;
		}
		if (i < width){
			board[i].display = to_string(gridX);
			gridX++;
			continue;
		}
		if (((i % width) == 0)){
			board[i].display = to_string(gridY);
			gridY++;
			continue;
		}
	}
}


vector<brownAlmond>& GameBase::getBoard(){
	return board;
}

void GameBase::setBoard(){
	board.resize(width * height);
}

brownAlmond& GameBase::getPieceByCord(int x, int y){
	for (int i = 1; i <= numPiece; i++){
		brownAlmond& b = getPiece(i);
		if ((6 * (y + 1) + (x + 1)) == b.getIndex()){
			return b;
		}
	}
	//I have my code designed so that this part of the code will never be called. The purpose of this is to avoid the warning of not all paths returning a value. This also helps with debugging purposes 
	cout << "Piece Not Found Recheck code" << endl;
	return pieceOne;
}

brownAlmond& GameBase::getPiece(int i){
	switch (i){
	case 1:
		return pieceOne;
	case 2:
		return pieceTwo;
	case 3:
		return pieceThree;
	case 4:
		return pieceFour;
	case 5:
		return pieceFive;
	case 6:
		return pieceSix;
	case 7:
		return pieceSeven;
	case 8:
		return pieceEight;
	case 9:
		return pieceNine;
	}
	//I have my code designed so that this part of the code will never be called. The purpose of this is to avoid the warning of not all paths returning a value. This also helps with debugging purposes 
	cout << "Piece Not Found. Recheck Code" << endl;
	return pieceOne;
}

void GameBase::command(int argc, char* argv[])
{
	if (gamePtr != nullptr){
		throw NotNullErr;
	}
	if (argc < 2 || argc > 4){
		cout << "Insufficient Argument" << endl;
		throw InsuffArg;
	}
	if (argc == 2){
		if (strcmp("NineAlmonds", argv[1]) == 0){
			GameBase *nGame;
			nGame = new NineAlmonds;
			gamePtr = make_shared<NineAlmonds>();
			return;
		}
		else if (strcmp("MagicSquare", argv[1]) == 0){
			MagicSquare *mGame;
			mGame = new MagicSquare;
			gamePtr = make_shared<MagicSquare>();
			return;
		}
		else{
			cout << "Syntax Error" << endl;
			throw SyntaxErr;
		}
	}
	if (argc == 3){
		if (strcmp("MagicSquare", argv[1]) == 0){
			istringstream iss(argv[2]);
			int extract;
			if (iss >> extract){
				if (extract >= 1){
					gamePtr = make_shared<MagicSquare>();
					gamePtr->setNum(extract);
					return;
				}
				else {
					cout << "Gameboard Dimensions Must Be Greater Than 1!" << endl;
					throw DimensionErr;
				}
				
			}
			else{
				cout << "Second Argument must be a number!" << endl;
				throw ArgumentErr;
			}
		}
		else {
			cout << "First Argument Must be MagicSquare" << endl;
			throw SyntaxErr;
		}
	}
	else if (argc == 4){
		if (strcmp("MagicSquare", argv[1]) == 0){
			istringstream iss1(argv[2]);
			istringstream iss2(argv[3]);
			int extract1;
			int extract2;
			if (iss1 >> extract1 && iss2 >> extract2){
				if (extract1 >= 1){
					gamePtr = make_shared<MagicSquare>();
					gamePtr->setNum(extract1);
					gamePtr->setMini(extract2);
					return;
				}
				else {
					cout << "Gameboard Dimensions Must Be Greater Than 1!" << endl;
					throw DimensionErr;
				}
			}
			else {
				cout << "Second and Third Arguments must be numbers!" << endl;
				throw ArgumentErr;
			}
		}
		else if (strcmp("Reversi", argv[1]) == 0){
			string p1;
			string p2;
			istringstream ex1(argv[2]);
			istringstream ex2(argv[3]);
			if (ex1 >> p1 && ex2 >> p2){
				Reversi *rGame;
				rGame = new Reversi;
				gamePtr = make_shared<Reversi>();
				gamePtr->setp1(p1);
				gamePtr->setp2(p2);
				return;
			}
			else {
				cout << "Invalid User Name. Please Enter Valid Characters" << endl;
				throw InvalidUserName;
			}
		}
		else {
			cout << "First Argument Must be MagicSquare" << endl;
			throw SyntaxErr;
		}
	}
	else {
		throw SyntaxErr;
	}
}