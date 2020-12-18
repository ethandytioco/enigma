//	name:	rotor.h
//	author:	Ethan Dy Tioco
//	desc:	Contains declarations for the Rotor class, to be used for the Enigma project

#ifndef Rotor_H
#define Rotor_H

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Rotor{
private:
	int indexTurnover[2] = {0};
	int rotor[26][2] = {0};
	string name;
	
	
public:
	// Constructors
	Rotor();
	Rotor(string name, string mapping, int indexTurnover1, int indexTurnover2);
	Rotor(const Rotor& orig);	// copy constructor
	Rotor(Rotor&& orig);		// move constructor
	Rotor& operator = (const Rotor& orig);
	
	// GET methods
	string getName();
	int getIndexTurnover1();
	int getIndexTurnover2();
	int getInputAt(int n);
	int getOutputAt(int n);
	
	// Functionalities
	void rotateBy(int n);
	void printRotor();
};

#endif