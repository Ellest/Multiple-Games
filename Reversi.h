#include "MagicSquare.h"

enum rowvals {Below = -1, Current, Up};
enum colvals { Left = -1, Right = 1 };

class Reversi : public GameBase
{
	public:
		// integer value for whose turn it is. 1 for player one 2 for player 2
		int whoseTurn;
		// method for switching turns between the two players
		void swapTurn();
		friend ostream& operator<< (ostream &os, const Reversi &re);
		void print();
		bool done();
		int play();
		bool stalemate();
		int turn();
		int prompt(unsigned int &a, unsigned int &b);
		// checks if the move is valid
		bool valid(int x, int y, string wTurn);
		// flips pieces for a valid move
		void flip(int ind);
		// Initializing Pieces for a new game
		void pieceInit();
		// save method
		void save(string s);

		// methods for checking if there's an available move or not
		bool avail(int x, int y, string wTurn);
		bool availCheck();
		bool availCheck(string s);

		// methods for checking move availability. If there is a valid move, the pieces will be flipped accordingly. If check is set to true, only check for validity and don't flip the pieces.
		bool checkDownLeftD(int x, int y, string wTurn, bool check);
		bool checkDown(int x, int y, string wTurn, bool check);
		bool checkDownRightD(int x, int y, string wTurn, bool check);
		bool checkUpLeftD(int x, int y, string wTurn, bool check);
		bool checkUp(int x, int y, string wTurn, bool check);
		bool checkUpRightD(int x, int y, string wTurn, bool check);
		bool checkLeft(int x, int y, string wTurn, bool check);
		bool checkRight(int x, int y, string wTurn, bool check);
};