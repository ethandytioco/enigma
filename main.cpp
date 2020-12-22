//	author:	Ethan Dy Tioco
//	desc:	Creating the Enigma machine (M3) with better coding practices than the first attempt

/*	Citations:
	[1]		Left shift algorithms: https://www.geeksforgeeks.org/array-rotation/
	[2]		memcpy: http://www.cplusplus.com/reference/cstring/memcpy/
	[3]		char tolower(): http://www.cplusplus.com/reference/cctype/tolower/
	[4]		remove non-alphabet characters in string https://www.geeksforgeeks.org/remove-characters-alphabets-string/
	[5?]		check to see if string is comprised of numbers only https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int/37864920
	
	Knowledge sources:
	[i]		Rotor details, turnover: https://en.wikipedia.org/wiki/Enigma_rotor_details
	[ii]	How enigma machines work: https://www.youtube.com/watch?v=G2_Q9FoD-oQ
	[iii]	Ring and ground settings: http://users.telenet.be/d.rijmenants/en/enigmatech.htm
*/
#include <iostream>
#include <string>
#include <cstring>			// <-- memcpy(destination*, source*, sizeInBytes)
#include <cctype>			// <-- isupper(char), tolower(char)
#include <unordered_map>	// <-- for dictionary/labels to be outputted based on a numeric key
#include <algorithm>		// <-- for removing white spaces functionality

#include "rotor.h"			// <-- class definition for rotor
#include "enigma.h"			// <-- class definition for enigma machine
using namespace std;

int main(){

	Enigma m3;
	m3.menu();
	
	return 0;
}