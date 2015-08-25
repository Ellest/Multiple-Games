#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <sstream>
#include <istream>
#include <iomanip>
using namespace std;

string lowerCase(string& s);
string colorString(string s);

// struct constructed to keep track of each piece
struct brownAlmond {
	private:
		// these private variables have a default value of -1 which indicates that the piece is not on the board. 
		int cordX = -1;
		int cordY = -1;
		int index = -1;
	public:
		string color;
		string display;
		int value = -1;
		// these are the getter and setter methods of the private variables
		int getX() const{
			return cordX;
		}

		int getY() const{
			return cordY;
		}

		void setX(int x) {
			cordX = x;
		}

		void setY(int y) {
			cordY = y;
		}
		int getIndex(){
			return index;
		}
		// takes 3 parameters, the width and two coordinates to set the index of a certain piece
		void setIndex(int w, int x, int y){
			int result = w * (y + 1) + (x + 1);
			index = result;
		}
};