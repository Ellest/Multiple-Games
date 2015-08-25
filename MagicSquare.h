#include "NineAlmonds.h"

class MagicSquare : public GameBase
{
	public:
		//MagicSquare();
		//MagicSquare(int a);
		vector<int> row;
		vector<int> col;
		int diagSum[2];

		// setter for num
		void setNum(int x){
			num = x;
		}

		void save(string s);
		friend ostream& operator<< (ostream &os, const MagicSquare &ma);
		void print();
		bool done();
		int play();
		bool stalemate();
		int turn();
		int prompt(unsigned int &a, unsigned int &b);
		void prompt(int &a);
		bool isDiag(int x, int y);
};
