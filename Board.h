#include "NineAlmonds.h"

//function for retrieving the board dimensions
int boardDimension(ifstream& ifs, unsigned int& i, unsigned int& j);

//function for retrieving the board pieces
int boardPieces(ifstream& ifs, vector<brownAlmond>& v, unsigned int x, unsigned int y, NineAlmonds& n);
