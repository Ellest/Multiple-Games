#include "Piece.h"
#include <memory>
using namespace std;

enum errs{ Success, NullErr, InsuffArg, NotNullErr, SyntaxErr, InvalidUserName, NoAvailableMoves, DataErr, DimensionErr, ArgumentErr, InvalidArguments, IncorrectCommand, Quit, TurnError, StaleMate, Done, Stuck, WrongChoice, ExtractionError, GetLineError, PrintError, IncorrectDimensions, InvalidVector, PieceFileError };
void usage(char * program, string s);

int printBoard(const vector<brownAlmond>& vec, unsigned int a, unsigned int b);

class GameBase
{
	protected:
		static shared_ptr<GameBase> gamePtr;
		unsigned int width;
		unsigned int height;
		// these 9 pieces each indicate a unique piece on the board. They are in the form of "brownAlmonds" which is a custom struct that is created in Piece.h
		brownAlmond pieceOne;
		brownAlmond pieceTwo;
		brownAlmond pieceThree;
		brownAlmond pieceFour;
		brownAlmond pieceFive;
		brownAlmond pieceSix;
		brownAlmond pieceSeven;
		brownAlmond pieceEight;
		brownAlmond pieceNine;
		vector<brownAlmond> board;
		vector<int> pLeft;
		int longest = 0;
		int num = 3;
		int mini = 1;
		string player1;
		string player2;
	public:

		//GameBase(){};

		void setNum(int x){
			num = x;
		}
		void setMini(int x){
			mini = x;
		}
		void setWidth(int x){
			width = x;
		}
		void setHeight(int y){
			height = y;
		}
		void setLongestInt(int x)
		{
			longest = x;
		}
		void setp1(string s){
			player1 = s;
		}
		void setp2(string s){
			player2 = s;
		}
		shared_ptr<GameBase> getPointer(){
			return gamePtr;
		}
		// return pointer
		static shared_ptr<GameBase> instance();

		// main command. Returns the class pointer
		static void command(int argc, char* argv[]);
		vector<brownAlmond>& getBoard();
		void setBoard();
		//helper method to retrieve a piece by coordinates.
		brownAlmond& getPieceByCord(int x, int y);
		// helper method for retrieving each piece. Takes an interger indicating the piece number and returns a reference to that piece.
		brownAlmond& getPiece(int i);
		// sets the longest variable using the value of the piece (since the pieces are all numerical)
		void setLongest();
		// method that initializes the grid view of the board
		void boardInit();
		virtual int play() = 0;

		virtual void print() = 0;
		virtual bool done() = 0;
		virtual bool stalemate() = 0;
		virtual int prompt(unsigned int &a, unsigned int &b) = 0;
		virtual int turn() = 0;
		
 };





