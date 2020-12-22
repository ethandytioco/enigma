//	name:	enigma.h
//	author:	Ethan Dy Tioco
//	desc:	Contains declarations for the Enigma class, to be used in the Enigma project

#ifndef Enigma_H
#define Enigma_H

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "rotor.h"
using namespace std;

class Enigma{
private:
	unordered_map<int, Rotor> rotorBank;
	Rotor reflector, left, center, right, plugboard;
	char ringsetting_l, ringsetting_c, ringsetting_r;
	char groundsetting_l, groundsetting_c, groundsetting_r;
	
public:
	Enigma();

	void menu();
	
	void configure();
	void ringstellung(char l, char c, char r);
	void grundstellung(char l, char c, char r);
	void steckerbrett(string pairs);
	
	void viewConfigurationLite();
	void viewConfiguration();
	
	void useEnigma();
	string scrubInput(string input);
	void rotation();
	int intForceWithinRange(int n);
	void diagnostic();
};

#endif