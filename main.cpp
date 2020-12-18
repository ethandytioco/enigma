//	author:	Ethan Dy Tioco
//	desc:	Creating the Enigma machine (M3) with better coding practices than the first attempt

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
	// ----------------------------------------------------------------
	// Testing Rotor::rotateBy() -> SUCCESS
	Rotor rotor_i("I", "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 16, 7);
	rotor_i.printRotor();
	rotor_i.rotateBy(27);
	cout << "\nRotated by 27 spaces\n";
	rotor_i.printRotor();
	// ----------------------------------------------------------------
	
	
	// ----------------------------------------------------------------
	Rotor rotor_ii("II", "AJDKSIRUXBLHWTMCQGZNPYFVOE", 4, 14);
	Rotor rotor_copy = rotor_i;		// copy constructor
	
	
	cout << "\nrotor_copy is now a copy of rotor_i\n";
	rotor_copy.printRotor();
	rotor_copy = rotor_ii;			// = Operator
	
	
	cout << "\nrotor_copy = rotor_ii\n";
	rotor_copy.printRotor();
	
	// ----------------------------------------------------------------
	return 0;
}