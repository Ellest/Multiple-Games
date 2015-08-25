#include "stdafx.h"
#include "Piece.h"

// this was taken from lab 1 to transform a string into an all-lowercase string
string lowerCase(string& s){
	for (char& c : s){
		if (isupper(c)){
			c = c + 32;
		}
	}
	return s;
}

// this checks if the color is valid in the piece file upon extraction. This was also taken from lab1
string colorString(string s){
	string a = lowerCase(s);
	if (a == "brown"){
		return "brown";
	}
	else {
		return "invalid";
	}
}
