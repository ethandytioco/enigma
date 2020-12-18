//	name:	enigma.cpp
//	author:	Ethan Dy Tioco
//	desc:	Implementing the functions for the Enigma class

#include <iostream>
#include <string>
#include <cstring>			// <-- memcpy(destination*, source*, sizeInBytes)
#include <cctype>			// <-- isupper(char), tolower(char)
#include <unordered_map>	// <-- for dictionary/labels to be outputted based on a numeric key
#include <algorithm>		// <-- for removing white spaces functionality

#include "enigma.h"			// <-- class definition for enigma
using namespace std;

Enigma::Enigma(){
	
}

void Enigma::start(){
	int menuChoice = 0;
	while(true){
		cout << "\n========= Enigma Machine: Menu =========\n\n";
		cout << "[1] - Configure Enigma <-- do this first\n";
		cout << "[2] - Encrypt/Decrypt\n";
		cout << "[3] - Exit\n";
		cin >> menuChoice;
		
		switch(menuChoice){
			case 1:
				// TODO: configure() takes parameters by reference and writes into them.
				
				break;
			case 2:
				// TODO: useEnigma() takes the parametrs that have been hopefully set by configure()
				
				break;
			case 3:
				cout << "\n...exiting\n";
				return;
				break;
			default:
				cout << "\n[error] unrecognized entry\n\n";
				break;
		}
	}
}