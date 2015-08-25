#include "GameBase.h"

class NineAlmonds : public GameBase
{
private:

public:
	// printString is utilized to tell the users of the moves that they have made so far in the turn. 
	string printString;
	// turnCount is used to keep track of how many turns the user has used
	int turnCount;
	int pieceCount = 0;
	friend ostream& operator<< (ostream &os, const NineAlmonds &na);
	void print();
	int boardDimension(ifstream& ifs, unsigned int& i, unsigned int& j);
	int boardPieces(ifstream& ifs, vector<brownAlmond>& v);
	virtual bool done();

	// save func
	void save(string s);
	
	// helper method to check if there are any available moves associated to a piece selected by the user.  
	// the following method takes 3 parameters: a reference to a vector and 2 integers. It checks all the pieces and if conditions are met then the piece is pushed into the vector.
	void checkMove(vector<brownAlmond> &checkList, int x, int y);

	//stalemate method
	virtual bool stalemate();

	// prompt function 
	virtual int prompt(unsigned int &a, unsigned int &b);

	// overloaded prompt function to modify the question for the second prompt (the propmt to retrieve the destination for the piece). This is the exact same function as the regular function just with a different prompt message 
	virtual int prompt(unsigned int &a, unsigned int &b, int overLoad);

	// Turn method 
	int turn();

	// overloaded turn function to be used when user decides to continue turn
	// this function is idential to the regular turn() function besides the fact that the helper method to check availability of further moves is called as soon as this overloaded turn function is called. 
	// Instead of using the two coordinates extracted from user input, it uses the two variables that were passed from the turn() function to use the ending space from the previous move as the piece to be moved for the following move.
	int turn(int x, int y);

	// play  method
	int play();
};

